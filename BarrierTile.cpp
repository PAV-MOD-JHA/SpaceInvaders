#include "BarrierTile.h"

BarrierTile::BarrierTile(const char * normalImage, const char * damagedImage)
{
    normal.loadFromFile(normalImage);
    damaged.loadFromFile(damagedImage);
    sprite.setTexture(normal);
    health = 4;
}

bool BarrierTile::strikeWith(Bullet &bullet){
    if (health && bullet.isAlive() && sprite.getGlobalBounds().intersects(bullet.getSprite().getGlobalBounds())) {
        takeDamage();
        bullet.kill();
        return true;
    }
    return false;
}

bool BarrierTile::knockedBy(Alien &alien) {
    if (health && alien.isAlive() && sprite.getGlobalBounds().intersects(alien.getSprite().getGlobalBounds()))
        return true;
    else
        return false;
}

void BarrierTile::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(sprite);
}

void BarrierTile::takeDamage()
{
    health--;
    if (!health)
        sprite.setColor(sf::Color::Transparent);
    else if (health<=2)
        sprite.setTexture(damaged);
}
