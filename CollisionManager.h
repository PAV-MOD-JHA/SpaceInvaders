//
//  CollisionManager.h
//

#ifndef SpriteMove_CollisionManager_h
#define SpriteMove_CollisionManager_h

#include "Ufo.h"
#include "Bullet.h"
#include <iostream>

class CollisionManager
{
public:
    static bool collidesWith(Ufo &, Ufo &);
    static bool collidesWith(Bullet &, Ufo &);

private:
};

#endif
