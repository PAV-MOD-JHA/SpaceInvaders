#include "Barrier.h"

#define BARRIER_TILE_W 40
#define BARRIER_TILE_H 25

Barrier::Barrier(sf::Vector2f origin)
{
    this->origin = origin;
    
    tiles[0][0] = new BarrierTile("resources/barrier_tl1.png", "resources/barrier_tl2.png", "resources/barrier_tl3.png");
    tiles[0][1] = new BarrierTile("resources/barrier_tr1.png", "resources/barrier_tr2.png", "resources/barrier_tr3.png");
    tiles[1][0] = new BarrierTile("resources/barrier_bl1.png", "resources/barrier_bl2.png", "resources/barrier_bl3.png");
    tiles[1][1] = new BarrierTile("resources/barrier_br1.png", "resources/barrier_br2.png", "resources/barrier_br3.png");
    
    // Textures & Sprites
    sf::Vector2f pos(origin);
    for (int r = 0; r < 2; r++) {
        for (int c = 0; c < 2; c++) {
            tiles[r][c]->sprite.setPosition(pos);
            pos.x += BARRIER_TILE_W;
        }
        pos.x = origin.x;
        pos.y += BARRIER_TILE_H;
    }
}

bool Barrier::strikeWith(Bullet& bullet)
{
    for (int r = 0; r < 2; r++)
        for (int c = 0; c < 2; c++)
            if (tiles[r][c]->strikeWith(bullet))
                return true;
    return false;
}

bool Barrier::knockedBy(Alien& alien)
{
    for (int r = 0; r < 2; r++)
        for (int c = 0; c < 2; c++)
            if (tiles[r][c]->knockedBy(alien))
                return true;
    return false;
}


void Barrier::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (int r = 0; r < 2; r++)
        for (int c = 0; c < 2; c++)
            tiles[r][c]->draw(target, states);
}

