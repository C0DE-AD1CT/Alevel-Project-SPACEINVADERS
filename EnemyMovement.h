#include <vector>
#include <iostream>
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Main.hpp"
#include "EnemySprite.h"
#pragma once

class EnemyMovement {
	//  this is the class for the enemy movmeent
	//  All methods regarding enemy movement are contained here 
public:
	// Primary Movement Pattermn 
	enemySprite method1(enemySprite enemyX) {
		int* EnemyOldPos = enemyX.getPosition();
		int EnemyNewYPos = EnemyOldPos[1] + moveDown();
		int EnemyNewPos[2] = { EnemyOldPos[0], EnemyNewYPos };
		enemyX.SetPosition(EnemyNewPos);
		return enemyX;
	}
	//for a later stage 
	enemySprite method2(enemySprite enemyX) {

	}
	void SetINCR(int waveX) {
		if (waveX <= 2) {
			incr = waveX * 1;
		}
		else {
			incr = 2;
		}
	}
	// 
private:
	// the methods to move the enemies are defined below: 
	int moveUp() {
		//function will increment the enemy y positions negatively
		return -incr;
	}
	int moveDown() {
		//function will increment the enemy y positions positively
		return +incr;
	}
	int moveLeft() {
		//function will increment the enemy x positions negitively
		return -incr;
	}
	int moveRight() {
		//function will increment the enemy x positions positively 
		return +incr;
	}
	int incr = 1;
};
