#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include<iostream>
#include<vector>
#include<string>
#include "ToolsCl.h"
#include "Butttons.h"
#include "scaler.h"


class mainMenu {
public:
    tools tls;

    mainMenu() {
        //[2770 , 187] <-- top right corner of window  --> [72% of screen , 8.66% of screen]
        background_contSETUP();
        Button_divider1SETUP();
        Button_divider2SETUP();
        TitleSETUP();
    }
    // container containing background 
    void drawMainMenu(sf::RenderWindow& window) {

        window.draw(backgroundcont);
       // std::cout << "main background cont POS --> [" 
       //     << backgroundcont.getPosition().x 
       //     <<" , " 
       //    << backgroundcont.getPosition().y 
       //     << "]\n";
        window.draw(buttonDivider_1);
        window.draw(buttonDivider_2);
        window.draw(titleCont);
        
        //window.draw();
    }
    
private:

    sf::Texture TitleTexture;
    sf::Texture LogoTexture;
    sf::Sprite titleCont;
    sf::Sprite logo;
    sf::RectangleShape backgroundcont;
    sf::RectangleShape buttonDivider_1;
    sf::RectangleShape buttonDivider_2;
    void background_contSETUP() {
        //
        int Xsize = tls.windowSizeX * 0.88;
        int Ysize = tls.windowSizeY * 0.60;
        int Xpos = tls.windowSizeX * 0.05;
        int Ypos = tls.windowSizeY * 0.0266;
        int Thickness = tls.windowSizeY * 0.005;
        //
        backgroundcont.setFillColor(sf::Color::Black);
        backgroundcont.setPosition(sf::Vector2f(Xpos, Ypos));
        backgroundcont.setSize(sf::Vector2f(Xsize, Ysize));
        backgroundcont.setOutlineColor(sf::Color::White);
        backgroundcont.setOutlineThickness(Thickness);
    }
    void Button_divider1SETUP() {
        //
        int Xpos = tls.windowSizeX * 0.05;
        int Ypos = tls.windowSizeY * 0.68;
        int Xsize = tls.windowSizeX * 0.88;
        int Ysize = tls.windowSizeY * 0.03;
        //
        buttonDivider_1.setFillColor(sf::Color::Cyan);
        buttonDivider_1.setPosition(sf::Vector2f(Xpos, Ypos));
        buttonDivider_1.setSize(sf::Vector2f(Xsize, Ysize));
    }
    void Button_divider2SETUP() {
        //
        int Xpos = tls.windowSizeX * 0.05;
        int Ypos = tls.windowSizeY * 0.89;
        int Xsize = tls.windowSizeX * 0.88;
        int Ysize = tls.windowSizeY * 0.03;
        //
        buttonDivider_2.setFillColor(sf::Color::Cyan);
        buttonDivider_2.setPosition(sf::Vector2f(Xpos, Ypos));
        buttonDivider_2.setSize(sf::Vector2f(Xsize, Ysize));
    }
    void TitleSETUP() {
        // titleCont.setSize(sf::Vector2f(tls.windowSizeX*0.2,tls.windowSizeY*0.167));
        titleCont.setPosition(sf::Vector2f(tls.windowSizeX * 0.35, tls.windowSizeY * 0.042));
        TitleTexture.loadFromFile("Assets/SI2.png");
        TitleTexture.setSmooth(true);
        titleCont.setTexture(TitleTexture);
        scaleImage titleScale(titleCont.getScale().x, titleCont.getScale().y,tls.screen_res,2);
        titleCont.setScale(sf::Vector2f(titleScale.Scalewidth,titleScale.Scaleheight));
    }
    sf::Texture background;
    int bcontPosX;
    int bcontPosY;
    
};
//
//  ------------- main menu Buttons -------------------------------------------------------------------------//
//
class Mbuttons : mainMenu {
    //[305 , 582]  15.89 % of the screen width, 53.94% of the screen height
public:
    Mbuttons() {
        GamemodesBSETUP();
        ScoreboardBSETUP();
        ExitGameBSETUP(); 
       // QuickGameSETUP();
    }
    
    void DrawButtons(sf::RenderWindow& window,int mousepos[2]) {
        if (loop == true) {
            buttons GamemodesB(Bsize, BPositions[0], colour, borderColor, false, window, "Gamemodes\n", mousepos,fontColour);
            buttons ScoreboardB(Bsize, BPositions[1], colour, borderColor, false, window, "scoreBoard\n", mousepos, fontColour);
            buttons ExitGameB(Bsize, BPositions[2], colour, borderColor, false, window, "ExitGame\n", mousepos, fontColour);
            MenuButtons[0] = GamemodesB;
            MenuButtons[1] = ScoreboardB;
            MenuButtons[2] = ExitGameB;
            if (GamemodesB.getLaunchEvent() == false) {
                loop = false;
                tls.clearScreen(window);
                buttonlaunch = "G";
            }
            if (ScoreboardB.getLaunchEvent() == false)
            {
                loop = false;
                tls.clearScreen(window);
                buttonlaunch = "S";
            }
            if (ExitGameB.getLaunchEvent() == false) {
                loop = false;
                tls.clearScreen(window);
                buttonlaunch = "E";
            }
        }     
       // GamemodesB.checkMousePositions();
    }
    std::string buttonlaunch = "";
    int loop = true;
private:
    
    void GamemodesBSETUP() {
        int Xpos = tls.windowSizeX * 0.05; 
        int Ypos = tls.windowSizeY * 0.720;
        BPositions[0] = { Xpos,Ypos };
    }
    void ScoreboardBSETUP() {
        int Xpos = tls.windowSizeX * 0.30;
        int Ypos = tls.windowSizeY * 0.720;
        BPositions[1] = { Xpos,Ypos };
    }
    void ExitGameBSETUP() {
        int Xpos = tls.windowSizeX * 0.55;
        int Ypos = tls.windowSizeY * 0.720;
        BPositions[2] = { Xpos,Ypos };
       
    }
    sf::Color fontColour = sf::Color::Yellow;
    sf::Color colour = sf::Color::Black;
    sf::Color borderColor = sf::Color::White;
    std::vector<double> Bsize = { tls.windowSizeX * 0.2, tls.windowSizeX * 0.089 };
    std::vector<std::vector<int>> BPositions = { {},{},{} };// postitions x,y of buttons stored in order : gamemodes ,scoreboard, exitgame, 
    buttons MenuButtons[3];

      
};



