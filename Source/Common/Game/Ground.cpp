//
//  Ground.cpp
//  GameDevFramework
//
//  Created by Bradley Flood on 2014-04-02.
//  Copyright (c) 2014 Algonquin College. All rights reserved.
//

#include "Ground.h"


Ground::Ground(b2Body* body) : GameObject(body)
{

}

Ground::~Ground()
{

}
    
const char* Ground::getType()
{
    return "Ground";
}