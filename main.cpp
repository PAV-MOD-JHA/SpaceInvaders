#include "AnimatedSprite.hpp"
#include "yemam.h"
#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;
using namespace sf;

int main()
{
	// création de la fenêtre
	sf::Vector2i screenDimensions(500, 500);
	sf::RenderWindow window(sf::VideoMode(screenDimensions.x, screenDimensions.y), "Space Invaders!");
    sf::FloatRect boundingBoxWindow (0,0,500,500);
	window.setFramerateLimit(60);

	int speed_myShip = 2;
    sf::Clock frameClock;

    int speedAlien = 3;

    // Declare and load a texture
	sf::Texture texture;
	texture.loadFromFile("sprite.gif");

	// Create the spaceship
	sf::Sprite myShip;
	myShip.setTexture(texture);
	myShip.setTextureRect(sf::IntRect(150, 638, 73, 52));
	myShip.setPosition(225, 400);


	// Create first alien
	Animation alien1;
	alien1.setSpriteSheet(texture);
	alien1.addFrame(sf::IntRect(19, 14, 110, 81));
	alien1.addFrame(sf::IntRect(165, 14, 110, 81));
	AnimatedSprite animatedAlien1(sf::seconds(0.2), true, false);
    animatedAlien1.setScale(0.5f, 0.5f);
    animatedAlien1.setPosition(10, 10);
	Animation* currentAnimation1 = &alien1;
    int directionAlien1 = 1;

    //Create second alien
    //Animation alien2;
    //alien2.setSpriteSheet(texture);
    //alien2.addFrame(sf::IntRect(19, 134, 121, 80));
    //alien2.addFrame(sf::IntRect(165, 134, 121, 80));
    //AnimatedSprite animatedAlien2(sf::seconds(0.2), true, false);
    //animatedAlien2.setScale(0.5f, 0.5f);
    //animatedAlien2.setPosition(10, 60);
    //Animation* currentAnimation2 = &alien2;

	// Faire tourner le programme tant que la fenêtre n'a pas été fermée
	while (window.isOpen()) {
		// Traitement de tous les évènements de la fenêtre qui ont été générés depuis la dernière itération de la boucle
		sf::Event event;
		while (window.pollEvent(event)) {
			// fermeture de la fenêtre lorsque l'utilisateur le souhaite
			if (event.type == sf::Event::Closed)
				window.close();
		}

		sf::Time frameTime = frameClock.restart();
        animatedAlien1.play(*currentAnimation1);
        //animatedAlien2.play(*currentAnimation2);

        // Move the spaceship
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			myShip.move(-speed_myShip, 0);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			myShip.move(speed_myShip, 0);
		}

        // Change direction of aliens when hits borders
        if (animatedAlien1.getPosition().x > 430 || animatedAlien1.getPosition().x < 10 ) {
            directionAlien1 = -1 * directionAlien1;
            animatedAlien1.move(0, 30);

        }
        animatedAlien1.move(directionAlien1*speedAlien, 0);

        // Shoot missile
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {

        }

		// effacement de la fenêtre en noir
		window.clear(sf::Color::Black);

		// c'est ici qu'on dessine tout
		window.draw(myShip);
        animatedAlien1.update(frameTime);
		window.draw(animatedAlien1);
        //animatedAlien2.update(frameTime);
        //window.draw(animatedAlien2);

		// fin de la frame courante, affichage de tout ce qu'on a dessiné
		window.display();
	}

	return 0;
}
