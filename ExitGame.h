#include "ToolsCl.h"

class ExitGame:tools  {
public:
	ExitGame() {
		exitbuttonSETUP();
		returnButtonSETUP();
	}
	
	void drawButtons(sf::RenderWindow& window, int mousepos[2]) {
		buttons ExitB  (Bsize, BPositions[0], Bcolor, Bborder, false, window, "Exit Game\n"       , mousepos,fontColour);
		buttons ReturnB(Bsize, BPositions[1], Bcolor, Bborder, false, window, "Back\nToMainMenu\n", mousepos,fontColour);
		if (ExitB.getLaunchEvent() == false) {
			window.close();
			
			
		}
		if (ReturnB.getLaunchEvent() == false) {
			buttonlaunch = "M";
			loop = false;
			ReturnB.setLaunchEvent();
		}
	}
	std::string buttonlaunch = "";
	int loop = true;
private:
	void exitbuttonSETUP() {
		int Xpos = windowSizeX * 0.05;
		int Ypos = windowSizeY * 0.720;
		BPositions[0] = { Xpos,Ypos };
	}
	void returnButtonSETUP() {
		int Xpos = windowSizeX * 0.75;
		int Ypos = windowSizeY * 0.720;
		BPositions[1] = { Xpos,Ypos };
	}
	sf::Color fontColour = sf::Color::Black;
	sf::Color Bborder = sf::Color::Red;
	sf::Color Bcolor = sf::Color::White;
	
	std::vector<double> Bsize = { windowSizeX * 0.2, windowSizeX * 0.089 };
	std::vector<std::vector<int>> BPositions = { {},{},{} };
};

