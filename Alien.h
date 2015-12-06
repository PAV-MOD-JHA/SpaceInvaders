//
//  Alien.h
//

#ifndef SpriteMove_Alien_h
#define SpriteMove_Alien_h

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Ufo.h"

class Alien: public Ufo
{
    public:
        //constructor sets ID number, loads sprite
        Alien(){};
        Alien(const int, int,float);
        void switchSprite();

	protected:
        int line;
        int spriteNumber;
  
};


#endif
