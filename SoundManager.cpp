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

    //load alien explosion
    if (!alienExplosionBuffer.loadFromFile("resources/alien_explode.wav"))
        throw invalid_argument("Alien explosion sound not loaded!");

    //load ship explosion
    if (!shipExplosionBuffer.loadFromFile("resources/ship_explode.wav"))
        throw invalid_argument("Ship explosion sound not loaded!");

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

void SoundManager::playAlienExplosion()
{
    alienSound.setBuffer(alienExplosionBuffer);
    alienSound.play();
}

void SoundManager::playShipExplosion()
{
    shipSound.setBuffer(shipExplosionBuffer);
    shipSound.play();
}

void SoundManager::playReward()
{
    rewardSound.setBuffer(rewardBuffer);
    rewardSound.play();
}