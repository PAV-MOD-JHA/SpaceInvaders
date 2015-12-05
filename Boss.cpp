//
//  Boss.cpp
//

#include "Boss.h"
#include <iostream>
#include <stdexcept>

using namespace std;

//constructor sets ID number, loads sprite
Boss::Boss(const int id, float sp) {
	//set life points
	lifePoints = 3;

	//set non activated
	activated = false;

	//set speed
	speed = sp;

	// Load a Boss texture
	if (!texture.loadFromFile("resources/Nyancat.png"))
		throw invalid_argument("Boss not found!");

	//scale sprite and set texture so we know size 
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, 1150, 700));
	sprite.scale(sf::Vector2f(0.05, 0.05));
}

void Boss::activate() {
	activated = true;
}

void Boss::deactivate() {
	activated = false;
}

bool Boss::isActivated() {
	return activated;
}

