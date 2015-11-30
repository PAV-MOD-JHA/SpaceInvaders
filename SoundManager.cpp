//
//  SoundManager.cpp
//  SpriteMove
//
//  Created by Matt Shirlaw on 26/04/13.
//  Copyright (c) 2013 mshirlaw. All rights reserved.
//

#include "SoundManager.h"

SoundManager::SoundManager()
{
    //load lazer
    if (!lazerBuffer.loadFromFile("resources/space_gun.wav"))
        throw invalid_argument("Lazer sound not loaded!");

    //load explosion
    if (!explosionBuffer.loadFromFile("resources/ship_explode.wav"))
        throw invalid_argument("Explosion sound not loaded!");

    //load explosion
    if (!rewardBuffer.loadFromFile("resources/reward.wav"))
        throw invalid_argument("Reward sound not loaded!");
    
    //open music from file
    if (!music.openFromFile("resources/background.wav"))
        throw invalid_argument("Explosion sound not loaded!");
}

void SoundManager::playBackgroundMusic()
{
    music.setLoop(true);
    music.play();
}

void SoundManager::pauseBackgroundMusic()
{
    music.pause();
}

void SoundManager::playLazer()
{
    lazerSound.setBuffer(lazerBuffer);
    lazerSound.play();
}

void SoundManager::playExplosion()
{
    explosionSound.setBuffer(explosionBuffer);
    explosionSound.play();
}

void SoundManager::playReward()
{
    rewardSound.setBuffer(rewardBuffer);
    rewardSound.play();
}