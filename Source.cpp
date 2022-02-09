#include <iostream>
#include<vector>
#include "globals.h"
#include "SFML/Graphics.hpp"
#include "missiles.h"

using namespace std;

int main() {
    //game set up (you'll need these lines in every game)
    sf::RenderWindow screen(sf::VideoMode(800, 800), "Bullet Hell"); //set up screen
    sf::Event event; //set up event queue
    sf::Clock clock; //set up the clock (needed for game timing)
    const float FPS = 60.0f; //FPS
    screen.setFramerateLimit(FPS); //set FPS



    //player setup------------------------------------------------
    sf::Texture ship;
    ship.loadFromFile("ship.png");
    sf::IntRect playerImg(0, 0, 30, 30); //select portion of image to draw (our ship is 30x30)
    sf::Sprite player(ship, playerImg);
    // player.setTexture(ship); //use this instead of 2 lines above for static images
    int xpos = 400;
    int ypos = 700;
    int vx = 0;
    int vy = 0;
    player.setPosition(xpos, ypos); //top left "corner" of circle (not center!)
    bool keys[] = { false, false, false, false, false };




    int justshot = 0;

    sf::Texture MissileImg;
    MissileImg.loadFromFile("missile.png");
    sf::Sprite MissilePic;
    MissilePic.setTexture(MissileImg);

    vector<missile*> missiles;
    vector<missile*>::iterator iter2;
    for (int i = 0; i < 5; i++) {
        missile* newMissile = new missile(xpos, ypos, MissilePic);
        missiles.push_back(newMissile);
    }


    //################### HOLD ONTO YOUR BUTTS, ITS THE GAME LOOP###############################################################
    while (screen.isOpen()) {//keep window open until user shuts it down

        while (screen.pollEvent(event)) { //look for events-----------------------

            //this checks if the user has clicked the little "x" button in the top right corner
            if (event.type == sf::Event::EventType::Closed)
                screen.close();

            //KEYBOARD INPUT 
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                keys[LEFT] = true;
            }
            else keys[LEFT] = false;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                keys[RIGHT] = true;
            }
            else keys[RIGHT] = false;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                keys[UP] = true;
            }
            else keys[UP] = false;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                keys[DOWN] = true;
            }
            else keys[DOWN] = false;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                keys[SPACE] = true;
            }
            else
                keys[SPACE] = false;


        }//end event loop---------------------------------------------------------------
        justshot++;
        if (keys[SPACE] == true) {
            for (iter2 = missiles.begin(); iter2 != missiles.end(); iter2++) {
                if (((*iter2)->isalive()) == false && justshot > 5) {
                    (*iter2)->shoot(xpos, ypos);
                    justshot = 0;
                }
            }
        }
        for (iter2 = missiles.begin(); iter2 != missiles.end(); iter2++) {
            if ((*iter2)->isalive()) {
                (*iter2)->move();
                cout << "Is Alive\n";
            }
        }

        for (iter2 = missiles.begin(); iter2 != missiles.end(); iter2++) {
            if ((*iter2)->offscreen())
                (*iter2)->kill();
        }
         //move ship
        if (keys[LEFT] == true)
            vx = -5;

        else if (keys[RIGHT] == true)
            vx = 5;

        else vx = 0;
        xpos += vx;
        player.setPosition(xpos, ypos);

        if (keys[UP] == true)
            vy = -5;

        else if (keys[DOWN] == true)
            vy = 5;

        else vy = 0;
        ypos += vy;
        player.setPosition(xpos, ypos);

        int ticker = 60;
        int frameNum = 0;
        int direction = RIGHT;

        ticker += 1;

        if (ticker % 10 == 0)
            frameNum += 1;

        if (frameNum > 4)
            frameNum = 0;

        if (direction == RIGHT) {
            playerImg = sf::IntRect((frameNum + 5) * 32, 0, 30, 30);
        }
        else if (direction == LEFT) {
            playerImg = sf::IntRect((frameNum + 5) * 32, 0, -30, 30);
            cout << "left" << frameNum + 5;
        }
        else {
            playerImg = sf::IntRect(frameNum * 32, 0, 30, 30);
        }
       
        playerImg = sf::IntRect(frameNum * 32, 0 , 30, 30);
        sf::Sprite player(ship, playerImg);
        player.setPosition(xpos, ypos);


        //render section-----------------------------------------
        screen.clear(); //wipes screen, without this things smear
        for (iter2 = missiles.begin(); iter2 != missiles.end(); iter2++) {
            (*iter2)->draw(screen);
        }

        screen.draw(player); //draw player
        screen.display(); //flips memory drawings onto screen

    }//######################## end game loop ###################################################################################

    cout << "goodbye!" << endl;
} //end of main