#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "Ship.h"
#include "Enemy.h"
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

int main()
{
    const float shipSpeed = 200.f;
    const int alienMaxSpeed = 1200;
    const int alienMinSpeed = 500;
    int alienDownSpeed = 2;
    const float bulletSpeed = 10.f;
    bool gameOver=false;
    bool winner = false;
    bool play = false;
    int globalDirection = +1;
    int difficulty = 1;

    // Create main window
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "HomeScreen");
    window.setVerticalSyncEnabled(true);

    //start background music
    SoundManager music;
    music.playBackgroundMusic();

    // Create background
    sf::Sprite back;
    sf::Texture star;

    // Load background to display
    if(!star.loadFromFile("resources/stars.png"))
        throw invalid_argument("Background not found!");
    //create sprite and scale
    back.setTexture(star);

    // Load a font from a file
    sf::Font font;
    if (!font.loadFromFile("resources/BebasNeue.otf"))
        throw invalid_argument("Font not found!");


    // ----------------------- CREATE HOMESCREEN ------------------------- //

    // Create strings
    sf::Text titleText;
    titleText.setFont(font);
    titleText.setString("Space Invaders");
    titleText.setCharacterSize(100);
    titleText.setColor(sf::Color::White);
    titleText.setPosition(WIDTH/2 - titleText.getLocalBounds().width/2, titleText.getLocalBounds().height - 20);

    sf::Text startText;
    startText.setFont(font);
    startText.setString("Start Game");
    startText.setCharacterSize(48);
    startText.setColor(sf::Color::White);
    startText.setPosition(180, HEIGHT-100);

    sf::Text exitText;
    exitText.setFont(font);
    exitText.setString("Exit Game");
    exitText.setCharacterSize(48);
    exitText.setColor(sf::Color::White);
    exitText.setPosition(450, HEIGHT-100);

    sf::Text difficultyText;
    difficultyText.setFont(font);
    difficultyText.setString("Choose difficulty");
    difficultyText.setCharacterSize(44);
    difficultyText.setColor(sf::Color::White);
    difficultyText.setPosition(50.f, 350.f);

    sf::Text difficulty0;
    difficulty0.setFont(font);
    difficulty0.setString("1");
    difficulty0.setCharacterSize(44);
    difficulty0.setColor(sf::Color::White);
    difficulty0.setPosition(350 + 50.f, 350.f);

    sf::Text difficulty1;
    difficulty1.setFont(font);
    difficulty1.setString("2");
    difficulty1.setCharacterSize(44);
    difficulty1.setColor(sf::Color::White);
    difficulty1.setPosition(425 + 50.f, 350.f);

    sf::Text difficulty2;
    difficulty2.setFont(font);
    difficulty2.setString("3");
    difficulty2.setCharacterSize(44);
    difficulty2.setColor(sf::Color::White);
    difficulty2.setPosition(500 + 50.f, 350.f);

    sf::Text difficulty3;
    difficulty3.setFont(font);
    difficulty3.setString("4");
    difficulty3.setCharacterSize(44);
    difficulty3.setColor(sf::Color::White);
    difficulty3.setPosition(575 + 50.f, 350.f);

    sf::Text difficulty4;
    difficulty4.setFont(font);
    difficulty4.setString("5");
    difficulty4.setCharacterSize(44);
    difficulty4.setColor(sf::Color::White);
    difficulty4.setPosition(650 + 50.f, 350.f);

    sf::RectangleShape difficultyOutline;
    difficultyOutline.setSize(sf::Vector2f(50, 50));
    difficultyOutline.setOutlineColor(sf::Color::White);
    difficultyOutline.setFillColor(sf::Color::Transparent);
    difficultyOutline.setOutlineThickness(5);
    difficultyOutline.setPosition(385, 354.f);

    // Create gameover screens
    WinScreen win;
    LoseScreen lose;

    // ----------------------- CREATE ALIENS AND SPACESHIP ------------------------- //

    // Create a bullet
    Bullet bullet(0,bulletSpeed);

    // Create the ship
    Ship myShip(0,shipSpeed);
    myShip.setLocation(WIDTH/2 - myShip.getSprite().getGlobalBounds().height/2, HEIGHT - myShip.getSprite().getGlobalBounds().height-20);

    // Create an array of an array of enemys
    Enemy alienArray[NUMBER_OF_LINES][NUMBER_OF_ALIENS_PER_LINE];
    for(int i=0; i<NUMBER_OF_LINES; i++) {
        for(int j=0; j<NUMBER_OF_ALIENS_PER_LINE; j++) {
            Enemy alien(i, j, alienMinSpeed);
            alien.setLocation(j * 50 + 150, alien.getSprite().getGlobalBounds().height / 2 + i*50);
            alienArray[i][j] = alien;
        }
    }

    // ----------------------- CREATE MULTIPLE CLOCKS ------------------------- //

    // Main clock for fps
    sf::Clock clock;

    // Clock for alien movement
    sf::Clock alienClock;
    alienClock.restart().asSeconds();

    // Clock for bullet
    sf::Clock bulletClock;
    bulletClock.restart().asSeconds();

    // ----------------------- START GAME LOOP ------------------------- //

    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                play=false;
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                if (!bullet.isAlive() && !gameOver && play) {
                    bullet.spawn(true);
                    bullet.setLocation(myShip.getSprite().getPosition().x + 13, myShip.getSprite().getPosition().y - 10);
                    music.playLazer();
                }
            }

        }

        window.clear();
        window.draw(back);

        // If not ready to play
        if (!play) {
            // Get cursor position
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

            // Click on Start
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mousePosition.x > startText.getPosition().x &&
                mousePosition.x < startText.getPosition().x + startText.getLocalBounds().width &&
                mousePosition.y > startText.getPosition().y &&
                mousePosition.y < startText.getPosition().y + startText.getLocalBounds().height) {
                play = true;
            }
            // Click on Exit
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mousePosition.x > exitText.getPosition().x &&
                mousePosition.x < exitText.getPosition().x + exitText.getLocalBounds().width &&
                mousePosition.y > exitText.getPosition().y &&
                mousePosition.y < exitText.getPosition().y + exitText.getLocalBounds().height) {
                window.close();
            }

            // Choose difficulty
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mousePosition.x > difficulty0.getPosition().x - 5 &&
                mousePosition.x < difficulty0.getPosition().x + difficulty0.getLocalBounds().width + 5 &&
                mousePosition.y > difficulty0.getPosition().y - 5 &&
                mousePosition.y < difficulty0.getPosition().y + difficulty0.getLocalBounds().height + 5) {
                difficultyOutline.setPosition(385, 354.f);
                difficulty = 1;
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mousePosition.x > difficulty1.getPosition().x - 5 &&
                mousePosition.x < difficulty1.getPosition().x + difficulty1.getLocalBounds().width + 5 &&
                mousePosition.y > difficulty1.getPosition().y - 5 &&
                mousePosition.y < difficulty1.getPosition().y + difficulty1.getLocalBounds().height + 5) {
                difficultyOutline.setPosition(460, 354.f);
                difficulty = 2;
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mousePosition.x > difficulty2.getPosition().x - 5 &&
                mousePosition.x < difficulty2.getPosition().x + difficulty2.getLocalBounds().width + 5 &&
                mousePosition.y > difficulty2.getPosition().y - 5 &&
                mousePosition.y < difficulty2.getPosition().y + difficulty2.getLocalBounds().height + 5) {
                difficultyOutline.setPosition(535, 354.f);
                difficulty = 3;
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mousePosition.x > difficulty3.getPosition().x - 5 &&
                mousePosition.x < difficulty3.getPosition().x + difficulty3.getLocalBounds().width + 5 &&
                mousePosition.y > difficulty3.getPosition().y - 5 &&
                mousePosition.y < difficulty3.getPosition().y + difficulty3.getLocalBounds().height + 5) {
                difficultyOutline.setPosition(610, 354.f);
                difficulty = 4;
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mousePosition.x > difficulty4.getPosition().x - 5 &&
                mousePosition.x < difficulty4.getPosition().x + difficulty4.getLocalBounds().width + 5 &&
                mousePosition.y > difficulty4.getPosition().y - 5 &&
                mousePosition.y < difficulty4.getPosition().y + difficulty4.getLocalBounds().height + 5) {
                difficultyOutline.setPosition(685, 354.f);
                difficulty = 5;
            }

            // Clear screen
            //window.clear();

            // Draw our strings
            //window.draw(back);
            window.draw(titleText);
            window.draw(startText);
            window.draw(difficultyText);
            window.draw(difficulty0);
            window.draw(difficulty1);
            window.draw(difficulty2);
            window.draw(difficulty3);
            window.draw(difficulty4);
            window.draw(difficultyOutline);
            window.draw(exitText);
        }

        // If ready to play
        else {

            // Check for movement of ship
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right) {
                if (myShip.getSprite().getPosition().x + myShip.getSprite().getGlobalBounds().width < WIDTH) {
                    myShip.getSprite().move(shipSpeed * deltaTime, 0.f);
                }
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left) {
                if (myShip.getSprite().getPosition().x > 0.f) {
                    myShip.getSprite().move(-shipSpeed * deltaTime, 0.f);
                }
            }

            //move aliens
            sf::Time t = alienClock.getElapsedTime();
            if (t.asSeconds() > 1 / log2(alienDownSpeed)) {
                for (int j = 0; j < NUMBER_OF_ALIENS_PER_LINE; j++) {
                    for (int i = 0; i < NUMBER_OF_LINES; i++) {
                        alienArray[i][j].getSprite().move((alienMaxSpeed + alienMinSpeed * difficulty) * globalDirection * deltaTime, 0.f);
                    }
                    alienClock.restart();
                }
            }

            // Get furthest alien ID on the side (left or right)
            int lastAliveRight = 0;
            int lastAliveLeft = NUMBER_OF_ALIENS_PER_LINE - 1;
            int lastAliveLine = 0;
            if (globalDirection == 1) {
                for (int j = NUMBER_OF_ALIENS_PER_LINE - 1; j > lastAliveRight - 1; j--) {
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
                        if (alienArray[i][j].isAlive()) {
                            lastAliveLeft = j;
                            lastAliveLine = i;
                        }
                    }
                }
            }

            //test collisions between aliens and borders of the screen
            if (alienArray[lastAliveLine][lastAliveRight].getSprite().getPosition().x +
                alienArray[lastAliveLine][lastAliveRight].getSprite().getGlobalBounds().width > WIDTH - 50 &&
                alienArray[lastAliveLine][lastAliveRight].isAlive()) {
                globalDirection = -1 * globalDirection;
                alienDownSpeed += 0.5;
                for (int k = 0; k < NUMBER_OF_ALIENS_PER_LINE; k++) {
                    for (int l = 0; l < NUMBER_OF_LINES; l++) {
                        alienArray[l][k].getSprite().move((alienMaxSpeed + alienMinSpeed * difficulty) * globalDirection * deltaTime, 30);
                    }
                }
            }
            if (alienArray[lastAliveLine][lastAliveLeft].getSprite().getPosition().x < 50 &&
                alienArray[lastAliveLine][lastAliveLeft].isAlive()) {
                globalDirection = -1 * globalDirection;
                alienDownSpeed += 0.5;
                for (int k = 0; k < NUMBER_OF_ALIENS_PER_LINE; k++) {
                    for (int l = 0; l < NUMBER_OF_LINES; l++) {
                        alienArray[l][k].getSprite().move((alienMaxSpeed + alienMinSpeed * difficulty) * globalDirection * deltaTime, 30);
                    }
                }
            }

            // Fire bullet
            sf::Time bc = bulletClock.getElapsedTime();
            if (bc.asSeconds() > 1.0) {
                if (bullet.isAlive() && !gameOver) {
                    //draw bullet
                    bullet.draw(window);
                    //move bullet
                    bullet.getSprite().move(0.f, -20);
                }
            }

            //test collisions between aliens and ship
            for (int i = 0; i < NUMBER_OF_LINES; i++) {
                for (int j = 0; j < NUMBER_OF_ALIENS_PER_LINE; j++) {
                    if (CollisionManager::collidesWith(myShip, alienArray[i][j]) && alienArray[i][j].isAlive()) {
                        if (!gameOver)
                            music.playExplosion();
                        myShip.kill();
                        winner = false;
                        gameOver = true;
                    }
                }
            }

            //test collisions between aliens and bottom of screen
            for (int i = 0; i < NUMBER_OF_LINES; i++) {
                for (int j = 0; j < NUMBER_OF_ALIENS_PER_LINE; j++) {
                    if (alienArray[i][j].getSprite().getPosition().y +
                        alienArray[i][j].getSprite().getGlobalBounds().height > HEIGHT && alienArray[i][j].isAlive()) {
                        if (!gameOver)
                            music.playExplosion();
                        winner = false;
                        gameOver = true;
                    }
                }
            }

            //test collisions between bullet and aliens
            for (int i = 0; i < NUMBER_OF_LINES; i++) {
                for (int j = 0; j < NUMBER_OF_ALIENS_PER_LINE; j++) {
                    if (CollisionManager::collidesWith(bullet, alienArray[i][j]) && alienArray[i][j].isAlive() &&
                        bullet.isAlive()) {
                        music.playExplosion();
                        alienArray[i][j].kill();
                        bullet.kill();
                    }
                }
            }

            //test for a winner
            int deadAliens = 0;
            for (int i = 0; i < NUMBER_OF_LINES; i++) {
                for (int j = 0; j < NUMBER_OF_ALIENS_PER_LINE; j++) {
                    if (!alienArray[i][j].isAlive()) {
                        deadAliens++;
                    }
                    if (deadAliens == NUMBER_OF_ALIENS_PER_LINE * NUMBER_OF_LINES) {
                        if (!gameOver) {
                            music.playReward();
                            winner = true;
                        }
                        gameOver = true;
                    }
                }
            }

            //test collision with bullet and boundary
            if (bullet.getSprite().getPosition().y < 0) {
                bullet.kill();
            }

            if (!gameOver) {
                for (int i = 0; i < NUMBER_OF_LINES; i++) {
                    for (int j = 0; j < NUMBER_OF_ALIENS_PER_LINE; j++) {
                        if (alienArray[i][j].isAlive())
                            alienArray[i][j].draw(window);
                    }
                }
                if (myShip.isAlive())
                    myShip.draw(window);
            }
            else {
                music.pauseBackgroundMusic();
                play = false;
                if (winner)
                    win.draw(window);
                else
                    lose.draw(window);
            }
        }

        window.display();
    }

    return EXIT_SUCCESS;
}