//
//  KinematicPlatform.h
//  GameDevFramework
//
//  Created by Bradley Flood on 2014-04-02.
//  Copyright (c) 2014 Algonquin College. All rights reserved.
//

#ifndef __GameDevFramework__KinematicPlatform__
#define __GameDevFramework__KinematicPlatform__

#include "GameObject.h"


class KinematicPlatform : public GameObject
{
public:
    KinematicPlatform(b2Vec2 position, b2Vec2 size, b2Vec2 linearVelocity, b2Vec2 minLimits, b2Vec2 maxLimits);
    ~KinematicPlatform();
    
    const char* getType();
    
    void update(double delta);
    
private:
    b2Vec2 m_MinLimits;
    b2Vec2 m_MaxLimits;
};

#endif /* defined(__GameDevFramework__KinematicPlatform__) */
