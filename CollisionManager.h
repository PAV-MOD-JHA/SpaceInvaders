//
//  CollisionManager.h
//

#ifndef SpriteMove_CollisionManager_h
#define SpriteMove_CollisionManager_h

#include "Ship.h"
#include "Ufo.h"
#include "Bullet.h"
#include <iostream>

class CollisionManager
{
public:
    static bool collidesWith(Ship &, Ufo &);
    static bool collidesWith(Bullet &, Ufo &);

private:
};

#endif
