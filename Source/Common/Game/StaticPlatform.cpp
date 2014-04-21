//
//  StaticPlatform.cpp
//  GameDevFramework
//
//  Created by Bradley Flood on 2014-04-02.
//  Copyright (c) 2014 Algonquin College. All rights reserved.
//

#include "StaticPlatform.h"


StaticPlatform::StaticPlatform(b2Vec2 position, b2Vec2 size, float angle, float restitution) : GameObject()
{
    unsigned short platformMask = PlatformCategory | TurretCategory | ProjectileCategory;
    m_Body = Game::getInstance()->createBox(position, size, angle, b2_staticBody, PlatformCategory, platformMask);
    m_Body->SetUserData(this);
    m_Body->GetFixtureList()->SetRestitution(restitution);
}

StaticPlatform::~StaticPlatform()
{

}
    
const char* StaticPlatform::getType()
{
    return "StaticPlatform";
}
