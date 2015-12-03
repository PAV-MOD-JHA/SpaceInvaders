#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include <stdexcept>
#include <cstdlib>
#include "Ship.h"
#include "Alien.h"
#include "Boss.h"
#include "Bullet.h"
#include "WinScreen.h"
#include "LoseScreen.h"
#include "CollisionManager.h"
#include "SoundManager.h"

using namespace std;

#define WIDTH 800
#define HEIGHT 600
#define NUMBER_OF_ALIENS_PER_LINE 7
#define NUMBER_OF_LINES 4

int main(int, char *argv[]) {

    const float shipSpeed = 200.f;
    const int alienMaxSpeed = 1200;
    const int alienMinSpeed = 500;
    const int difficulty = 3;
    const float bulletSpeed = 10.f;
    bool gameOver=false;
    bool winner = false;
    int moveDown=2;
    int globalDirection = +1;
	int bossDirection = +1;


    //initialize random seed
    srand (time(NULL));

    // Create the main window
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Space Invaders");
    window.setVerticalSyncEnabled(true);

    //start background music
    SoundManager music;
    music.playBackgroundMusic();

    //create background
    sf::Sprite back;
    sf::Texture star;

    // Load background to display
    if(!star.loadFromFile("resources/stars.png"))
        throw invalid_argument("Background not found!");
    //create sprite and scale
    back.setTexture(star);

    //create win and lose screens
    WinScreen win;
    LoseScreen lose;

    //create a bullet
    Bullet bullet(0,bulletSpeed);

    //create the ship
    Ship myShip(0,shipSpeed);
    myShip.setLocation(WIDTH/2 - myShip.getSprite().getGlobalBounds().height/2, HEIGHT - myShip.getSprite().getGlobalBounds().height-20);

    //create a an array of Aliens
    Alien alienArray[NUMBER_OF_LINES][NUMBER_OF_ALIENS_PER_LINE];
    for(int i=0; i<NUMBER_OF_LINES; i++) {
        for(int j=0; j<NUMBER_OF_ALIENS_PER_LINE; j++) {
            Alien alien(i, j, alienMinSpeed);
            alien.setLocation(j * 50 + 150, alien.getSprite().getGlobalBounds().height / 2 + i*50);
            alienArray[i][j] = alien;
        }
    }

	// Create a Boss
	Boss Boss(0, alienMinSpeed);
	Boss.setLocation(WIDTH/2, Boss.getSprite().getGlobalBounds().height / 2);

    //main clock for fps
    sf::Clock clock;

    //clock for aliens
    sf::Clock alienClock;
    alienClock.restart().asSeconds();

	//clock for Boss
	sf::Clock BossClock;
	BossClock.restart().asSeconds();

    //clock for bullet
    sf::Clock bulletClock;
    bulletClock.restart().asSeconds();

    // Start the game loop
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {

            // Close window : exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Close window : exit
            if (event.type == sf::Event::MouseButtonPressed) {
                if (gameOver) {
                    // (re)start the game
                    gameOver = false;
                    winner=false;
                    moveDown=2;
                    clock.restart();

                    //reset aliens
                    for(int i=0; i<NUMBER_OF_LINES; i++) {
                        for(int j=0; j<NUMBER_OF_ALIENS_PER_LINE; j++) {
                            Alien alien(i, j, alienMinSpeed);
                            alien.setLocation(j * 50 + 150, alien.getSprite().getGlobalBounds().height / 2 + i*50);
                            alienArray[i][j] = alien;
                        }
                    }

					//reset Boss location
					Boss.setLocation(WIDTH / 2, Boss.getSprite().getGlobalBounds().height / 2);

                    //reset ship location
                    myShip.setLocation(WIDTH/2, HEIGHT - myShip.getSprite().getGlobalBounds().height);
                    myShip.respawn();

                    //restart music
                    music.playBackgroundMusic();
                }
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                if(!bullet.isAlive() && !gameOver) {
                    bullet.spawn(true);
                    bullet.setLocation(myShip.getSprite().getPosition().x+13,myShip.getSprite().getPosition().y-10);
                    music.playLazer();
                }
            }

            // Escape pressed : exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }

        // Clear screen
        window.clear(sf::Color(0,0,0,255));
        window.draw(back);

        //check for movement of ship
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right) {
            if (myShip.getSprite().getPosition().x + myShip.getSprite().getGlobalBounds().width < WIDTH) {
                myShip.getSprite().move(shipSpeed * deltaTime, 0.f);
            }
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left) {
            if(myShip.getSprite().getPosition().x > 0.f) {
                myShip.getSprite().move(-shipSpeed * deltaTime, 0.f);
            }
        }

        //move aliens
        sf::Time t = alienClock.getElapsedTime();
        if(t.asSeconds() > 1/log2(moveDown)) {
            for (int j = 0; j < NUMBER_OF_ALIENS_PER_LINE; j++) {
                for (int i = 0; i < NUMBER_OF_LINES; i++) {
                    alienArray[i][j].getSprite().move((alienMaxSpeed + alienMinSpeed*difficulty) * globalDirection * deltaTime, 0.f);
                }
                alienClock.restart();
            }
        }

        // Get furthest alien ID on the side (left or right)
        int lastAliveRight = 0;
        int lastAliveLeft = NUMBER_OF_ALIENS_PER_LINE-1;
        int lastAliveLine = 0;
        if (globalDirection == 1) {
            for (int j = NUMBER_OF_ALIENS_PER_LINE - 1; j > lastAliveRight-1; j--) {
                for (int i = 0; i < NUMBER_OF_LINES; i++) {
                    if (alienArray[i][j].isAlive()) {
                        lastAliveRight = j;
                        lastAliveLine = i;
                    }
                }
            }
        }
        else if (globalDirection == -1) {
            for (int j = 0; j <= lastAliveLeft; j++) {
                for (int i = 0; i < NUMBER_OF_LINES; i++) {
                    if (alienArray[i][j].isAlive() ) {
                        lastAliveLeft = j;
                        lastAliveLine = i;
                    }
                }
            }
        }

        //test collisions between aliens and borders of the screen
        if (alienArray[lastAliveLine][lastAliveRight].getSprite().getPosition().x + alienArray[lastAliveLine][lastAliveRight].getSprite().getGlobalBounds().width > WIDTH-50 && alienArray[lastAliveLine][lastAliveRight].isAlive()) {
            globalDirection = -1 * globalDirection ;
            moveDown += 0.5;
            for (int k = 0; k < NUMBER_OF_ALIENS_PER_LINE; k++) {
                for (int l = 0; l < NUMBER_OF_LINES; l++) {
                    alienArray[l][k].getSprite().move((alienMaxSpeed + alienMinSpeed*difficulty) * globalDirection * deltaTime, 30);
                }
            }
        }
        if (alienArray[lastAliveLine][lastAliveLeft].getSprite().getPosition().x < 50 && alienArray[lastAliveLine][lastAliveLeft].isAlive()) {
            globalDirection = -1 * globalDirection ;
            moveDown += 0.5;
            for (int k = 0; k < NUMBER_OF_ALIENS_PER_LINE; k++) {
                for (int l = 0; l < NUMBER_OF_LINES; l++) {
                    alienArray[l][k].getSprite().move((alienMaxSpeed + alienMinSpeed*difficulty) * globalDirection * deltaTime, 30);
                }
            }
        }

        // Fire bullet
        sf::Time bc = bulletClock.getElapsedTime();
        if(bc.asSeconds() > 1.0) {
            if(bullet.isAlive() && !gameOver) {
                //draw bullet
                bullet.draw(window);
                //move bullet
                bullet.getSprite().move(0.f,-20);
            }
        }

        //test collisions between aliens and ship
        for(int i=0; i<NUMBER_OF_LINES; i++) {
            for(int j=0; j<NUMBER_OF_ALIENS_PER_LINE; j++) {
                if (CollisionManager::collidesWith(myShip, alienArray[i][j]) && alienArray[i][j].isAlive()) {
                    if (!gameOver) {
                        music.playExplosion();
                    }
                    myShip.kill();
                    winner = false;
                    gameOver = true;
                }
            }
        }

        //test collisions between aliens and bottom of screen
        for(int i=0; i<NUMBER_OF_LINES; i++) {
            for(int j=0; j<NUMBER_OF_ALIENS_PER_LINE; j++) {
                if(alienArray[i][j].getSprite().getPosition().y+alienArray[i][j].getSprite().getGlobalBounds().height>HEIGHT && alienArray[i][j].isAlive()) {
                    if (!gameOver) {
                        music.playExplosion();
                    }
                    winner = false;
                    gameOver = true;
                }
            }
        }

        //test collisions between bullet and aliens
        for(int i=0; i<NUMBER_OF_LINES; i++) {
            for(int j=0; j<NUMBER_OF_ALIENS_PER_LINE; j++) {
                if (CollisionManager::collidesWith(bullet, alienArray[i][j]) && alienArray[i][j].isAlive() && bullet.isAlive()) {
                    music.playExplosion();
                    alienArray[i][j].kill();
                    bullet.kill();
                }
            }
        }

        //test for a winner
        int deadAliens=0;
        for(int i=0; i < NUMBER_OF_LINES; i++) {
            for (int j = 0; j < NUMBER_OF_ALIENS_PER_LINE; j++) {
                if (!alienArray[i][j].isAlive()) {
                    deadAliens++;
                }
                if (deadAliens == NUMBER_OF_ALIENS_PER_LINE*NUMBER_OF_LINES && (Boss.isAlive()==false || Boss.isActivated() == false)) {
                    if (!gameOver) {
                        //music.playReward();
                        winner = true;
                    }
                    gameOver = true;
                }
            }
        }

        //test collision with bullet and boundary
        if(bullet.getSprite().getPosition().y < 0) {
            bullet.kill();
        }

		//>>> Boss Collisions and movement <<<
		// activate boss
		if (t.asSeconds() > 0,5 && Boss.isActivated()== false) {
			for (int j = 0; j < NUMBER_OF_ALIENS_PER_LINE; j++) {
				if (alienArray[0][j].getSprite().getPosition().y > 100) {
					Boss.activate();
				}
			}
		}

		//Move Boss -- bouge tout les 1/ln(int aléatoire entre 1 et 10)
		sf::Time tb = BossClock.getElapsedTime();
		if (tb.asSeconds() > 1/(log2(rand()%(9)+1)) ){
			Boss.getSprite().move((alienMaxSpeed + alienMinSpeed*difficulty) * bossDirection * deltaTime, 0.f);
			BossClock.restart();
		}

		// test collisions Between boss and borders of the screen
		if (Boss.isAlive() && Boss.isActivated() &&  (Boss.getSprite().getPosition().x +Boss.getSprite().getGlobalBounds().width > WIDTH - 50 || Boss.getSprite().getPosition().x < 20) ) {
			bossDirection = -1 * bossDirection;
			Boss.getSprite().move((alienMaxSpeed + alienMinSpeed*difficulty) * bossDirection * deltaTime, 0);
		}
	
		// test collisions between boss and bullets


        //draw to screen
        if(!gameOver) {
            for(int i=0; i<NUMBER_OF_LINES; i++) {
                for(int j=0; j<NUMBER_OF_ALIENS_PER_LINE; j++) {
                    if (alienArray[i][j].isAlive()) {
                        alienArray[i][j].draw(window);
                    }
                }
            }

            if(myShip.isAlive()) {
                //draw ship
                myShip.draw(window);
            }

			if (Boss.isAlive() && Boss.isActivated()) {
				//draw Boss
				Boss.draw(window);
			}

            // Update the window
            window.display();
        }
        else {
            music.pauseBackgroundMusic();
            if(winner) {
                win.draw(window);
            }
            else {
                lose.draw(window);
            }

            // Update the window
            window.display();
        }

    }

        return EXIT_SUCCESS;
}
