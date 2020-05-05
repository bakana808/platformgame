
CC = g++

# name of executable
OUTPUT = main

ENTRIES = $(SRCDIR)/main.cpp

# .o / .cpp / .h / .d directories
# -------------------------------

BINDIR := bin
OBJDIR := obj
SRCDIR := src
INCDIR := include
DEPDIR := .deps

# SFML location
# -------------

# surface pro loc
# SFML = D:/SFML-2.5.1
# desktop loc
SFML = D:/libs/sfml_2.5.1

# C libraries
# -----------

LIBS =

# dependency generator flags
# --------------------------

# -MT: sets the name of the target generated
# -MMD: ignores system headers when generating dependancies
# -MP: generates phony targets for each dependency
# -MF: sets the name of the .d file generated
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.d

# compile flags
# -------------

# -D_DEBUG: when set, includes debugging messages in the game
# -DSFML_STATIC : when set (combined with linking with "-s" libraries),
#     links the SFML libraries statically (copies the SFML code into the program),
#     instead of dynamically (uses SFML .dll's to run the program)
# -U__STRICT_ANSI__ : allows access to M_PI macro

CFLAGS += -U__STRICT_ANSI__ -Wall -std=c++1z -D_DEBUG -I"./$(INCDIR)"

#==============================================================================
#==============================================================================

# collect source files
# (first wildcard gets root-level .cpp's, second gets nested .cpp's)
SRCS := $(wildcard $(SRCDIR)**/*.cpp) $(wildcard $(SRCDIR)/**/*.cpp)
SRCS := $(filter-out $(ENTRIES),$(SRCS))
OBJS := $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
DEPS := $(wildcard $(DEPDIR)**/*.d) $(wildcard $(DEPDIR)/**/*.d)

EXES := $(subst .cpp,,$(ENTRIES)) # remove .cpp extension
EXES := $(EXES:$(SRCDIR)/%=$(BINDIR)/%)


# platform-dependant flags

# Windows vars
# ------------

ifeq ($(OS), Windows_NT)
	CFLAGS += -L'${SFML}/lib'
	# -isystem adds this folder as system headers
	# (won't be included when generating dependencies)
	CFLAGS += -isystem'${SFML}/include'
	CFLAGS += -static -static-libgcc -static-libstdc++
	CFLAGS += -DSFML_STATIC

	# replace src/ with bin/ and add .exe extension
	# EXES := $(EXES:$(SRCDIR)/%=$(BINDIR)/%.exe)

	# use static libraries for Windows
	LIBS += -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lwinmm -lgdi32 -lfreetype
	OUTFILE := $(OUTPUT).exe

	# exec command
	RUN.c = ${BINDIR}\${OUTPUT}.exe
	#$(OUTFILE)

	# commands to silently make missing folders

	MKDIR_OBJS.c = \
		@if not exist "$(subst /,\,$(@D))" \
		mkdir $(subst /,\,$(@D))

	MKDIR_DEPS.c = \
		@if not exist "$(subst /,\,$(subst $(OBJDIR),$(DEPDIR),$(@D)))" \
		mkdir $(subst /,\,$(subst $(OBJDIR),$(DEPDIR),$(@D)))

	MKDIR_BINS.c = \
		@if not exist "$(subst /,\,$(subst $(OBJDIR),$(BINDIR),$(@D)))" \
		mkdir $(subst /,\,$(subst $(OBJDIR),$(BINDIR),$(@D)))

	# clean command
	CLEAN.c = del /Q /S *.exe *.o *.d

# Unix vars
# ---------

else
	# CFLAGS += -L /usr/lib/x86_64-linux-gnu/lib/ -L/usr/local/lib/
	LIBS += -lsfml-graphics -lsfml-window -lsfml-system
	OUTFILE := $(OUTPUT)


	RUN.c = ${BINDIR}/$(OUTPUT)

	MKDIR_OBJS.c = @mkdir -p $(@D)
	MKDIR_DEPS.c = @mkdir -p $(subst $(OBJDIR),$(DEPDIR),$(@D))
	MKDIR_BINS.c = @mkdir -p $(subst $(OBJDIR),$(BINDIR),$(@D))

	CLEAN.c = rm -rf $(OBJDIR)/*; rm -rf $(BINDIR)/*; rm -f $(OUTFILE); rm -rf $(DEPDIR)/*
endif

#==============================================================================
# targets
#==============================================================================

%.o : %.cpp # remove default target

# executable linking
$(BINDIR)/% : $(OBJDIR)/%.o $(OBJS)
	@echo     creating exec "$(BINDIR)/$(notdir $@)"
	$(CC) $^ -o $(BINDIR)/$(notdir $@) $(CFLAGS) $(LIBS)

# link step
# $(CC) $^ -o $(OUTPUT) $(CFLAGS) $(LIBS)

# compile step
$(OBJDIR)/%.o $(DEPDIR)/%d: $(SRCDIR)/%.cpp
	$(MKDIR_OBJS.c)
	$(MKDIR_DEPS.c)
	$(MKDIR_BINS.c)
	$(CC) $(CFLAGS) $(DEPFLAGS) $< -o $(@:$(DEPDIR)%.d=$(OBJDIR)%.o) -c

# executable dependancy
$(OUTFILE): all

# include src dependencies
include $(DEPS)

#==============================================================================
# utility rules
#==============================================================================

.PHONY: all run run-test clean

all : $(EXES)

run: all
	$(RUN.c)

run-test: bin/test/test-statetimer
	bin/test-statetimer.exe

clean:
	$(CLEAN.c)
