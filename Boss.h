//
//  Boss.h
//

#ifndef SpriteMove_Boss_h
#define SpriteMove_Boss_h

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class Boss
{
public:
	//constructor sets ID number, loads sprite
	Boss() {};
	Boss(const int, float);
	sf::Sprite & getSprite();
	void setLocation(float, float);
	void kill();
	bool isAlive();
	void activate();
	bool isActivated();
	float getSpeed() const;
	void draw(sf::RenderWindow &win);
private:
	sf::Sprite sprite;
	sf::Texture texture;
	bool alive;
	bool activated;
	float speed;
};


#endif
#pragma once
