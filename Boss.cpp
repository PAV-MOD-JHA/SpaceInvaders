//
//  Boss.cpp (From Enemy)
//

#include "Boss.h"
#include <iostream>
#include <stdexcept>

using namespace std;

//constructor sets ID number, loads sprite
Boss::Boss(const int id, float sp) {
	//set alive
//	alive = true;

	//set non activated
	activated = false;

	//set speed
//	speed = sp;

	// Load a Boss texture
	if (!texture.loadFromFile("resources/Nyancat.png"))
		throw invalid_argument("Boss not found!");

	//scale sprite and set texture so we know size 
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, 1150, 700));
	sprite.scale(sf::Vector2f(0.05, 0.05));
}

//sf::Sprite & Boss::getSprite() {
//	return sprite;
//}

//void Boss::setLocation(float xpos, float ypos) {
//	sprite.setPosition(xpos, ypos);
//}

void Boss::activate() {
	activated = true;
}

bool Boss::isActivated() {
	return activated;
}

//void Boss::kill() {
//	alive = false;
//}

//bool Boss::isAlive() {
//	return alive;
//}

//void Boss::draw(sf::RenderWindow &win) {
	//set texture
//	sprite.setTexture(texture);
	//draw
//	win.draw(sprite);
//}

//float Boss::getSpeed() const {
//	return speed;
//}

