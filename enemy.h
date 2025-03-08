#pragma once
#include <vector>
#include <iostream>
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Main.hpp"
#include "Arcade.h"
// need to include an additional include to get the quotient of a division: 
#include <cstdlib>
// 
#include "EnemySprite.h"
#include "EnemyMovement.h"
// here is the general class for enemies

class enemy {
public:
	enemy() {

	}
	void setWindow(sf::RenderWindow* win) {
		window = win;
		
	}
	int getEnemyNum() {
		//std::cout << "Enemy Num: " << enemyNum << "\n";
		return enemyNum;
	}
	int getEnemyRowNum() {
		//function to return the number of enemy rows.
		return rownum;
	}
	int getEnemiesPerRow() {
		//function to return the enemies per row 
		return 4;
	}
	std::vector<std::vector<int>> getEnemySpriteHitbox(int RowX, int EnemyX) {
		//function to return the hitbox of a specific enemy
		//2d vector to temporarily hold the hitboxes in integer form 
		std::vector<std::vector<int>> EHitbox; 
		std::vector<int> temp; 
		//retrieves the Specific EnemySprite from the Sprite 2d array 
		enemySprite EnemyObj = initialisedEnemies[RowX][EnemyX];
		//Pushes back the hitboxes of the sprite onto the array
		//x coords positioned at index 0 
		//y coords positioned at index 1
		EHitbox.push_back({ EnemyObj.Hitbox[0][0], EnemyObj.Hitbox[0][1] });
		EHitbox.push_back({ EnemyObj.Hitbox[1][0], EnemyObj.Hitbox[1][1] });
		//r
		return EHitbox; // returns the 2d vector  defined 
	}
	void DestroyEnemy(int row ,int Sector , player &P ,int &PlayerScore){
		//Function to prevent enemy from being drawn or interfering
		enemyActive[row][Sector] = 1; // Sets the active state to 1 meaning the enmy is no longer active 
		//ASSIGNING THE ENEMIES VALUE  TO THE PLAYER SCORE
		PlayerScore += initialisedEnemies[row][Sector].RetrievePoints();
		//end of assignment section 
		std::cout << "\n"<< enemyActive[row][Sector]<<"[ENEMY ELIMINATED]\n"; 
		enemiesEliminated++;  // Adds to the enemy eliminated counter 
		//NOTE: the enemies eliminated counter will be compared to the enemy Num 
		// If it is the same, or greater than enemynum, then enemynum will be set to 0 
		//this will automatically usher a new wave in the main cpp file, as all the enemies are defeated 
	//	std::cout << "\n Eliminated Enemy Num : " << enemiesEliminated << "\n";
		if (enemiesEliminated >= enemyNum) {
			enemyNum = 0;
		}
	}
	int getEnemyActiveState(int rowx, int Sector) {
		// Functions to get whether the enemy is alive or no // 
		// 0 is default --> this means the enmy is alive , 1 on the contrary means inactive or 'dead' 
		if (enemyActive[rowx][Sector] != 0) {
			// if statement to prevent Index-Error 
			return enemyActive[rowx][Sector]; 
			//Returns the enemyActive state for the particular enemy identified by its row and sector 
		}
		else {
			return 0;
		}
	}
	void RESET_EliminatedArr() {
		for (int Row = 0; Row < sizeof(enemyActive);Row++) {
			for (int Sector = 0; Sector < sizeof(enemyActive[Row]); Sector++) {
				enemyActive[Row][Sector] = 0;
			}
		}
		enemiesEliminated = 0;
	}
	void InitialiseEnemies() {
		//this function should only call once
		//startFunction 
		//A function to setup the enemy Sprites & draw them to the screen 
		//initialises their textures & positions & sprites. 
		sf::Texture evenE; // texture for even enemies 
		sf::Texture oddE; // texture for odd enemies 
		//for the time Assets for the enemy are loaded here: 
		evenE.loadFromFile("Assets/Enemy/E2.png");
		oddE.loadFromFile("Assets/Enemy/E1.png"); 
		int EnemyRem;
		for (int row = 0; row < enemies.size(); row++) { 
			
		// for loop loops through the first level of the vector, which corrosponds to the row  
			std::vector<enemySprite> temp; // this vector will temporarily hold the constructed enemySprites until they can be assigned
			for (int Enemy = 0; Enemy < enemies[row].size(); Enemy++) {
				
				EnemyRem = div(Enemy, 2).rem; // returns the remainder of the division 
				//std::cout << "[row" << row << "]";
				if (EnemyRem != 0 && enemies[row][Enemy] == true) {
				//startif 
				// if the remainder is not = 0 then the following code will be executed
				// this is to seperate the odd places from the even places. This is done because there will be unique assets
				//for each odd place and even place 
				//for now this is all there will be, although later minibosses may be added at the end.
					enemySprite EnemyX(sectors[Enemy], MaxEnemyYSpawnPos, sectorXHeight, row,oddE, window);
					EnemyX.AssignPoints("odd"); // assigning the points 
					initialisedEnemies[row][Enemy] = EnemyX ;
				}
				else if (EnemyRem == 0 && enemies[row][Enemy] == true)
				{ // all even enemies here 
					enemySprite EnemyX(sectors[Enemy],MaxEnemyYSpawnPos,sectorXHeight,row,evenE,window);
					EnemyX.AssignPoints("even"); // Assigning the points 
					initialisedEnemies[row][Enemy] = EnemyX;
				}
				// endif
				temp.clear(); // empties the vector 
			} // end of nested loop
		}//end of loop 
		//endfunction 
	}
	void DisplayEnemies() {
		// num records the current enemy number in the context of the function: 
		int num = 0;
		// rownum holds the total number of rows of enemies
		rownum = div(enemyNum, 4).quot;
		for (int row = 0 ; row < sizeof(initialisedEnemies ) && row<rownum; row ++) {
			//std::cout << "[row" << row << "]";
			for (int EnemyX = 0; EnemyX < sizeof(initialisedEnemies[row])  && num < enemyNum; EnemyX++) {
				num++;
			//	std::cout << "[row" << EnemyX << "]";
				if (enemyActive[row][EnemyX] == 0) {
					initialisedEnemies[row][EnemyX] = Emov.method1(initialisedEnemies[row][EnemyX]);
					initialisedEnemies[row][EnemyX].DisplayEnemy(window);
				}
				// std::cout <<"POINT of Enemy Num-"<<num<<"\t[" << initialisedEnemies[row][EnemyX].Hitbox[1][0] << "]\n";
				// 
			}
		}
	}
	void enemyNumCalc(int waveX){
		//this function works out the number of enemies 
		int n; // this is the factor for increasing (determined by wave number) 
		int d = 4;
		n = 0.5 + (0.3 * waveX);
		if (n > 3) {
			n = 3.7; // ensures that the factor remains at 3.5 no matter what 
			//was 10 originally, however that spawned approximatley 280 enemies!!! too much. 
		}
		//calculating the total enemy num 
		int Sn; 
		Sn = (n / 2) * ( (2*InitialEnemies)+((n - 1)*d) );
		if (Sn <= 4) {
			Sn = InitialEnemies;
		}
		Emov.SetINCR(waveX);
		//std::cout << "\nEnemyNum : " << Sn << "\n";
		enemyNum = Sn; 
		
	}	
	void EnemyPositions() {
		//the number of rows will be the whole number return of :  total enemies  / 4   
		//we divide by 4 as there are 4 sectors in total 
		int nrows; 
		div_t RowQuotient_and_remainder = div(enemyNum, 4); // part of the 'cstdlib' library 
		nrows = RowQuotient_and_remainder.quot; // sets the row num to the quotient of the division 
		int EnemiesLeftToAssign = enemyNum;
		//loop to set the enemy positions;
		//for the time being formation will be generic 
		//std::cout << "\n[";
		
		for (int row = 0; row < nrows; row ++) {
			//std::cout << "[";
			enemies.push_back({ false,false,false,false });
			for (int x = 0; x < 4;x++) {
				if (EnemiesLeftToAssign != 0) {
					enemies[row][x] = true;
				}
				else {
					enemies[row][x] = false;
				}
				EnemiesLeftToAssign -= 1;
			//	std::cout << enemies[row][x] << ",";
			}
		//	std::cout << "]";
		}
		//std::cout << "]\n";
	}
	int enemyNum;
	int enemiesEliminated = 0;
	
private:
	//Arcade Ar;
	EnemyMovement Emov;
	int rownum = 5;
	int InitialEnemies = 4;
	int LEFTbufferX =  150 ; // xend
	int RIGHTbufferY = 1112;// xstart 
	int MaxEnemyYSpawnPos = 0 + 500;
	int sectors[4][2] = { {60+ 150,123 + 150},{223 + 150,386 + 150},{486 + 150,649 + 150},{749 + 150,912 + 150}};// {xstart ,  xend} .... {xnstart, xnend}
	int enemyPos[2];
	int sectorXWidth = 163;
	int sectorXHeight = 263;
	std::vector<std::vector<bool>> enemies; 
	enemySprite initialisedEnemies[5][4]; // vector holding the enemy objects  <-- can hold 80 enemies 
	int enemyActive[5][4];//Holds whether the enemy has been eliminated  -->  1 for true, 0 for false ; 
	//the above vector holds the enemies which can now be drawn to the screen; 
	sf::RenderWindow* window; // pointer to the window 
};