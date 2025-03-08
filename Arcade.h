#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include<iostream>
#include<vector>
#include<string>
#include "ToolsCl.h"
#include "player.h"
#include "enemy.h"
//#include "enemy.h"



class Arcade {
public:
	//DEFAULT CONSTRUCTOR//
	Arcade() {
		
	
	};
	
	//-------------------//
	int getWaveNum() {
		return WaveNum;
	}
	void SetWave() {
		WaveNum++; 
	}
	int getScorePlayer() {
		return PlayerScore;
	}
	bool EnemyPlayerCollision(std::vector<std::vector<int>>EnemyXhitbox, std::vector<std::vector<int>> playerHitbox , sf::RenderWindow& window ) {
		
			if (playerHitbox[1][0] <= EnemyXhitbox[1][1] && playerHitbox[1][0] >= EnemyXhitbox[1][0]
				&& playerHitbox[0][0] <= EnemyXhitbox[0][1] && playerHitbox[0][0] >= EnemyXhitbox[0][0]
				) {
				// the if statement checks the player domain and codomain  agaisnt that of the enemy being checked. 
				//If the player intersects with the enemy Hitbox then the code is triggered 
			//    onArcade = false;
				std::cout << "\n" << "[collison  1 with enemy Occured]" << "\n";
			//	window.close();
				
				return false;
			}
			else if (playerHitbox[1][1] <= EnemyXhitbox[1][1] && playerHitbox[1][1] >= EnemyXhitbox[1][0]
				&& playerHitbox[0][1] <= EnemyXhitbox[0][1] && playerHitbox[0][1] >= EnemyXhitbox[0][0]) {
				// the if statement checks the player domain and codomain  agaisnt that of the enemy being checked. 
				//If the player intersects with the enemy Hitbox then the code is triggered 
				std::cout << "\n" << "[collison  2 with enemy Occured]" << "\n";
				//window.close();
				
				return  false;
				
			}
			else if (playerHitbox[1][1] >= EnemyXhitbox[1][1] && playerHitbox[1][0] <= EnemyXhitbox[1][0]
				&& playerHitbox[0][0] <= EnemyXhitbox[0][1] && playerHitbox[0][0] >= EnemyXhitbox[0][0]
				) {
				// the if statement checks the player domain and codomain  agaisnt that of the enemy being checked. 
				//If the player intersects with the enemy Hitbox then the code is triggered 
				std::cout << "\n" << "[collison 3 with enemy Occured]" << "\n";
			//	window.close();
				
				return  false;
				
			}
			
			return true;
		
	}
	int  BulletEnemyCollision(std::vector<std::vector<int>>EXhbox, std::vector<std::vector<int>> Bulletxy , int row , int Sector , enemy& Eclass, player& PLAYER) {
		//This is the Function that detects whether a collision between an enemy and a Players bullet has taken place 
		// If a collision has taken place then true is returned 
		int returnVal = 0;
		if (Bulletxy.size() != 0) {
			if (Bulletxy[0][0] >= EXhbox[0][0] && Bulletxy[0][0]+10 <= EXhbox[0][1]
				&& Bulletxy[0][1] <= EXhbox[1][1] && Bulletxy[0][1] >= EXhbox[1][0]) {
				PLAYER.clearBulletposArr(); // tHE FIX TO THE BULLET DESTROY PLAYER PROBLEM 
				std::cout << "\n" << Bulletxy[0][0] <<"[ Bullet collison  with enemy Occured]" << "\n";
				returnVal = 1;
				Eclass.DestroyEnemy(row, Sector, P,PlayerScore);
				P.clearBulletposArr();
				return returnVal;
			}
			else {
				return 0; // returns false signifying no collision 
			}
		}
		else
		{
			return 0;// returns false signifying no collision 
		}
		return 0;
	}

	






