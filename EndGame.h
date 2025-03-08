#pragma once
#include "Arcade.h"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Main.hpp"
#include<iostream>
#include<vector>
#include <SQL.H>
#include "ToolsCl.h"


// new class named Endgame 
//THis is for the endgame screen 
// this was done as part of the databases addition
// 
// 
// 
// struct typeX {
//		std::string type;
//		std::string name;
//		std::vector<int> size;
//		std::vector<int> pos;
//		sf::RectangleShape shapeX;
//		sf::Color bodycolour;
//		sf::Color borderColour;
//		int Bthick;
//	};
//

//we have 5 main visual elements to the screen: 
	//  ENTXT - the text telling the user to enter text 
	//  ENTXTINP - the input box where text is input 
	//	SUBBTTN  - The button that submits to the database 
	//  WaveTxt - above the wave box stating what it represents : the wave number
	//  WaveBox  - holds the wave number the user managed to progress to 
	//  ScoreTxt - above the Score box stating what it represents :
	//  Score Box  - hold the score the user obtained 
	//  GameTITLE  - Aesthetic, that identifies the game; 

class Endgame {
public:
	// the Default constructor 
	Endgame() {
		ENTXT_SETUP();
		ENTXTINP_SETUP();
		SUBBTTN_SETUP();
		WaveTxt_SETUP();
		ScoreTxt_SETUP();
		Score_SETUP();
		WaveTxt_SETUP(); 
		Wave_SETUP(); 
	}
	//D
	std::string getINPVAR() {
		return userInput; 
	}
	void getUserInp(sf::Event eventVar) {
		
		if (eventVar.type == eventVar.TextEntered) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Delete)) {
				userInput = "";
			}
			else {
				if (userInput.size() <= 20) {
					userInput += eventVar.text.unicode;
				}
				else {
					printf("\n[STRING MAX SIZE REACHED]\n");
				}
			} // ENDIF 
		}//ENDIF 
	}//ENDPROCEDURE
	void saveStatsToDB(Gamestats& cElem, bool& on_engamescreen) {
		SQLCL SQLC;
		SQLC.displayDB();
		SQLC.Create_Table(SQLC.gettblname());
		SQLC.add_DATA(SQLC.gettblname(), cElem);
		on_engamescreen = false;
	}
	void DrawEndgame(sf::RenderWindow& window, int mousepos [2], Arcade& A , bool& on_engamescreen , Gamestats& GStat) {
		
			for (typeX cElem : ScreenElementVec) {
				if (cElem.type == "BTTN") {
					buttons bttnX({(double)cElem.size[0], (double)cElem.size[1]}, cElem.pos,cElem.borderColour,cElem.borderColour,false ,window,cElem.name ,mousepos,cElem.bodycolour );
					if (bttnX.getLaunchEvent() == false) {
						GStat.usrname = userInput; 
						saveStatsToDB( GStat , on_engamescreen );
					}
					
				}
				else if (cElem.type == "TXT") {
					sf::Color RTC  [2] = {cElem.bodycolour,cElem.borderColour};
					sf::Color RTBC [2] = {cElem.borderColour,cElem.borderColour};
					int RTBTH      [2] = {cElem.Bthick,cElem.Bthick};
					int RTSI[2] = { cElem.size[0] , cElem.size[1] };
					int RTPO[2] = { cElem.pos[0] , cElem.pos[1] };
					tools::DrawText::DrawTextWRect txtX(window, RTSI,RTPO, 24,RTC,RTBC, sf::Color::Cyan, RTBTH, cElem.name);
				}
				else if (cElem.type == "INP"){
					cElem.name =  userInput;
					sf::Color RTC[2] = { cElem.bodycolour,sf::Color::Blue };
					sf::Color RTBC[2] = { cElem.borderColour,cElem.borderColour };
					int RTBTH[2] = { cElem.Bthick,cElem.Bthick };
					int RTSI[2] = { cElem.size[0] , cElem.size[1] };
					int RTPO[2] = { cElem.pos[0] , cElem.pos[1] };
					tools::DrawText::DrawTextWRect txtX(window, RTSI, RTPO, 20, RTC, RTBC, sf::Color::Cyan, RTBTH, cElem.name);
				}
				else if (cElem.type == "SCORE") {
					cElem.name = std::to_string(A.getScorePlayer());
					sf::Color RTC[2] = { cElem.bodycolour,sf::Color::White };
					sf::Color RTBC[2] = { cElem.borderColour,cElem.borderColour };
					int RTBTH[2] = { cElem.Bthick,cElem.Bthick };
					int RTSI[2] = { cElem.size[0] , cElem.size[1] };
					int RTPO[2] = { cElem.pos[0] , cElem.pos[1] };
					tools::DrawText::DrawTextWRect txtX(window, RTSI, RTPO, 50, RTC, RTBC, sf::Color::Cyan, RTBTH, cElem.name);
				}
				else if (cElem.type == "WAVE") {
					cElem.name = std::to_string(A.getWaveNum());
					sf::Color RTC[2] = { cElem.bodycolour,sf::Color::White };
					sf::Color RTBC[2] = { cElem.borderColour,cElem.borderColour };
					int RTBTH[2] = { cElem.Bthick,cElem.Bthick };
					int RTSI[2] = { cElem.size[0] , cElem.size[1] };
					int RTPO[2] = { cElem.pos[0] , cElem.pos[1] };
					tools::DrawText::DrawTextWRect txtX(window, RTSI, RTPO, 50, RTC, RTBC, sf::Color::Cyan, RTBTH, cElem.name);

				}
				else {
					printf("\n[UNRECOGNISED TYPE]\n");
				}
				//endif
			}
			//endfor
		}
		//endfor 
	
	
	//end procedure 
