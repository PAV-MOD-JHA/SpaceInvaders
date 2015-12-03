#include <SFML/Graphics.hpp>
#include "Bullet.h"
#include "Alien.h"

#ifndef BARRIER_TILE_HPP
#define BARRIER_TILE_HPP

class BarrierTile : public sf::Drawable
{
    sf::Texture normal, damaged;
    void takeDamage();
    int health;
    
public:
    BarrierTile(const char *, const char *);
    bool strikeWith(Bullet&);
    bool knockedBy(Alien&);
    sf::Sprite sprite;
    virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
};

#endif
