//
//  Bullet.h
//

#ifndef SpriteMove_Bullet_h
#define SpriteMove_Bullet_h


#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class Bullet
{
public:
    Bullet() {};
    //constructor sets ID number, loads sprite
	Bullet(float);
    sf::Sprite & getSprite();
    void setLocation(float,float);
    void kill();
    bool isAlive();
    void spawn(bool);
	float getSpeed();
    //draw the sprite
    void draw(sf::RenderWindow &win);
private:
    sf::Sprite sprite;
    sf::Texture texture;
    bool alive;
	float speed;

};

#endif
