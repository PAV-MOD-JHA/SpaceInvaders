//
//  Alien.cpp
//

#include "Alien.h"
#include <iostream>
#include <stdexcept>

using namespace std;

//constructor sets ID number, loads sprite
Alien::Alien(int lineNumber, const int id, float sp) {
    //set life points
    lifePoints = 1;

    //set line number
    line = lineNumber;
    spriteNumber = 1;

    //set speed
    speed = sp;

    // Load an enemy texture
    if(!texture.loadFromFile("resources/sprite.png"))
        throw invalid_argument("Enemy not found!");
    
    //scale sprite and set texture so we know size
    sprite.setTexture(texture);
    if (line % 4 == 0) {
        sprite.setTextureRect(sf::IntRect(19, 134, 120, 80));
        sprite.scale(sf::Vector2f(0.3,0.3));
    }
    else if (line % 4 == 1) {
        sprite.setTextureRect(sf::IntRect(19, 14, 110, 80));
        sprite.scale(sf::Vector2f(0.33,0.3));
    }
    else if (line % 4 == 2) {
        sprite.setTextureRect(sf::IntRect(312, 14, 80, 80));
        sprite.scale(sf::Vector2f(0.45,0.3));
    }
    else {
        sprite.setTextureRect(sf::IntRect(300, 134, 100, 80));
        sprite.scale(sf::Vector2f(0.36,0.3));
    }

}

void Alien::switchSprite() {

    if (spriteNumber == 1) {
        if (line % 4 == 0) {
            sprite.setTextureRect(sf::IntRect(19, 134, 120, 80));
        }
        else if (line % 4 == 1) {
            sprite.setTextureRect(sf::IntRect(19, 14, 110, 80));
        }
        else if (line % 4 == 2) {
            sprite.setTextureRect(sf::IntRect(312, 14, 80, 80));
        }
        else {
            sprite.setTextureRect(sf::IntRect(300, 134, 100, 80));
        }
        spriteNumber = 2;
    }

    else {
        if (line % 4 == 0) {
            sprite.setTextureRect(sf::IntRect(160, 134, 120, 80));
        }
        else if (line % 4 == 1) {
            sprite.setTextureRect(sf::IntRect(165, 14, 110, 80));
        }
        else if (line % 4 == 2) {
            sprite.setTextureRect(sf::IntRect(428, 14, 80, 80));
        }
        else {
            sprite.setTextureRect(sf::IntRect(421, 134, 100, 80));
        }
        spriteNumber = 1;
    }
}

