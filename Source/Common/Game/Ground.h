//
//  Ground.h
//  GameDevFramework
//
//  Created by Bradley Flood on 2014-04-02.
//  Copyright (c) 2014 Algonquin College. All rights reserved.
//

#ifndef __GameDevFramework__Ground__
#define __GameDevFramework__Ground__

#include "GameObject.h"


class Ground : public GameObject
{
public:
    Ground(b2Body* body);
    ~Ground();
    
    const char* getType();
};

#endif /* defined(__GameDevFramework__Ground__) */
