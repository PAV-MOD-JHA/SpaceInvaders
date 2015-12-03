//
//  Boss.h
//

#ifndef SpriteMove_Boss_h
#define SpriteMove_Boss_h

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Ufo.h"

class Boss : public Ufo
{
public:
	//constructor sets ID number, loads sprite
	Boss();
	Boss(const int, float);
	void activate();
	void deactivate();
	bool isActivated();

protected:
	bool activated;
};


#endif
#pragma once
