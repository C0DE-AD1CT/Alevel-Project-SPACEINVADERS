#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include<iostream>
#include<vector>
#include<string>
#include "ToolsCl.h"
#pragma
//#include "scaler.h"
class gamemodes {
public:

	//DEFAULT CONSTRUCTOR
	gamemodes()  {
		SETUPArcadeB();
		SETUPGameSettingsB();
		SETUPReturnB();
		titleTexture.loadFromFile("Assets/SI3.png");
		title.setTexture(titleTexture);
	//void run()
	}
	void drawScreen(sf::RenderWindow &window, int mousepos[2]) {
		//sf::Thread DBTHREAD(gamemodes::drawButtons,this, window, mousepos);
		window.clear(BackgroundColor);
		SETUPbuttonCont();
	//	std::cout << buttonCont.getSize().x;
		window.draw(buttonCont);
		SETUPscreenTitle(window);
		
		
		
	}
	void drawButtons(sf::RenderWindow &window ,int mousepos[2])  {
		buttons ReturnB(Bsize,BPositions[2], Bcolor, Bborder, false, window, "Back ToMainMenu\n", mousepos, fontColour);
		buttons Arcade(Bsize, BPositions[0], Bcolor, Bborder, false, window, "ARCADE\n", mousepos, fontColour);
		buttons Gsettings(Bsize, BPositions[1], Bcolor, Bborder, false, window, "GAME SETTINGS\n", mousepos, fontColour);
		//ReturnB.checkMousePositions(tls.mousepos);

		if (ReturnB.getLaunchEvent() == false) {
			buttonlaunch = "M";
			loop = false;
			ReturnB.setLaunchEvent();
		}
		if (Arcade.getLaunchEvent() == false) {
			buttonlaunch = "A";
			loop = false;
			Arcade.setLaunchEvent();
		}
		if (Gsettings.getLaunchEvent() == false) {
			buttonlaunch = "GS";
			loop = false;
			Gsettings.setLaunchEvent();
		}
	}
	//-----------------------//
	std::string buttonlaunch = "";
	int loop = true;
private:
	
	void SETUPbuttonCont() {
		int Xpos = 740;
		int Ypos = tls.windowSizeY *0.01;
		int Xsize = tls.windowSizeX*0.39;
		int Ysize = tls.windowSizeY*0.85;
		//
		//std::cout << "["<<""<<"";
		
		// 
		buttonCont.setPosition(sf::Vector2f(Xpos,Ypos));
		buttonCont.setSize(sf::Vector2f(Xsize, Ysize));
		buttonCont.setFillColor(sf::Color(38, 247, 219)); //rgb(38, 247, 219)
		buttonCont.setOutlineColor(sf::Color::Black);
		buttonCont.setOutlineThickness(tls.windowSizeY * 0.003);
	}
	void SETUPscreenTitle(sf::RenderWindow& window) {
		int Xpos = 38;
		int Ypos = 46;
		
		title.setPosition(Xpos,Ypos);
		
		title.setScale(sf::Vector2f(0.9,0.9));
		window.draw(title);
	}
	void SETUPGameSettingsB() {
		int Xpos = 760;
		int Ypos = tls.windowSizeY*0.25;
		BPositions[1] = { Xpos,Ypos };
	}
	void SETUPArcadeB() {
		int Xpos =760 ;
		int Ypos = tls.windowSizeY *0.05;
		BPositions[0] = { Xpos,Ypos };
	}
	void SETUPReturnB() {
		int Xpos = 760;
		int Ypos = tls.windowSizeY*0.45;
		BPositions[2] = { Xpos,Ypos };
	}

	tools tls;
	scaleImage SCALE;
	sf::RectangleShape buttonCont;
	sf::Sprite title;
	sf::Texture titleTexture;
	sf::Color BackgroundColor = sf::Color(38,240,219);//rgb(38, 240, 219)
	sf::Color Bborder = sf::Color::Black;
	sf::Color Bcolor = sf::Color(252, 235, 103,99); //rgb(52, 235, 103)
	sf::Color fontColour = sf::Color(7, 110, 34);//rgb(7, 110, 34)
	sf::Color colour = sf::Color(0x8afff9); //rgb(38, 240, 219)
	sf::Color borderColor = sf::Color::Black;
	std::vector<double> Bsize = { tls.windowSizeX * 0.35, tls.windowSizeX * 0.089 };
	std::vector<std::vector<int>> BPositions = { {},{},{} };

//	sf::Thread test;
};
