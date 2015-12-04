//
//  Ship.h
//

#ifndef SpriteMove_Ship_h
#define SpriteMove_Ship_h

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Ufo.h"

class Ship : public Ufo
{
    public:
        //constructor sets ID number, loads sprite
        Ship(const int,float);
        void respawn();
        void getShot();
        bool isAlive();
        int getLifePoints();

    private:
        int lifePoints;
};

#endif
