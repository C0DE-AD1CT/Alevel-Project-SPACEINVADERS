#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Main.hpp"
#include<iostream>
#include<vector>
#include "ToolsCl.h"
#pragma once
class projectile {
public:
	projectile() {}
	class playerP  {
	public:
		playerP() {
			//timer = -1;
		}
		int * positionMath(int playerxy[2], int playerSize[2],int bulletSize[2], int BulletBuffer) {
			// this function will constantly run in the background <-- needs to be constantly updated
			int playerX = playerxy[0]; 
			int playerY = playerxy[1];
			int playerSizeX = playerSize[0]; 
			int playerSizeY = playerSize[1];
			// the math of the function //
			projectileArr[0] =(playerX + (playerSizeX/2.5)) +  bulletSize[0];
			projectileArr[1] = (playerY-50) + BulletBuffer;
	//		std::cout << "\nprojectiles xy player:" << projectileArr[0] << "," << projectileArr[1];
			return projectileArr;
		};
		int GetTimer() {
		//	std::cout << " \n[ timer : " << timer << "]";
			return timer;
		}
		void SetTimer(int value) {
			timer = value; 
		//	std::cout << " \n[ timer : " << timer << "]";
		}
	private:
	//	player P; 
		std::vector<int> BulletsVEC;
		int projectileArr[2];
		int timer; 
	};
	class  enemy {
	public:
		enemy() {}
		
		void positionMath() {};
	private:
		
	};
	tools tls;
private:
};

class Bullet {
public:
	Bullet() {
		BulletBuffer = 10; // 10 pixel // 
		bulletSize[0] = 5;
		bulletSize[1] = 12;
	}
	Bullet(int position[2], sf::RenderWindow& window, bool IsPlayer);
	int* getBulletSize() {
		return bulletSize;
	}
	int getBulletBuffer() {
		return BulletBuffer;
	}
	void SetBullet(sf::RenderWindow* window) {
		Gwindow = window;
	}
	void drawBullet(std::vector<std::vector<int>> bulletPositions, int bulletPositionSize) {

		for (int index = 0; index < bulletPositionSize - 1; index++) {

			bulletPosition[0] = bulletPositions[index][0];
			bulletPosition[1] = bulletPositions[index][1];
			tools::DrawRect bulletx(Gwindow, bulletSize, bulletPosition, sf::Color::Yellow, sf::Color::Red, 5);
			std::cout << "\nBullets " << index << "[" << bulletPosition[0] << "," << bulletPosition[1] << "]";
		}
	}
	std::vector<std::vector<int>> moveBullet(std::vector<std::vector<int>> bulletPositions, int bulletPositionSize) {
		for (int index = 0; index < bulletPositionSize - 1; index++) {
			bulletPositions[index][1] -= 15;
		}
		return bulletPositions;
	}
	std::vector<std::vector<int>> getBulletHitbox() {
		return BulletHitbox;
	}
private:
	void SetBulletHitbox() {
		BulletHitbox.push_back({ bulletPosition[0],bulletPosition[0] + bulletSize[0] });
		BulletHitbox.push_back({ bulletPosition[1],bulletPosition[1] + bulletSize[1] });
	}
	sf::RenderWindow* Gwindow; // pointer to the window 
	std::vector<std::vector<int>> BulletHitbox;
	int bulletSize[2];
	int bulletPosition[2];
	int BulletBuffer;
	void BulletArea() {}
	void Setupbullet() {}
};
//custom bullet constructor definition 
Bullet::Bullet(int position[2] ,sf::RenderWindow &window, bool IsPlayer) {
	for (int index = 0; index < 2 - 1; index ++) {
		bulletPosition[index] = position[index]; 
	}	
}