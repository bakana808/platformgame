#include"obstacle.h"


void Obstacle:: spawnTrap(){

	tex.loadFromFile("upperTriangle.png");
	topTrap.setTexture(tex);
	topTrap.setScale(0.2, 0.2);
	topTrap.setPosition(topXposition,topYposition);

	tex.loadFromFile("bottomTriangle.png");
	bottomTrap.setTexture(tex);
	bottomTrap.setScale(0.2, 0.2);
        bottomTrap.setPosition(bottomXposition,bottomYposition);
}

void Obstacle:: activateTrap(){
	spawnTrap();
		//No need stop x, ++ypos//
		int topStopYposition=-100;
		int bottomStopYposition=500;
	while(topXposition==200){

		topYposition--;
		bottomYposition++;

     if(topYposition==topStopYposition && bottomYposition==bottomStopYposition)
     {
	     //Spawn traps at starting position//
		topTrap.setPosition(topXposition,topYposition);
		bottomTrap.setPosition(bottomXposition,bottomYposition);}

	else{

		topYposition--;
		bottomYposition++;
			}
	}
}

