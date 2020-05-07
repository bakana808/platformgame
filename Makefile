
# the c++ compiler to use
CC = g++

# name of output executable
OUTPUT = main

# list of source files with a main() function
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

# Windows-specific libraries
ifeq ($(OS), Windows_NT)

# NOTE: static variants of SFML libraries used
# The use of static libraries was used so the compiled .exe file
# does not require any additional .dlls to be included with it.
LIBS += -lsfml-graphics-s -lsfml-window-s -lsfml-system-s
LIBS += -lopengl32 -lwinmm -lgdi32 -lfreetype

# Unix-specific libraries
else

LIBS += -lsfml-graphics -lsfml-window -lsfml-system

endif


# dependency generator flags
# --------------------------
# Compiling source files will generate a .d file. This file follows
# the makefile syntax, which contains targets where the target is the .cpp file
# and the dependencies are the header files found in the .cpp file.
#
# By including these .d files into this makefile we can automate the process of
# adding header files into the Makefile for a given source file.

# -MT: sets the name of the target generated
# -MMD: ignores system headers when generating dependancies
# -MP: generates phony targets for each dependency
# -MF: sets the name of the .d file generated

DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.d

# compile flags
# -------------

# -Wall: displays all warnings when compiling
# -D_DEBUG: when set, includes debugging messages in the game
# -DSFML_STATIC : when set (combined with linking with "-s" libraries),
#     links the SFML libraries statically (copies the SFML code into the program),
#     instead of dynamically (uses SFML .dll's to run the program)
# -U__STRICT_ANSI__ : allows access to M_PI macro

CFLAGS += -U__STRICT_ANSI__ -Wall -std=c++1z -D_DEBUG -I"./$(INCDIR)"

#==============================================================================
#==============================================================================

# ALL AUTOMATIC BELOW

#==============================================================================
#==============================================================================

# automatically find all source files in this project and store it in $(SRCS)
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

	# exec command
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
# ------------------

$(BINDIR)/% : $(OBJDIR)/%.o $(OBJS)
	@echo     creating exec "$(BINDIR)/$(notdir $@)"
	$(CC) $(FLAGS) $^ -o $(BINDIR)/$(notdir $@) $(CFLAGS) $(LIBS)

# link step
# $(CC) $^ -o $(OUTPUT) $(CFLAGS) $(LIBS)

# compile step
# ------------------

$(OBJDIR)/%.o $(DEPDIR)/%d: $(SRCDIR)/%.cpp
	@echo [INFO] TARGET: $@
	@echo [INFO] PREREQS: $?
	$(MKDIR_OBJS.c)
	$(MKDIR_DEPS.c)
	$(MKDIR_BINS.c)
	$(CC) $(CFLAGS) $(FLAGS) $(DEPFLAGS) $< -o $(@:$(DEPDIR)%.d=$(OBJDIR)%.o) -c

# have our output file depend on all
# ----------------------------------

$(OUTFILE): all

# include all .d files
# --------------------

include $(DEPS)

#==============================================================================
# utility rules
#==============================================================================

.PHONY: info all run run-test clean

info :
	@echo =====================================================================
	@echo COMPILING INFO:
	@echo =====================================================================
	@echo src dir: $(SRCDIR)/
	@echo inc dir: $(INCDIR)/
	@echo dep dir: $(DEPDIR)/
	@echo bin dir: $(BINDIR)/
	@echo srcs: $(SRCS)
	@echo =====================================================================

all : info $(EXES)

run: all
	$(RUN.c)

run-test: bin/test/test-statetimer
	bin/test-statetimer.exe

clean:
	$(CLEAN.c)
