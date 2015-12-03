//
//  Ship.cpp
//

#include "Ship.h"
#include <iostream>
#include <stdexcept>

using namespace std;

//constructor sets ID number, loads sprite
Ship::Ship(const int id,float speed) {
    alive = true;
    lifePoints = 3;

    // Load a Ship to display
    if (!texture.loadFromFile("resources/sprite.png"))
        throw invalid_argument("Ship not found!");

    //create sprite and set texture so we know its size
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(150, 638, 73, 52));
    sprite.scale(sf::Vector2f(0.5, 0.5));
}

bool Ship::isAlive() {
    if (lifePoints>0)
        return true;
    else
        return false;
}

void Ship::respawn() {
    alive=true;
}

void Ship::getShot() {
    lifePoints -= 1;
}