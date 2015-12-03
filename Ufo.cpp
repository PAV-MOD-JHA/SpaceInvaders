//
//  Ufo.cpp
//

#include "Ufo.h"
#include <iostream>
#include <stdexcept>

using namespace std;

//constructor sets ID number, loads sprite
Ufo::Ufo(int lineNumber, const int id, float sp) {
    //set alive
    alive = true;

    //set speed
    speed = sp;

}

sf::Sprite & Ufo::getSprite() {
    return sprite;
}

void Ufo::setLocation(float xpos, float ypos) {
    sprite.setPosition(xpos,ypos);
}

void Ufo::kill() {
    alive = false;
}

bool Ufo::isAlive() {
    return alive;
}

void Ufo::draw(sf::RenderWindow &win) {
    //set texture
    sprite.setTexture(texture);
    //draw
    win.draw(sprite);
}

float Ufo::getSpeed() const {
    return speed;
}

