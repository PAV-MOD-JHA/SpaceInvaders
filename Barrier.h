#include <SFML/Graphics.hpp>
#include "BarrierTile.h"
#include "Bullet.h"
#include "Alien.h"

#ifndef BARRIER_HPP
#define BARRIER_HPP

class Barrier : public sf::Drawable
{
    sf::Vector2f origin;
    BarrierTile * tiles[2][2];
    
public:
    Barrier(sf::Vector2f);
    bool strikeWith(Bullet&);
    bool knockedBy(Alien&);
    virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
};

#endif