	void drawArcade(sf::RenderWindow& window, int mousepos[2]) {
		//Function to centralise Drawing for the Arcade in one place to keep clean code

		int temp = 8;
		int titlebarSize[2] = {1200,tls.windowSizeY*0.15};
		int titleBarPos[2] = {1146/2,titlebarSize[1]/2};
		int gameAreaSize[2] = {1093,505};
		int gameAreaPos[2] = {37+gameAreaSize[0]/ 2,122+gameAreaSize[1]/2};
		tools::DrawRect titlebar(&window,titlebarSize,titleBarPos,sf::Color::Green,sf::Color::Black,5);
		tools::DrawRect gameArea(&window, gameAreaSize, gameAreaPos, sf::Color::Black, sf::Color::White, 10);
		int posins[2] = {700,36};
		int rectins[2] = {700,100};
		int rectsi[2] = { 300,36 };
		sf::Color RectTxtColor[2] = { sf::Color::Black,sf::Color::Yellow };
		sf::Color Bcolors[2] = { sf::Color::Red,sf::Color::Red };
		int borderThick[2] = { 3,3 };
	//	tools::DrawText::DrawTextWRect Instructions(window, rectins, { 9,36 }, 13, { sf::Color::Black ,sf::Color::Black }, { sf::Color::Red,sf::Color::Black }, sf::Color::Red, 5, "INSTRUCTIONS : \n move up = W , move left = A , move right = D , move down =S \n Spacebar to fire projectile");
		tools::DrawText::DrawTextWRect::DrawTextWRect(window, rectins, rectsi, 14.5, RectTxtColor, Bcolors, txtColor, borderThick, "INSTRUCTIONS : \n move up = W , move left = A , move right = D , move down =S \n Spacebar to fire projectile");
		// implemented 26/12/2022 // 
		DisplayPlayerScore(window);
		DisplayWaveNum(window);

	}
private:
	void DisplayWaveNum(sf::RenderWindow& window) {
		// Function to display the Wave num to the Arcade
		int PosXY[2] = { 926,66}; 
		int PosXYheader[2] = { PosXY[0],PosXY[1] - ScreenStatSize[1] - 5 };
		sf::Color Bcolors[2] = { sf::Color::Red,sf::Color::Red };
		sf::Color RectTxtColor[2] = {sf::Color::Black,sf::Color::Yellow};
		int borderThick[2] = {3,3};
		tools::DrawText::DrawTextWRect::DrawTextWRect(window, ScreenStatSize, PosXYheader, 14.5, RectTxtColor, Bcolors, txtColor, borderThick, "WAVE \nNUM");
		tools::DrawText::DrawTextWRect::DrawTextWRect(window,ScreenStatSize,PosXY,20,RectTxtColor ,Bcolors,txtColor,borderThick,std::to_string(WaveNum));
	}
	void DisplayPlayerScore(sf::RenderWindow& window) {
		// Function to display the Players score to the Arcade
		int PosXY[2] = { 926 - ScreenStatSize[0] - 10,66};
		int PosXYheader[2] = { PosXY[0] ,PosXY[1] - ScreenStatSize[1] - 5};
		sf::Color Bcolors[2] = { sf::Color::Red,sf::Color::Red };
		sf::Color RectTxtColor[2] = { sf::Color::Black,sf::Color::Yellow };
		int borderThick[2] = { 3,3 };
		tools::DrawText::DrawTextWRect::DrawTextWRect(window, ScreenStatSize, PosXYheader, 14.5, RectTxtColor, Bcolors, txtColor, borderThick, "PLAYER \nSCORE");
		tools::DrawText::DrawTextWRect::DrawTextWRect(window, ScreenStatSize, PosXY, 20, RectTxtColor, Bcolors, txtColor, borderThick, std::to_string(PlayerScore));
	}
	tools tls;
	player P; 
	enemy E;
	sf::RectangleShape gameArea;
	sf::RectangleShape titlebar;
	sf::Texture titleTexture; 
	sf::Sprite title; 
	int gameRectBoundries[2][2] = {};
	int PauseB[2];
	int PauseBSize[2] = {20,50};
	//implemented 26/12/2022 
	int ScreenStatSize[2] = {70,40};
	sf::Color txtColor = sf::Color::Yellow; 
	// 
	int WaveNum = 0; // the wave number 
	int PlayerScore = 0; 
};


