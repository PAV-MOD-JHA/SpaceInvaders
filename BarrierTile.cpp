#include "BarrierTile.h"

BarrierTile::BarrierTile(const char * normalImage, const char * hitOnceImage, const char * hitTwiceImage)
{
    normal.loadFromFile(normalImage);
    hitOnce.loadFromFile(hitOnceImage);
    hitTwice.loadFromFile(hitTwiceImage);
    sprite.setTexture(normal);
    health = 3;
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
    else if (health == 1)
        sprite.setTexture(hitTwice);
    else if (health >= 2)
        sprite.setTexture(hitOnce);
}
