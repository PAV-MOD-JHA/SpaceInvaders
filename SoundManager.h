//
//  SoundManager.h
//  SpriteMove
//
//  Created by Matt Shirlaw on 26/04/13.
//  Copyright (c) 2013 mshirlaw. All rights reserved.
//

#ifndef __SpriteMove__SoundManager__
#define __SpriteMove__SoundManager__

#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <stdexcept>
using namespace std;

class SoundManager
{
public:
    SoundManager();
    void playBackgroundMusic();
    void pauseBackgroundMusic();
    void playLazer();
    void playAlienExplosion();
    void playShipExplosion();
    void playReward();
private:
    sf::SoundBuffer lazerBuffer;
    sf::SoundBuffer alienExplosionBuffer;
    sf::SoundBuffer shipExplosionBuffer;
    sf::SoundBuffer rewardBuffer;
    sf::Music music;
    sf::Sound lazerSound;
    sf::Sound alienSound;
    sf::Sound shipSound;
    sf::Sound rewardSound;
};

#endif
