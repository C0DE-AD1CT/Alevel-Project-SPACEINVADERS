
#include <vector>
#include <iostream>
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Main.hpp"
#include "Arcade.h"
// need to include an additional include to get the quotient of a division: 
#include <cstdlib>
#pragma once
class enemySprite {
	//this is the class for the enemy sprites 
	//class start 
public:
	enemySprite() {
	}
	//constructor declaration 
	enemySprite(int pos[2], int minspawnY, int sectorHeight, int row, sf::Texture enemyTexture, sf::RenderWindow* window);
	// constructor for enemy object takes 3 variables:
	//

	sf::Sprite getSprite() {
		//this is a function to get the enemy sprite with all its attributes 
		//function start 
		return enemyX;
		// function returns the enemy sprite
	}
	int* getPosition() {
		return positions;
	}
	void SetPosition(int pos[2]) {
		//This is the function to set the position of the sprite
		//takes a 1-d array as a parameter and is a void function 
		positions[0] = pos[0];//stores the new positions in the positions array 
		positions[1] = pos[1];
		//sets the position of the sprite 
		enemyX.setPosition(sf::Vector2f(pos[0], pos[1]));
		//endprocedure 
	}
	void DisplayEnemy(sf::RenderWindow* window) {
		//the function to display enemy 
		//start function 
		enemyX.setTexture(texture);
		setHitbox(positions);
		if (positions[1] > 100) {
			window->draw(enemyX);
		}
		else {
		//	std::cout << "\n[enemy not in game area]\n";
		}
		//endfunction 
	}
	int Hitbox[2][2];
	void setHitbox(int posX[2]) {
		//function start 
		//function to calculate the hitboxes for the enemy 
		Hitbox[0][0] = posX[0]; // left x coord
		Hitbox[1][0] = posX[1]; // top left y coord
		Hitbox[0][1] = posX[0] + SizeX[0]; //  right x coord
		Hitbox[1][1] = posX[1] + SizeX[1]; // bottom right y coord
		//function end  
	//	std::cout << "\nHitbox [" << Hitbox[0][0] <<"," << Hitbox[0][1] <<"][" << Hitbox[1][0] << "," << Hitbox[1][1] << "]";
	}
	
	// ENEMY VALUE SECTION + GET METHODS 
	void AssignPoints(std::string Etype) {
		if (Etype == "even") {
			EnemyValue = 100;
		}
		else if (Etype == "odd") {
			EnemyValue = 150;
		}
		else {
			//impossible// 
		}//endif//
	}//endprocedure// 
	int RetrievePoints() {
		return EnemyValue;
	}
private:
	int EnemyValue; // variable holding the enemy value 
	int positions[2];  // holds the xy positions of the enemy 
	sf::Texture texture;
	sf::Sprite enemyX;
	int SizeX[2]; 
};
//clss end 
//constructor definition
enemySprite::enemySprite(int sectorX[2], int minspawnY, int sectorHeight, int row,
	sf::Texture enemyTexture, sf::RenderWindow* window) {
	//planning the constructor:
	// sector ranges: 
	//row 1 :  ylower = minspawnY, yupper = ylower-sectorHeight
	//row 2 to n: ylower = minspawny - (sectorHeight*n), yupper = ylower + sector Height
	//spawning the enemies. 
	//the enemies will be spawned in the center of each sector: 
	//enemy  xpos = (sectorx[0]+sector[1])/2  , ypos = (ylower+yupper)/2
	//Uing the equation determined in plan
	positions[0] = ((sectorX[0] + sectorX[1]) / 2) - 50;
	positions[1] = ((minspawnY + (-sectorHeight * row)) - sectorHeight) / 2;
	//setting the enemy textures, hitboxes and attributes: 
	enemyX.setPosition(sf::Vector2f(positions[0], positions[1]));
	texture = enemyTexture;
	// I will need a way to determine whether to diplay the enemy if its on the game screen: 
	SizeX[0] =  texture.getSize().x ;
	SizeX[1] = texture.getSize().y;
//	DisplayEnemy(window); // calls function to display enemy 
 // draws the enemy to the screen using the window pointer 
}