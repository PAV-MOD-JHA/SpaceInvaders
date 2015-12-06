#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "Ship.h"
#include "Alien.h"
#include "Boss.h"
#include "Bullet.h"
#include "CollisionManager.h"
#include "SoundManager.h"
#include "Barrier.h"

using namespace std;

#define WIDTH 800
#define HEIGHT 600
#define NUMBER_OF_ALIENS_PER_LINE 7
#define NUMBER_OF_LINES 4

int main() {
    const float shipSpeed = 200.f;
    const int alienMaxSpeed = 1000;
    const int alienMinSpeed = 800;
    int alienDownSpeed = 2;
    const float bulletSpeed = 5.f;
    int globalDirection = +1;
	int bossDirection = +1;

    bool gameOver=false;
    bool winner = false;
    bool play = false;

    int difficulty = 1;
    int score = 0;
    const int fixedScoreAlien = 100;
    const int variableScoreAlien = 2;
	const int bossPremium = 1000;
    int levelAchievedScore = 1000;
    string highscore="0";

    // Create main window
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "HomeScreen");
    window.setVerticalSyncEnabled(true);

    //start background music
    SoundManager music;
    //music.playBackgroundMusic();

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
    difficultyText.setPosition(52.f, 370.f);

    sf::Text difficulty0;
    difficulty0.setFont(font);
    difficulty0.setString("1");
    difficulty0.setCharacterSize(44);
    difficulty0.setColor(sf::Color::White);
    difficulty0.setPosition(350 + 50.f, 370.f);

    sf::Text difficulty1;
    difficulty1.setFont(font);
    difficulty1.setString("2");
    difficulty1.setCharacterSize(44);
    difficulty1.setColor(sf::Color::White);
    difficulty1.setPosition(425 + 50.f, 370.f);

    sf::Text difficulty2;
    difficulty2.setFont(font);
    difficulty2.setString("3");
    difficulty2.setCharacterSize(44);
    difficulty2.setColor(sf::Color::White);
    difficulty2.setPosition(500 + 50.f, 370.f);

    sf::Text difficulty3;
    difficulty3.setFont(font);
    difficulty3.setString("4");
    difficulty3.setCharacterSize(44);
    difficulty3.setColor(sf::Color::White);
    difficulty3.setPosition(575 + 50.f, 370.f);

    sf::Text difficulty4;
    difficulty4.setFont(font);
    difficulty4.setString("5");
    difficulty4.setCharacterSize(44);
    difficulty4.setColor(sf::Color::White);
    difficulty4.setPosition(650 + 50.f, 370.f);

    sf::RectangleShape difficultyOutline;
    difficultyOutline.setSize(sf::Vector2f(50, 50));
    difficultyOutline.setOutlineColor(sf::Color::White);
    difficultyOutline.setFillColor(sf::Color::Transparent);
    difficultyOutline.setOutlineThickness(5);
    difficultyOutline.setPosition(385, 374.f);

    // Display current high score
    ifstream highscoreFile ("highscores.txt");
    string line;
    if (highscoreFile.is_open()) {
        while (getline(highscoreFile,line)) {
            highscore = line;
        }
        highscoreFile.close();
    }
    else {
        cout << "Unable to open highscore file";
    }

    sf::Text highScoreText;
    highScoreText.setFont(font);
    highScoreText.setString("Highscore : "+highscore);
    highScoreText.setCharacterSize(56);
    highScoreText.setColor(sf::Color::Red);
    highScoreText.setPosition(WIDTH/2 - highScoreText.getLocalBounds().width/2, 235.f);



    // ----------------------- CREATE GAME SCREEN ------------------------- //

    // Create a bullet for our ship
    Bullet bullet(0,bulletSpeed);

	// Create an array for the bullets of the aliens
	Bullet bulletArray[NUMBER_OF_ALIENS_PER_LINE];
	for (int j = 0; j < NUMBER_OF_ALIENS_PER_LINE; j++) {
		Bullet bulletAlien(j, bulletSpeed);
		bulletArray[j] = bulletAlien;
	}

    // Create the ship
    Ship myShip(0,shipSpeed);
    myShip.setLocation(WIDTH/2 - myShip.getSprite().getGlobalBounds().height/2, HEIGHT - myShip.getSprite().getGlobalBounds().height-20);

    // Create an array of an array of aliens
    Alien alienArray[NUMBER_OF_LINES][NUMBER_OF_ALIENS_PER_LINE];
    for(int i=0; i<NUMBER_OF_LINES; i++) {
        for(int j=0; j<NUMBER_OF_ALIENS_PER_LINE; j++) {
            Alien alien(i, j, alienMinSpeed);
            alien.setLocation(j * 50 + 150, alien.getSprite().getGlobalBounds().height / 2 + i*50 + 50);
            alienArray[i][j] = alien;
        }
    }

	// Create a Boss
	Boss boss(0, alienMinSpeed);
    boss.setLocation(WIDTH/2, boss.getSprite().getGlobalBounds().height / 2 + 50);

    // Create score display
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setString("Score :");
    scoreText.setCharacterSize(24);
    scoreText.setColor(sf::Color::White);
    scoreText.setPosition(10,10);

    sf::Text scoreLiveText;
    scoreLiveText.setFont(font);
    scoreLiveText.setString("0");
    scoreLiveText.setCharacterSize(24);
    scoreLiveText.setColor(sf::Color::White);
    scoreLiveText.setPosition(90,10);

    // Create life points display
    sf::Text lifePointsText;
    lifePointsText.setFont(font);
    lifePointsText.setCharacterSize(24);
    lifePointsText.setColor(sf::Color::White);
    lifePointsText.setPosition(700,10);

    // Create barriers
    Barrier barrier1(sf::Vector2f(140, 480));
    Barrier barrier2(sf::Vector2f(280, 480));
    Barrier barrier3(sf::Vector2f(420, 480));
    Barrier barrier4(sf::Vector2f(560, 480));


    // ----------------------- CREATE GAMEOVER SCREEN ------------------------- //

    sf::Text congratsText;
    congratsText.setFont(font);
    congratsText.setString("CONGRATULATIONS!");
    congratsText.setCharacterSize(100);
    congratsText.setColor(sf::Color::White);
    congratsText.setPosition(WIDTH/2 - congratsText.getLocalBounds().width/2, 150);

    sf::Text youWinText;
    youWinText.setFont(font);
    youWinText.setString("YOU WIN!");
    youWinText.setCharacterSize(72);
    youWinText.setColor(sf::Color::White);
    youWinText.setPosition(WIDTH/2 - youWinText.getLocalBounds().width/2, 250);

    sf::Text gameoverText;
    gameoverText.setFont(font);
    gameoverText.setString("GAME OVER!");
    gameoverText.setCharacterSize(100);
    gameoverText.setColor(sf::Color::White);
    gameoverText.setPosition(WIDTH/2 - gameoverText.getLocalBounds().width/2, 150);

    sf::Text youLoseText;
    youLoseText.setFont(font);
    youLoseText.setString("YOU LOSE!");
    youLoseText.setCharacterSize(72);
    youLoseText.setColor(sf::Color::White);
    youLoseText.setPosition(WIDTH/2 - youLoseText.getLocalBounds().width/2, 250);

    sf::Text continueText;
    continueText.setFont(font);
    continueText.setString("Click on Space to play a new game");
    continueText.setCharacterSize(32);
    continueText.setColor(sf::Color::Red);
    continueText.setPosition(WIDTH/2 - continueText.getLocalBounds().width/2, 465);

    sf::Text quitText;
    quitText.setFont(font);
    quitText.setString("Or click on Escape to exit the game");
    quitText.setCharacterSize(32);
    quitText.setColor(sf::Color::Red);
    quitText.setPosition(WIDTH/2 - quitText.getLocalBounds().width/2, 500);

    sf::Text newHighScoreText;
    newHighScoreText.setFont(font);
    newHighScoreText.setString("New high score!");
    newHighScoreText.setCharacterSize(32);
    newHighScoreText.setColor(sf::Color::Red);
    newHighScoreText.setPosition(WIDTH/2 - newHighScoreText.getLocalBounds().width/2, 50);



    // ----------------------- CREATE MULTIPLE CLOCKS ------------------------- //

    // Main clock for fps
    sf::Clock clock;

    // Clock for alien movement
    sf::Clock alienClock;
    alienClock.restart().asSeconds();

    // Clock for alien animation
    sf::Clock alienAnimationClock;
    alienAnimationClock.restart().asSeconds();

	//Clock for Boss
	sf::Clock bossClock;
	bossClock.restart().asSeconds();

    // Clock for bullet
    sf::Clock bulletClock;
    bulletClock.restart().asSeconds();

	// Clock for alien fire
	sf::Clock alienFireClock;
    alienFireClock.restart().asSeconds();

    // Clock for score
    sf::Clock scoreClock;
    scoreClock.restart().asSeconds();


    // ----------------------- START GAME LOOP ------------------------- //

    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                if (gameOver) {
                    window.close();
                }
                else {
                    play = false;

                    // Reset aliens
                    for(int i=0; i<NUMBER_OF_LINES; i++) {
                        for(int j=0; j<NUMBER_OF_ALIENS_PER_LINE; j++) {
                            Alien alien(i, j, alienMinSpeed);
                            alien.setLocation(j * 50 + 150, alien.getSprite().getGlobalBounds().height / 2 + i*50 + 50);
                            alienArray[i][j] = alien;
                        }
                    }

                    // Reset Boss location
                    Boss boss2(0, alienMinSpeed);
                    boss = boss2;
                    boss.setLocation(WIDTH / 2, boss.getSprite().getGlobalBounds().height / 2 + 50);

                    // Reset ship
                    myShip.respawn();
                    myShip.setLocation(WIDTH/2 - myShip.getSprite().getGlobalBounds().height/2, HEIGHT - myShip.getSprite().getGlobalBounds().height-20);

                    // Reset Alien bullets
                    for (int j=0; j < NUMBER_OF_ALIENS_PER_LINE; j++) {
                        bulletArray[j].kill();
                    }

                    // Reset barriers
                    barrier1.respawn();
                    barrier2.respawn();
                    barrier3.respawn();
                    barrier4.respawn();

                    globalDirection = 1;
                    score = 0;
                    scoreLiveText.setString("0");

                }
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                if (!bullet.isAlive() && !gameOver && play) {
                    bullet.spawn(true);
                    bullet.setLocation(myShip.getSprite().getPosition().x + 13, myShip.getSprite().getPosition().y - 10);
                    music.playLazer();
                }
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                if (gameOver) {
                    play = false;
                }
            }
        }

        window.clear();
        window.draw(back);

        // If not ready to play
        if (!play) {

            // Reset the sprites
            if (gameOver) {
                for(int i=0; i<NUMBER_OF_LINES; i++) {
                    for(int j=0; j<NUMBER_OF_ALIENS_PER_LINE; j++) {
                        Alien alien(i, j, alienMinSpeed);
                        alien.setLocation(j * 50 + 150, alien.getSprite().getGlobalBounds().height / 2 + i*50 + 50);
                        alienArray[i][j] = alien;
                    }
                }

				// Reset Boss location
				Boss boss2(0, alienMinSpeed);
				boss = boss2;
				boss.setLocation(WIDTH / 2, boss.getSprite().getGlobalBounds().height / 2 + 50);

				// Reset ship
                myShip.respawn();
				myShip.setLocation(WIDTH/2 - myShip.getSprite().getGlobalBounds().height/2, HEIGHT - myShip.getSprite().getGlobalBounds().height-20);

				// Reset Alien bullets
				for (int j=0; j < NUMBER_OF_ALIENS_PER_LINE; j++) {
					bulletArray[j].kill();
				}

                // Reset barriers
                barrier1.respawn();
                barrier2.respawn();
                barrier3.respawn();
                barrier4.respawn();

                globalDirection = 1;
                score = 0;
                scoreLiveText.setString("0");

            }
            gameOver = false;
            winner = false;

            // Refresh high score
            ifstream highscoreFile ("highscores.txt");
            if (highscoreFile.is_open()) {
                while (getline(highscoreFile,line)) {
                    highscore = line;
                }
                highscoreFile.close();
            }
            else {
                cout << "Unable to open highscore file";
            }
            highScoreText.setString("Highscore : "+highscore);

            // Get cursor position
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

            // Click on Start
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mousePosition.x > startText.getPosition().x -5 &&
                mousePosition.x < startText.getPosition().x + startText.getLocalBounds().width +5 &&
                mousePosition.y > startText.getPosition().y -5 &&
                mousePosition.y < startText.getPosition().y + startText.getLocalBounds().height +5) {
                play = true;
                scoreClock.restart().asSeconds();
            }
            // Click on Exit
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mousePosition.x > exitText.getPosition().x -5 &&
                mousePosition.x < exitText.getPosition().x + exitText.getLocalBounds().width +5 &&
                mousePosition.y > exitText.getPosition().y -5 &&
                mousePosition.y < exitText.getPosition().y + exitText.getLocalBounds().height +5) {
                window.close();
            }

            // Choose difficulty
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mousePosition.x > difficulty0.getPosition().x - 5 &&
                mousePosition.x < difficulty0.getPosition().x + difficulty0.getLocalBounds().width + 5 &&
                mousePosition.y > difficulty0.getPosition().y - 5 &&
                mousePosition.y < difficulty0.getPosition().y + difficulty0.getLocalBounds().height + 5) {
                difficultyOutline.setPosition(385, 374.f);
                difficulty = 1;
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mousePosition.x > difficulty1.getPosition().x - 5 &&
                mousePosition.x < difficulty1.getPosition().x + difficulty1.getLocalBounds().width + 5 &&
                mousePosition.y > difficulty1.getPosition().y - 5 &&
                mousePosition.y < difficulty1.getPosition().y + difficulty1.getLocalBounds().height + 5) {
                difficultyOutline.setPosition(460, 374.f);
                difficulty = 2;
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mousePosition.x > difficulty2.getPosition().x - 5 &&
                mousePosition.x < difficulty2.getPosition().x + difficulty2.getLocalBounds().width + 5 &&
                mousePosition.y > difficulty2.getPosition().y - 5 &&
                mousePosition.y < difficulty2.getPosition().y + difficulty2.getLocalBounds().height + 5) {
                difficultyOutline.setPosition(535, 374.f);
                difficulty = 3;
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mousePosition.x > difficulty3.getPosition().x - 5 &&
                mousePosition.x < difficulty3.getPosition().x + difficulty3.getLocalBounds().width + 5 &&
                mousePosition.y > difficulty3.getPosition().y - 5 &&
                mousePosition.y < difficulty3.getPosition().y + difficulty3.getLocalBounds().height + 5) {
                difficultyOutline.setPosition(610, 374.f);
                difficulty = 4;
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mousePosition.x > difficulty4.getPosition().x - 5 &&
                mousePosition.x < difficulty4.getPosition().x + difficulty4.getLocalBounds().width + 5 &&
                mousePosition.y > difficulty4.getPosition().y - 5 &&
                mousePosition.y < difficulty4.getPosition().y + difficulty4.getLocalBounds().height + 5) {
                difficultyOutline.setPosition(685, 374.f);
                difficulty = 5;
            }

            window.draw(titleText);
            window.draw(startText);
            window.draw(difficultyText);
            window.draw(difficulty0);
            window.draw(difficulty1);
            window.draw(difficulty2);
            window.draw(difficulty3);
            window.draw(difficulty4);
            window.draw(difficultyOutline);
            window.draw(highScoreText);
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


            // Animate aliens
            sf::Time ta = alienAnimationClock.getElapsedTime();
            if (ta.asSeconds() > 0.5) {
                for (int j = 0; j < NUMBER_OF_ALIENS_PER_LINE; j++) {
                    for (int i = 0; i < NUMBER_OF_LINES; i++) {
                        alienArray[i][j].switchSprite();
                    }
                    alienAnimationClock.restart();
                }
            }

            // Move aliens
            sf::Time t = alienClock.getElapsedTime();
            if (t.asSeconds() > 1 / log2(alienDownSpeed)) {
                for (int j = 0; j < NUMBER_OF_ALIENS_PER_LINE; j++) {
                    for (int i = 0; i < NUMBER_OF_LINES; i++) {
                        alienArray[i][j].getSprite().move((alienMaxSpeed + alienMinSpeed * difficulty) * globalDirection * deltaTime, 0.f);
                    }
                    alienClock.restart();
                }
            }

			// Get the last alien IDs at the bottom
			int lastAliveBottom[NUMBER_OF_ALIENS_PER_LINE];
			for (int j = 0; j < NUMBER_OF_ALIENS_PER_LINE; j++) {
				for (int i = 0; i < NUMBER_OF_LINES; i++) {
					if (alienArray[i][j].isAlive()) {
						lastAliveBottom[j] = i;
					}
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

			// Alien Fire bullets
			//sf::Time afc = alienFireClock.getElapsedTime();
			//if (afc.asSeconds() > 1.0) {
			//	int columnShooting = rand() % NUMBER_OF_ALIENS_PER_LINE;
			//	if (!bulletArray[columnShooting].isAlive() && !gameOver) {
			//		bulletArray[columnShooting].spawn(true);
			//		bulletArray[columnShooting].setLocation(
			//			alienArray[lastAliveBottom[columnShooting]][columnShooting].getSprite().getPosition().x + 13,
			//			alienArray[lastAliveBottom[columnShooting]][columnShooting].getSprite().getPosition().y + 13);
			//		music.playLazer();
			//	}
			//}

			// Alien Fire bullets
			sf::Time afc = alienFireClock.getElapsedTime();
			float shootingTrigger = rand() % 3+1;
			if (afc.asSeconds() > (shootingTrigger/log2(difficulty+1))){
				int columnShooting = rand() % NUMBER_OF_ALIENS_PER_LINE;
				if (!bulletArray[columnShooting].isAlive() && !gameOver) {
					bulletArray[columnShooting].spawn(true);
					bulletArray[columnShooting].setLocation(alienArray[lastAliveBottom[columnShooting]][columnShooting].getSprite().getPosition().x + 13, alienArray[lastAliveBottom[columnShooting]][columnShooting].getSprite().getPosition().y + 13);
					music.playLazer();
					alienFireClock.restart();
					shootingTrigger = rand() % 3+1;
				}
			}

			// Alien bullet display
			for (int j = 0; j < NUMBER_OF_ALIENS_PER_LINE; j++) {
				if (bulletArray[j].isAlive() && !gameOver) {
					//draw bullet
					bulletArray[j].draw(window);
					//move bullet
					bulletArray[j].getSprite().move(0.f, bulletArray[j].getSpeed()+log2(difficulty));
				}
			}

            // Test collisions between aliens and ship
            for (int i = 0; i < NUMBER_OF_LINES; i++) {
                for (int j = 0; j < NUMBER_OF_ALIENS_PER_LINE; j++) {
                    if (CollisionManager::collidesWith(myShip, alienArray[i][j]) && alienArray[i][j].isAlive()) {
                        if (!gameOver)
                            music.playShipExplosion();
                        myShip.kill();
                        winner = false;
                        gameOver = true;
                    }
                }
            }

            // Test collisions between aliens and bottom of screen
            for (int i = 0; i < NUMBER_OF_LINES; i++) {
                for (int j = 0; j < NUMBER_OF_ALIENS_PER_LINE; j++) {
                    if (alienArray[i][j].getSprite().getPosition().y + alienArray[i][j].getSprite().getGlobalBounds().height > HEIGHT && alienArray[i][j].isAlive()) {
                        if (!gameOver)
                            music.playAlienExplosion();
                        winner = false;
                        gameOver = true;
                    }
                }
            }

            // Test collisions between aliens and barriers
            for (int i = 0; i < NUMBER_OF_LINES; i++) {
                for (int j = 0; j < NUMBER_OF_ALIENS_PER_LINE; j++) {
                    if (barrier1.knockedBy(alienArray[i][j]) || barrier2.knockedBy(alienArray[i][j]) || barrier3.knockedBy(alienArray[i][j]) || barrier4.knockedBy(alienArray[i][j])) {
                        gameOver = true;
                        winner = false;
                    }
                }
            }

            // Test collisions between bullet and aliens
            for (int i = 0; i < NUMBER_OF_LINES; i++) {
                for (int j = 0; j < NUMBER_OF_ALIENS_PER_LINE; j++) {
                    if (CollisionManager::collidesWith(bullet, alienArray[i][j]) && alienArray[i][j].isAlive() &&
                        bullet.isAlive()) {
                        music.playAlienExplosion();
                        alienArray[i][j].getShot();
                        bullet.kill();
                        score += fixedScoreAlien*difficulty;
                        if (scoreClock.getElapsedTime().asSeconds() < 120)
                            score += (120 - scoreClock.getElapsedTime().asSeconds())*variableScoreAlien;
                        scoreLiveText.setString(std::to_string(score));
                    }
                }
            }

			// Test collisions between bulletAlien and ship
			for (int j = 0; j < NUMBER_OF_ALIENS_PER_LINE; j++) {
				if (CollisionManager::collidesWith(bulletArray[j], myShip) && bulletArray[j].isAlive() && myShip.isAlive()) {
					music.playShipExplosion();
					myShip.getShot();
					myShip.setLocation(WIDTH / 2 - myShip.getSprite().getGlobalBounds().height / 2, HEIGHT - myShip.getSprite().getGlobalBounds().height - 20);
					bulletArray[j].kill();
				}
			}

			// Activate boss
			if (!boss.isActivated()) {
				for (int j = 0; j < NUMBER_OF_ALIENS_PER_LINE; j++) {
					if (alienArray[0][j].getSprite().getPosition().y > 150) {
                        boss.activate();
					}
				}
			}

			// Move Boss -- every 1/ln(int random between 1 and 10)
			sf::Time tb = bossClock.getElapsedTime();
			if (tb.asSeconds() > 1/(log2(rand()%(9)+1)) && boss.isActivated() ){
				boss.getSprite().move((alienMaxSpeed + alienMinSpeed*difficulty) * bossDirection * deltaTime, 0.f);
				bossClock.restart();
			}

			// Test collisions Between boss and borders of the screen
			if (boss.isAlive() && boss.isActivated() &&  (boss.getSprite().getPosition().x +boss.getSprite().getGlobalBounds().width > WIDTH - 50 || boss.getSprite().getPosition().x < 50) ) {
				bossDirection = -1 * bossDirection;
                boss.getSprite().move((alienMaxSpeed + alienMinSpeed*difficulty) * bossDirection * deltaTime, 0);
			}

			// Test collisions between boss and bullets
			if (CollisionManager::collidesWith(bullet, boss) && boss.isAlive() && boss.isActivated() &&	bullet.isAlive()) {
                music.playAlienExplosion();
                boss.getShot();
                if (!boss.isAlive()) {
                    boss.kill();
                    score += difficulty * bossPremium;
                }
				bullet.kill();
				if (scoreClock.getElapsedTime().asSeconds() < 120)
					score += (120 - scoreClock.getElapsedTime().asSeconds())*variableScoreAlien;
				scoreLiveText.setString(std::to_string(score));
			}

            // Test collision with bullet and boundary
            if (bullet.getSprite().getPosition().y < 0) {
                bullet.kill();
            }

			// Test collision with bulletAlien and boundary
			for (int j=0; j < NUMBER_OF_ALIENS_PER_LINE; j++) {
				if (bulletArray[j].getSprite().getPosition().y > 600) {
					bulletArray[j].kill();
				}
			}

            // Test collisions between barriers and bullets
            barrier1.strikeWith(bullet);
            barrier2.strikeWith(bullet);
            barrier3.strikeWith(bullet);
            barrier4.strikeWith(bullet);

			// Test collisions between barriers and bullets
			for (int j = 0; j < NUMBER_OF_ALIENS_PER_LINE; j++) {
				barrier1.strikeWith(bulletArray[j]);
				barrier2.strikeWith(bulletArray[j]);
				barrier3.strikeWith(bulletArray[j]);
				barrier4.strikeWith(bulletArray[j]);
			}

			// Test for a winner
			int deadAliens = 0;
			for (int i = 0; i < NUMBER_OF_LINES; i++) {
				for (int j = 0; j < NUMBER_OF_ALIENS_PER_LINE; j++) {
					if (!alienArray[i][j].isAlive()) {
						deadAliens++;
					}
					if (deadAliens == NUMBER_OF_ALIENS_PER_LINE * NUMBER_OF_LINES && !boss.isAlive()) {
						if (!gameOver) {
							music.playReward();
							winner = true;
						}
						gameOver = true;
					}
				}
			}

			// Draw to screen
			if (!gameOver) {
				for (int i = 0; i < NUMBER_OF_LINES; i++) {
					for (int j = 0; j < NUMBER_OF_ALIENS_PER_LINE; j++) {
						if (alienArray[i][j].isAlive())
							alienArray[i][j].draw(window);
					}
				}

				if (boss.isAlive() && boss.isActivated()) {
                    boss.draw(window);
				}

				if (myShip.isAlive())
					myShip.draw(window);
                else
                    gameOver = true;

                // Set remaining lives
                lifePointsText.setString("Lives : " + to_string(myShip.getLifePoints()));
                window.draw(lifePointsText);

                window.draw(barrier1);
                window.draw(barrier2);
                window.draw(barrier3);
                window.draw(barrier4);

				window.draw(scoreText);
				window.draw(scoreLiveText);
			}
			else {
				music.pauseBackgroundMusic();
				if (winner) {
					window.draw(youWinText);
					window.draw(congratsText);
				}
				else {
					window.draw(youLoseText);
					window.draw(gameoverText);
				}
				if (score > std::stoi(highscore)) {
					window.draw(newHighScoreText);
					ofstream highscoreFile ("highscores.txt");
					if (highscoreFile.is_open()) {
						highscoreFile.clear();
						highscoreFile << to_string(score+levelAchievedScore*difficulty);
						highscoreFile.close();
					}
					else {
						cout << "Unable to open highscore file";
					}
				}
				score = 0;
				window.draw(continueText);
				window.draw(quitText);
			}
		}

		window.display();
	}

    return EXIT_SUCCESS;
}
