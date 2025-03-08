#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include<iostream>
#include<vector>
#include<string>


struct typeX {
    std::string type;
    std::string name;
    std::vector<int> size;
    std::vector<int> pos;
    sf::RectangleShape shapeX;
    sf::Color bodycolour;
    sf::Color borderColour;
    int Bthick; 
};
struct Gamestats {
    std::string date;
    std::string usrname;
    std::string scoreStr;
    std::string wavenumStr;
};


class tools {
public:
    tools() {
      //  screen_res.push_back(sf::VideoMode::getDesktopMode().width);
      //  screen_res.push_back(sf::VideoMode::getDesktopMode().height);
        windowSizeX = screen_res[0] * 0.6;
        windowSizeY = screen_res[1] * 0.6;
        windowPosX = screen_res[0] * 0.119;
        windowPosY = screen_res[1] * 0.066;
        sf::Color blue(0x114c8f);
        background.setSize(sf::Vector2f(windowSizeX, windowSizeY));
        background.setFillColor(sf::Color(blue));
        background.setPosition(sf::Vector2f(0, 0));
    }
    //variables //
    int windowSizeX;
    int windowSizeY;
    int windowPosX;
    int windowPosY;
    int mousepos[2] ={};
    std::vector<int> screen_res ={ 1919 , 1079 };
    sf::RectangleShape background;

    void clearScreen(sf::RenderWindow &window) {
        window.clear(sf::Color::Black); 
    }
    //CLASS FOR DRAWING TEXT 
    class DrawText {
    public:
        DrawText() {
        }
        DrawText(sf::RenderWindow& window, int position[2], int size, std::string text, 
            sf::Color Fontcolor, sf::Color backgroundColor,bool bold);
        //CLASS FOR DRAWING TEXT ENCAPSUATED BY A RECTANGLE
        class DrawTextWRect {
        //NESTED CLASS START 
        public:
            DrawTextWRect() {
                // default constructor start
                //default constructor end 
            }
            //Forward Declaration of Constructor 
            DrawTextWRect(sf::RenderWindow& window, int rectDim[2], int rectPos[2], int txtSize, sf::Color RectTxtColor[2]
                , sf::Color RectTxtBorderColor[2], sf::Color txtColor, int RecttxtBorderThick[2], std::string txt);
        private:
            // no private variables as of yet 
            //end of nested class 
        };
    private:
        sf::Font font;
        sf::Text Ftxt;
    };
    // CLASS FOR DRAWING RECTANGLES // 
    class DrawRect {
    public:
        DrawRect() {
        }
        DrawRect(sf::RenderWindow *window, int size[2], int pos[2], sf::Color backgroundColor, sf::Color borderColor, int thickness);
        int bounds[2][2];
    private:
        void setBounds() {
            int bound1_x = RectArea.getPosition().x+ RectArea.getSize().x;
            int bound2_x = RectArea.getPosition().x+ RectArea.getSize().x;
            int bound1_y = RectArea.getPosition().y+ RectArea.getSize().y;
            int bound2_y = RectArea.getPosition().y+ RectArea.getSize().y;
            bounds[0][0] = bound1_x;
            bounds[0][1] = bound2_x;
            bounds[1][0] = bound1_y;
            bounds[1][1] = bound2_y;
        }

        sf::RectangleShape RectArea; 
    };
private:
};
tools::DrawText::DrawText(sf::RenderWindow& window, int position[2],
        int size, std::string text, sf::Color fontcolor,
        sf::Color backgroundColor, bool bold) {
    sf::Font font;
    sf::Text Ftxt;
    if (!font.loadFromFile("Assets/fonts/arial_narrow_7.ttf"))
    {
        std::cout << "Font load error!\n";
    }
    Ftxt.setString(text);
    Ftxt.setFont(font);
    Ftxt.setPosition(position[0], position[1]);
    if (bold == true) {
        Ftxt.Bold;
    }
    Ftxt.setFillColor(backgroundColor);
    Ftxt.setCharacterSize(size);
    window.draw(Ftxt);
}
//construictor for drawing rectangle 
tools::DrawRect::DrawRect(sf::RenderWindow* window,int size[2], int pos[2], sf::Color backgroundColor, sf::Color borderColor, int thickness ) {
    RectArea.setSize(sf::Vector2f(size[0],size[1]));
    RectArea.setPosition(sf::Vector2f(pos[0], pos[1]));
    RectArea.move(sf::Vector2f(-(size[0])/2,-(size[1]/2)));
    RectArea.setFillColor(backgroundColor);
    RectArea.setOutlineThickness(thickness);
    RectArea.setOutlineColor(borderColor);
    setBounds();
    //sf::RenderWindow &win= *window;
    window->draw(RectArea);
}
//constructor for drawing text with rectangle 
tools::DrawText::DrawTextWRect::DrawTextWRect(sf::RenderWindow& window, int rectDim[2], int rectPos[2], int txtSize, sf::Color RectTxtColor[2]
    , sf::Color RectTxtBorderColor[2], sf::Color txtColor, int RecttxtBorderThick[2], std::string txt) {
    //To draw the rectangle is simple, we just call the  obkect constructor I made to do it for me 
    DrawRect::DrawRect(&window, rectDim, rectPos, RectTxtColor[0], RectTxtBorderColor[0], RecttxtBorderThick[0]);
    //Next I need to generate the text onto the screen 
    //to do this I just call the txt constructor I made 
    int txtPos[2] = {
        (rectPos[0] - rectDim[0]/4) , // working out the x position for the text
        (rectPos[1] - rectDim[1]/4)  // working out the y position for the text 
    };// we want the txt centered
    DrawText::DrawText(window, txtPos, txtSize, txt, txtColor, RectTxtColor[1], false);
    //endfunction
}