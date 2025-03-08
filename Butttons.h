

// Inside Buttons.h header file 

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include<iostream>
#include<vector>
#include<string>
#include "ToolsCl.h"

class buttons {
public:
	//DEFAULT CONSTRUCTOR 
	buttons() { 	}
	//
	sf::RectangleShape getButtonArea() {
		return buttonArea;
	}
	sf::Text getText() {
		return text;
	}
	bool getLaunchEvent() {
		return launchEvent;
	}
	void setLaunchEvent() {
		launchEvent = true;
	}
	//CONSTRUCTOR USED TO CREATE BUTTONS
	buttons(std::vector<double> size, std::vector<int> position,sf::Color color, sf::Color borderColor, 
		bool specialFont ,sf::RenderWindow& window, std::string buttonTxt, int mousepos[2], 
		sf::Color FontColour);// size , position , color , bordercolor ,special font (bool), window ptr, txt, mousepos array
	//-----------------------------------------------------//
	std::vector<std::vector<int>> getVERTICIES() {
		std::vector<std::vector<int>> vertexes = { {},{} };
		int temp;
		//{verticies[0][0],verticies[0][1] } 
		//{verticies[1][0],verticies[1][1] }};
		std::cout << "a\n";
		return vertexes;
	}
	bool checkMousePositions(int mousepos[2]) {
		int mousepos_x = mousepos[0];
		int mousepos_y = mousepos[1];
		//std::cout << verticies_[0][1]<<" ,"<<mousepos_x;
		if (mousepos_x > verticies_[0][0] && mousepos_x < verticies_[0][1] 
			&& mousepos_y > verticies_[1][0] && mousepos_y < verticies_[1][1])
		{
			std::cout << "\n[Button Hover Command  Executed ]\n";
			buttonArea.setFillColor(sf::Color::Red);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
				std::cout << "\n[Button Pressed Command Executed ]\n";
				return false;
			}
			else {
				return true;
			}
		}
		else
		{
			return true;
		}
	}
	sf::Text text;
private:
	void setVERTICIES(std::vector<double> size, std::vector<int> position ) {
		verticies_[0][0] = position[0]; //top left corner (x)
		verticies_[0][1] = position[0] + size[0]; //top right corner (x)
		verticies_[1][0] = position[1] ; // top left corner (y)
		verticies_[1][1] = position[1] + size[1]; //top right corner (y)
		std::cout<<"[[x: " << verticies_[0][0] << "," << verticies_[0][1]<<"],";
		std::cout <<"[y: " << verticies_[1][0] <<"," << verticies_[1][1] << "]]";
	}
	void textSetup(sf::RenderWindow& window ,std::vector<int> position , std::string buttonTxt ,sf::Color FontColour) {
		sf::Font font;
		if (!font.loadFromFile("Assets/fonts/arial_narrow_7.ttf"))
		{
			std::cout << "Font load error!\n";
		}
		
		text.setString(buttonTxt);
		text.setFont(font);
		text.setCharacterSize(40);
		text.setFillColor(FontColour);
		text.setPosition(sf::Vector2f(position[0]+25, position[1]+5));
		window.draw(text);
	}
	//VARIABLES//---------------------------//

	sf::RectangleShape buttonArea;
	bool launchEvent = true;
	tools tls;
	sf::Texture buttonTexture;
	int verticies_[2][2] = {{0,0},{0,0}};
	//--------------------------------------//
};
buttons::buttons(std::vector<double> size, std::vector<int> position,
	sf::Color color,sf::Color borderColor,bool specialFont,
	sf::RenderWindow& window , std::string buttonTxt, int mousepos[2], sf::Color FontColour)
{
	buttonArea.setSize(sf::Vector2f(size[0],size[1]));
	buttonArea.setPosition(sf::Vector2f(position[0],position[1]));
	buttonArea.setFillColor(color);
	buttonArea.setOutlineColor(borderColor);
	buttonArea.setOutlineThickness(2);
	std::cout <<" , " << buttonTxt << ": ";
	setVERTICIES(size,position);
	launchEvent=checkMousePositions(mousepos);
	window.draw(buttonArea);
	textSetup(window,position,buttonTxt,FontColour);
	
}
/// THis is the class for slider buttons
/// All slider buttons will be created using the constructor 

class SliderButton:buttons {
public:
	//DEFAULT CONSTRUCTOR
	SliderButton() {

	}
	//CONSTRUCTOR USED TO CREATE SLIDER 
	SliderButton(int a);
private:
};
SliderButton::SliderButton(int a) {

}