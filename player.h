#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Main.hpp"
#include<iostream>
#include<vector>
#include "ToolsCl.h"
#include "projectile.h"


#pragma once
class player {
public:
	player() {
		playerTexture.loadFromFile("Assets/pla1.png");
		PlayerSprite.setTexture(playerTexture);

	}
	std::vector<std::vector<int>> getBulletFirePos() {
		return BulletsFiredPositions;
	}
	void clearBulletposArr( ) {
		if (BulletsFiredPositions.size() != 0) {
			BulletsFiredPositions.clear();
			//tempBulletHitbox.clear();
		}
	}
	int getBulletFirePosSIZE() {
		return BulletsFiredPositions.size();
	}

	void DeleteBullet() {
		if (BulletsFiredPositions.size() != 0) {
			std::vector<std::vector<int>> temp;
			int erase = 0 ;
			for (int index = 0; index < BulletsFiredPositions.size() - 1; index++) {
				if (BulletsFiredPositions[index][1] < 140) {
					erase = index;
					BulletsFiredPositions.erase(BulletsFiredPositions.begin() + (erase));
					index = BulletsFiredPositions.size() - 1;
					
					//tempBulletHitbox.clear();
				}
			}
			
		}
		
	}

	void SetBulletPositions(std::vector<std::vector<int>> positionsBullets) {
		BulletsFiredPositions = positionsBullets;
	}

	void FireBullet() {
		sf::Context context;
		bool passExecution;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			 passExecution = false;
		}
		else {
			 passExecution = true; 
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)&& passExecution == true) {
		//	std::cout << " \n[Player Shooting at position: " << playerX << "," << PlayerY << " ] \n";
			 
			BulletsFiredPositions.push_back({ ProjXY[0],ProjXY[1]});
			tools::DrawRect bulletX(Gwindow, PBullet.getBulletSize(), ProjXY, sf::Color::Red, sf::Color::Red, 2);
			
			//
			
			//
			//ProjP.SetTimer(5000);

		}

	}

	int* playerPosition() {
		int arr[] = { playerX, PlayerY };
		return arr;
	}
	int* getPlayerSize() {
		int arr[2] = { playerTexture.getSize().x,playerTexture.getSize().y};
		return arr;
	}
	void PlayerPosUpdate() {
	
		PlayerOldPos.push_back({playerX, PlayerY});


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			PlayerY -= 20;
		//	std::cout << PlayerY;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			playerX -= 20;
			
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			playerX += 20;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			PlayerY += 20;
		}

		int arr[] = { playerX,PlayerY };
		ProjXY = ProjP.positionMath(arr, getPlayerSize(), PBullet.getBulletSize(), PBullet.getBulletBuffer());
		
		
		
		PlayerSprite.setPosition(sf::Vector2f(playerX, PlayerY));
	}
	void drawPlayer(sf::RenderWindow& window) {
		Gwindow = &window;
		window.draw(PlayerSprite);
		playerSetBounds();

	}
	std::vector<std::vector<int>> PlayerOldPos;
	
	
	std::vector<std::vector<int>> getPlayerBounds() {
	//function to return the player bounds 
		std::vector<std::vector<int>> hitbox;
		std::vector<int> temp; 
		for (int arr = 0; arr < 2; arr++) {
			for (int coord = 0; coord < 2; coord++) {
				temp.push_back(playerbounds[arr][coord]);
				//std::cout << "\n !" << playerbounds[arr][coord];
			}
			hitbox.push_back(temp);
			temp.clear();
		}
		return hitbox;
	//endfunction 
	}
	
private:
	void playerSetBounds() {
		int bound1_x = PlayerSprite.getPosition().x;
		int bound2_x = PlayerSprite.getPosition().x + playerTexture.getSize().x;
		int bound1_y = PlayerSprite.getPosition().y;
		int bound2_y = PlayerSprite.getPosition().y + playerTexture.getSize().y;
		//std::cout << " player bounds: [x : " << bound1_x <<" , " << bound2_x<<"]";
	//	std::cout << " ,[y : " << bound1_y << " , " << bound2_y<<"]";
		playerbounds[0][0] = bound1_x;
		playerbounds[0][1] = bound2_x;
		playerbounds[1][0] = bound1_y;
		playerbounds[1][1] = bound1_y;
	}
	//
	
	//
	projectile::playerP ProjP;
	Bullet PBullet;
	tools tls;
	sf::Sprite PlayerSprite;
	sf::Texture playerTexture;
	int playerbounds[2][2]; //player hitbox coordinates  , [[x1,x2],[y1,y2]]
	int playerX = tls.windowSizeX * 0.5;
	int* ProjXY;
	int projNum = 0 ;
	std::vector<std::vector<int>> BulletsFiredPositions{};
	int PlayerY = tls.windowSizeY * 0.75;// player positions
	
	sf::RenderWindow* Gwindow;
};