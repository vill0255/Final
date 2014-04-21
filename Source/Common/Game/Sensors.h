//
//  Sensors.h
//  GameDevFramework
//
//  Created by Samueldarren Villeneuve on 2014-04-21.
//  Copyright (c) 2014 Algonquin College. All rights reserved.
//

#ifndef __GameDevFramework__Sensors__
#define __GameDevFramework__Sensors__

#include "GameObject.h"


class Sensors : public GameObject
{
public:
    Sensors(b2Vec2 position, b2Vec2 size);
    ~Sensors();
    
    const char* getType();
    
    void update(double delta);
    
private:
    b2Vec2 m_MinLimits;
    b2Vec2 m_MaxLimits;
};

#endif /* defined(__GameDevFramework__Sensors__) */
