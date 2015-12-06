//
//  Ufo.h
//

#ifndef SpriteMove_Ufo_h
#define SpriteMove_Ufo_h

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class Ufo
{
    public:
        //constructor sets ID number, loads sprite
        Ufo(){};
        Ufo(const int, int,float);
        sf::Sprite & getSprite();
        void setLocation(float,float);
        void kill();
        bool isAlive();
        float getSpeed() const;
        void draw(sf::RenderWindow &win);
        int getLifePoints();
        void getShot ();

    protected:
        sf::Sprite sprite;
        sf::Texture texture;
        bool alive;
        float speed;
        int lifePoints;
};


#endif
