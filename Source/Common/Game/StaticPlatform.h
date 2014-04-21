//
//  StaticPlatform.h
//  GameDevFramework
//
//  Created by Bradley Flood on 2014-04-02.
//  Copyright (c) 2014 Algonquin College. All rights reserved.
//

#ifndef __GameDevFramework__StaticPlatform__
#define __GameDevFramework__StaticPlatform__

#include "GameObject.h"


class StaticPlatform : public GameObject
{
public:
    StaticPlatform(b2Vec2 position, b2Vec2 size, float angle = 0.0f, float restitution = 0.6f);
    ~StaticPlatform();
    
    const char* getType();
};

#endif /* defined(__GameDevFramework__StaticPlatform__) */
