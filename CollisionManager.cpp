//
//  CollisionManager.cpp
//

#include "CollisionManager.h"

bool CollisionManager::collidesWith(Ufo &obj1, Ufo &obj2)
{
    //get the bounding box of the first Ufo
    sf::FloatRect ufo1;
    //top left
    ufo1.left = obj1.getSprite().getPosition().x+10;
    ufo1.top = obj1.getSprite().getPosition().y+10;
    //bottom right
    ufo1.width = obj1.getSprite().getGlobalBounds().width-10;
    ufo1.height = obj1.getSprite().getGlobalBounds().height-10;
    
    //get the bounding box of the ufo2
    sf::FloatRect ufo2;
    //top left
    ufo2.left = obj2.getSprite().getPosition().x;
    ufo2.top = obj2.getSprite().getPosition().y;
    //bottom right
    ufo2.width = obj2.getSprite().getGlobalBounds().width;
    ufo2.height =obj2.getSprite().getGlobalBounds().height;

    //std::cout << "ufo1 left: " << ufo1.left << " " << "ufo1 top: " << ufo1.top << std::endl;
    //std::cout << "ufo2 left: " << ufo2.left << " " << "ufo2 top: " << ufo2.top << std::endl;
        
    return ufo1.intersects(ufo2);
    
}

bool CollisionManager::collidesWith(Bullet &obj1, Ufo &obj2)
{
    //get the bounding box of the ufo1
    sf::FloatRect bullet;
    //top left
    bullet.left = obj1.getSprite().getPosition().x+10;
    bullet.top = obj1.getSprite().getPosition().y+10;
    //bottom right
    bullet.width = obj1.getSprite().getGlobalBounds().width-10;
    bullet.height = obj1.getSprite().getGlobalBounds().height-10;
    
    //get the bounding box of the ufo
    sf::FloatRect ufo;
    //top left
    ufo.left = obj2.getSprite().getPosition().x;
    ufo.top = obj2.getSprite().getPosition().y;
    //bottom right
    ufo.width = obj2.getSprite().getGlobalBounds().width;
    ufo.height =obj2.getSprite().getGlobalBounds().height;
    
    //std::cout << "ufo1 left: " << ufo1.left << " " << "ufo1 top: " << ufo1.top << std::endl;
    //std::cout << "ufo2 left: " << ufo2.left << " " << "ufo2 top: " << ufo2.top << std::endl;
    
    return bullet.intersects(ufo);
    
}
