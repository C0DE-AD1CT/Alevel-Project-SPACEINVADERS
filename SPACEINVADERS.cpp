//started 10/09/2022 
//finished: 05/01/2023
//modified: 23/10/2023
// In depth detail given in development write-up 
// project start ------------------------
//[3839 , 2159] size of desktop screen
//[1919 , 1079] size of laptop  screen 
//----------------------------------------
//include Files
// 


#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Main.hpp"
#include<iostream>
#include<vector>
#include "ToolsCl.h"
#include "MM.h"
#include "ExitGame.h"
#include "Gamemodes.h"
#include "Arcade.h"
#include <thread>
#include"player.h"
#include "enemy.h"
#include"projectile.h"
#include "EndGame.h"
#include "Scoreboard.h"
#include <iostream>
#pragma


//----------------------------------------
//boolean operators 
 bool onMainmenu = true ; bool onScoreboard = false; bool onscoreboardSettings = false;
 bool onGameSettings = false; bool onArcade = false; bool onGamemodes = false;
 bool onExitGame = false; bool removeB = true;  bool ongameover = false; bool endgameScreen = false;
 //----------------------------------------
 //MousePosition Variable 
int mousePosition[2] = {};
//----------------------------------------
//general Class variables 
Endgame ES;tools tls;enemy E;mainMenu MM;Mbuttons MMB;ExitGame EG;gamemodes GM;Arcade A;
player P;Bullet B;projectile::playerP ProjP;projectile::enemy ProjE;Gamestats GStat;Table TBL; 
//----------------------------------------
//sfml Screen Context init var 
sf::Context context;
//----------------------------------------
//General player position var 
int playerPosition[]; 
//----------------------------------------
//Main Program Logic 
int main(int argc, char* argv[])
{
    int EnemyEliminated = 0;
     sf::RenderWindow window(sf::VideoMode(tls.windowSizeX,tls.windowSizeY), "spaceInvaders", sf::Style::Titlebar);
    window.setPosition(sf::Vector2i(tls.windowPosX,tls.windowPosY));
    window.setFramerateLimit(50);window.setMouseCursorVisible(false);// hides the mouse cursor 
    int mouseRectSize[2] = { tls.windowSizeY * 0.02,tls.windowSizeY * 0.02 };
    B.SetBullet(&window);
    //----------------------------------------
    //THE GAME LOOP// this loop constinues until window is closed 
    //----------------------------------------
    while (window.isOpen())
    {
        sf::Event event;
        //----------------------------------------
        //Getting users Mouse position  SECTION  
        //----------------------------------------
        tls.mousepos[0] = sf::Mouse::getPosition(window).x;tls.mousepos[1] = sf::Mouse::getPosition(window).y;
        mousePosition[0] = tls.mousepos[0]; mousePosition[1] = tls.mousepos[1];
      // std::cout << "\nMOUSE POS --> ["<< tls.mousepos[0] << " , " << tls.mousepos[1] << "]\n";
       E.setWindow(&window); // used to set the window variable in the enemies class
       //----------------------------------------
       // EVENT LOOP CAPTURE SECTION 
       //The pollEvent loop for SFML library  
       //----------------------------------------
        while (window.pollEvent(event))
        {
            if (endgameScreen) {
                ES.getUserInp(event);
            }
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.close();
            }
        else {

        }
        tls.clearScreen(window);
        //----------------------------------------
        //THE START OF THE SCREEN DETERMINATION SECTION 
        // BRANCHES: 
        // branch 1  : opening menu
        // branch 2  : gamemodes menu 
        // branch 3  : Exit-game menu 
        // branch 4  : Arcade 
        // branch 5  :  (not implemented )
        //----------------------------------------
        //MENU 1  : opening main-menu-screen logic  here 
        //
        if (onMainmenu == true) {
            //START OF OPENING MENU BRANCH // 
            MMB.buttonlaunch = "";
            window.draw(tls.background);
            MM.drawMainMenu(window);
            MMB.DrawButtons(window,tls.mousepos);
            //----------------------------------------
            // OPENING MENU COMMAND RESULT SECTION // 

            if (MMB.loop == false) {
                onMainmenu = false;

            }
            if (MMB.buttonlaunch == "G") {
                //GAMEMODES BUTTON BRANCH 
                onGamemodes = true;
                MMB.loop = true;
            }
            if (MMB.buttonlaunch == "S") {
                //SCOREBOARD BUTTON BRANCH 
                onScoreboard = true;
                MMB.loop = true;
            }
            if (MMB.buttonlaunch == "E") {
                //EXITGAME BRANCH 
                onExitGame = true;
                MMB.loop = true;
            }
            // OPENING MENU COMMAND RESULT SECTION END // 
            //----------------------------------------
        //END OF OPENING MENU BRANCH // 
        }
        //
        //MENU 1 SECTION END// 
        //----------------------------------------
        //----------------------------------------
        //SUBMENU 1 : ExitGame-screen logic 
        //
        else if (onExitGame == true) {         
            EG.drawButtons(window,tls.mousepos);
            if (EG.buttonlaunch =="M") {
                onMainmenu = true;
                onExitGame = false;
                EG.buttonlaunch = "";

            }
        }
        //----------------------------------------
        //SUBMENU 2  : Gamemodes-screen logic  
        else if (onGamemodes == true) {
           // std::cout << "[on gamemodes screen]";
            GM.drawScreen(window,tls.mousepos);
            GM.drawButtons(window, tls.mousepos);
            
            if (GM.buttonlaunch == "M") {
                onMainmenu = true;
                onGamemodes = false;
                GM.buttonlaunch = "";
                
            }
            if (GM.buttonlaunch == "A") {
                onArcade = true;
                onGamemodes = false;
                GM.buttonlaunch = "";
                
            }
            if (GM.buttonlaunch == "GS") {
                onGameSettings = true;
                onGamemodes = false;
                GM.buttonlaunch = "";

            }
        }
        //----------------------------------------
        //GAMEMODE 1: Arcade logic 
        else if (onArcade == true) {
            
            std::thread th1(&player::PlayerPosUpdate, &P);
            // Firing Projectile Section 
            if (ProjP.GetTimer() <=200 && P.getBulletFirePosSIZE() <= 1) {
                 if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && ProjP.GetTimer() <= 0) {
                     //start if 
                    ProjP.SetTimer(300);
                    //endif
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)  == true
                    || sf::Keyboard::isKeyPressed(sf::Keyboard::D) == true 
                    && P.playerPosition()[0] != P.PlayerOldPos[0][0] && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) 
                {
                    //startif 
                    P.PlayerOldPos.erase(P.PlayerOldPos.begin());
                    if (removeB == true) {
                        //P.clearBulletposArr();
                        std::thread clearArr(&player::clearBulletposArr,&P);
                        clearArr.join();
                    }
                    removeB = false;
                    //endif 
                }

                else if (ProjP.GetTimer() == 200) {
                    std::thread clearArr(&player::clearBulletposArr, &P);
                    clearArr.join();
                }
                else
                {
                    removeB = true; 
                }      
                
                P.FireBullet();
                ProjP.SetTimer(ProjP.GetTimer() - 100);   
            }
            // End of firing projectile section 
            std::vector<std::vector<int>> bulletXY = B.moveBullet(P.getBulletFirePos(), P.getBulletFirePosSIZE());
            std::thread B1(&player::SetBulletPositions, &P, bulletXY);
            
            A.drawArcade(window, tls.mousepos);     
            P.drawPlayer(window);
            P.DeleteBullet();
           //ENEMY SPAWN and INITIALISATION  SECTION 
           // 
           //Initialise the enemies if the enemy Num = 0 . This signifies that a new wave should begin 
           //Increment the wave if the enemy Num is 0
            if (E.getEnemyNum() <= 1) {
                E.RESET_EliminatedArr();
                A.SetWave();// increments the wave by 1; 
                std::thread EnemyCalcTh(&enemy::enemyNumCalc,&E,A.getWaveNum()); EnemyCalcTh.join();
                std::thread EnemyPositionsTh(&enemy::EnemyPositions,&E); 
                
 
                E.InitialiseEnemies();
                EnemyPositionsTh.join();
            }
            else {
                E.DisplayEnemies();
            }
            //SECTION END
            //----------------------------------------//
            //COLLISION DETECTION SECTION// 
            //----------------------------------------//
            // (This section will not be placed within a function )
            //SEC 1:
            int ERowNum = E.getEnemyRowNum(); // Variable holding the number of enemy rows retrieved from the enemy class 
            int count = 0; // variable that will be used to check the current enemy index. This is to prevent Index errors 
          //  std::cout << "Enemy Num: " << E.enemyNum << "\n";
            for (int RowX = 0; RowX < ERowNum && count < E.enemyNum; RowX++) { // loop one --> This loops through the rows 
            // a do while loop is needed for this 
            //this is because the repeated function calls end up resetting the variable. 
                int EnemyX = 0; 
                int count = 0;
                do {
                    if (E.getEnemyActiveState(RowX, EnemyX) == 0) {
                        //if statement that only performs the code if the active state is 0 which means active 
                         onArcade= A.EnemyPlayerCollision(E.getEnemySpriteHitbox(RowX, EnemyX), P.getPlayerBounds(),window ); // Checks for an enemy Collision 
                        EnemyEliminated = A.BulletEnemyCollision(E.getEnemySpriteHitbox(RowX, EnemyX), bulletXY, RowX, EnemyX, E,P); // Checks for a bullet collision, determining the Active state 
                        if (EnemyEliminated == 1) {
                            EnemyX = E.enemyNum; // Ensures the loop gets ended if a state is deactivated 
                        }
                    }
                    EnemyX++;
                    count++;
                } while (EnemyX < 4 && count < E.enemyNum && EnemyEliminated == 0);
               
            //endloop
            }
                
            bulletXY.clear();
            //
            if (EnemyEliminated == 0 ){
                B.drawBullet(P.getBulletFirePos(), P.getBulletFirePosSIZE());
            }
            else {
                P.clearBulletposArr();
                EnemyEliminated = 0;
               // ProjP.SetTimer(1500);// resets the variable 
                std::cout <<"timer"<< ProjP.GetTimer();
            }
            //Collision Detection Section End 
           B1.join();
           th1.join();
           
          //  std::cout << "GCON:" <<GcondE.checkWinConditon();
           if (onArcade == false) {
               endgameScreen = 1;
               GStat.scoreStr = std::to_string(A.getScorePlayer());
               GStat.wavenumStr = std::to_string(A.getWaveNum());
               GStat.usrname =  ES.getINPVAR();
           }
        }
        else if (endgameScreen == true) {
        
        ES.DrawEndgame(window,tls.mousepos,A,endgameScreen,GStat);
        }
        else if (onScoreboard == true ) {
        TBL.draw_Table(window);
            }
        else {
        printf("\n[ALERT! NO ACTIVE SCREEN]\n");
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Dash)) {
            std::cout << "\n[Keypress '-' initiated, returning to opening Menu]\n";
            onArcade = false;
            onGamemodes = false;
            onGameSettings = false;
            onScoreboard = false; 
            onExitGame = false; 
            onMainmenu = true;

        }
        
        //GAMEMODE 1 END // 
        // 
        //----------------------------------------
        //----------------------------------------
        // THE END  OF THE SCREEN DETERMINATION 
        // SECTION 
        //----------------------------------------
        //----------------------------------------
        //
        std::cout << "\t\n[1= true , 0 = false]"
            <<"\n[onGamemodes: " << onGamemodes 
            <<" ]\n[onExitGame: " << onExitGame 
            <<" ]\n[onArcade: " << onArcade 
            <<" ]\n[onMainmenu: "<< onMainmenu 
            <<" ]\n ==========================="; // to check which screen is currently active*/
        tools::DrawRect mouse(&window, mouseRectSize, tls.mousepos, sf::Color::Green, sf::Color::Yellow,1);
        window.display();

        //system("cls");
        
}

    
return 0;
}
