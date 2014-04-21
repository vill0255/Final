//
//  Projectile.h
//  GameDevFramework
//
//  
//  Copyright (c) 2014 Algonquin College. All rights reserved.
//

#ifndef __GameDevFramework__Projectile__
#define __GameDevFramework__Projectile__

#include "GameObject.h"
#include "../Libraries/Box2D/Box2D.h"


class Projectile : public GameObject
{
public:
    Projectile(b2Vec2 position, float angle, b2Vec2 linearVelocity);
    ~Projectile();
    
    const char* getType();
};

#endif /* defined(__GameDevFramework__Projectile__) */
