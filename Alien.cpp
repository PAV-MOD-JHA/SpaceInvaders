//
//  Alien.cpp
//

#include "Alien.h"
#include <iostream>
#include <stdexcept>

using namespace std;

//constructor sets ID number, loads sprite
Alien::Alien(int lineNumber, const int id, float sp) {
    //set alive
    alive = true;

    //set speed
    speed = sp;

    // Load an enemy texture
    if(!texture.loadFromFile("resources/sprite.png"))
        throw invalid_argument("Enemy not found!");
    
    //scale sprite and set texture so we know size
    sprite.setTexture(texture);
    if (lineNumber%4 == 0) {
        sprite.setTextureRect(sf::IntRect(19, 14, 110, 81));
    }
    else if (lineNumber%4 == 1) {
        sprite.setTextureRect(sf::IntRect(165, 14, 110, 81));
    }
    else if (lineNumber%4 == 2) {
        sprite.setTextureRect(sf::IntRect(19, 134, 120, 80));
    }
    else {
        sprite.setTextureRect(sf::IntRect(165, 134, 120, 80));
    }
    sprite.scale(sf::Vector2f(0.3,0.3));
}