private: 
	
	// sf::Color 

	void ENTXT_SETUP() {
		std::vector<int> Size = {450,50};
		std::vector<int> pos  = {550,50};
		std::string type = "INP";
		std::string name = "";
		sf::RectangleShape objx;
		sf::Color bodycolour = sf::Color::White;
		sf::Color borderColour; sf::Color::Red;
		int Bthick = 5;
		typeX VX = { type,name,Size,pos,objx,bodycolour,borderColour,Bthick };
		ScreenElementVec.emplace_back(VX);
 	}
	void ENTXTINP_SETUP() {
		std::vector<int> Size = { 350,50 };
		std::vector<int> pos = { 150,50 };
		std::string type = "TXT";
		std::string name = "INPUT YOUR NAME";
		sf::RectangleShape objx;
		sf::Color bodycolour=   sf::Color::Yellow;
		sf::Color borderColour= sf::Color::Black;
		int Bthick = 5;
		typeX VX = { type,name,Size,pos,objx,bodycolour,borderColour,Bthick };
		ScreenElementVec.push_back( VX );
	}
	void SUBBTTN_SETUP() {
		std::vector<int> Size = { 350,50 };
		std::vector<int> pos = { 150,100 };
		std::string type = "BTTN";
		std::string name = "SUBMIT YOUR NAME";
		sf::RectangleShape objx;
		sf::Color bodycolour = sf::Color::Yellow;
		sf::Color borderColour = sf::Color::Blue;
		int Bthick = 0;
		typeX VX = { type,name,Size,pos,objx,bodycolour,borderColour,Bthick };
		ScreenElementVec.push_back(VX);
	}
	void WaveTxt_SETUP() {
		std::vector<int> Size = { 350,100 };
		std::vector<int> pos = { 200,250 };
		std::string type = "TXT";
		std::string name = "WAVE NUMBER REACHED";
		sf::RectangleShape objx;
		sf::Color bodycolour = sf::Color::Green;
		sf::Color borderColour = sf::Color::Black;
		int Bthick = 0 ;
		typeX VX = { type,name,Size,pos,objx,bodycolour,borderColour,Bthick };
		ScreenElementVec.push_back(VX);
	}
	void Wave_SETUP() {
		std::vector<int> Size = {350,150};
		std::vector<int> pos  = {200,350};
		std::string type = "WAVE";
		std::string name = "";
		sf::RectangleShape objx;
		sf::Color bodycolour = sf::Color::Black;
		sf::Color borderColour = sf::Color::Yellow;
		int Bthick = 2;
		typeX VX = { type,name,Size,pos,objx,bodycolour,borderColour,Bthick };
		ScreenElementVec.push_back(VX);
	}
		
	
	void Score_SETUP() {
		std::vector<int> Size = {350,150};
		std::vector<int> pos = {560,350};
		std::string type = "SCORE";
		std::string name = "";
		sf::RectangleShape objx;
		sf::Color bodycolour = sf::Color::Black;
		sf::Color borderColour = sf::Color::Yellow;
		int Bthick = 2;
		typeX VX = { type,name,Size,pos,objx,bodycolour,borderColour,Bthick };
		ScreenElementVec.push_back(VX);
		
	}
	void ScoreTxt_SETUP() {
		std::vector<int> Size = { 350,100 };
		std::vector<int> pos = { 560,250 };
		std::string type = "TXT";
		std::string name = "SCORE";
		sf::RectangleShape objx;
		sf::Color bodycolour = sf::Color::Green;
		sf::Color borderColour = sf::Color::Blue;
		int Bthick = 2;
		typeX VX = { type,name,Size,pos,objx,bodycolour,borderColour,Bthick };
		ScreenElementVec.push_back(VX);
	//	ScreenElementVec.emplace_back(type, name, Size, pos, objx);
	}
	void GameTITLE_SETUP() {
		std::vector<int> Size = {2,2};
		std::vector<int> pos = {3,3};
		std::string type = "GMETTL";
		std::string name = "";
		sf::RectangleShape objx;
		sf::Color bodycolour = sf::Color::Green;
		sf::Color borderColour = sf::Color::Black;
		int Bthick = 0;
		typeX VX = { type,name,Size,pos,objx,bodycolour,borderColour,Bthick };
		ScreenElementVec.push_back(VX);
	//	ScreenElementVec.emplace_back(type, name, Size, pos, objx);
	}
	// THE ATTRIBUTES : 
	std::string UserName;  // holds the users name // 
	std::vector < typeX> ScreenElementVec = {}; // holds the sizes and positions of the onscreen elements 
	// parameters:  defined by my custom data structor named typeX 
	// parent   - string literal, to identify to what it corrosponds to; 
	// Size     - array that contains the size of the element ; 
	// position - array that holds the position of the element; 
	//
	std::string userInput; 
	sf::Text userText; 
	
};