//
//  KinematicPlatform.cpp
//  GameDevFramework
//
//  Created by Bradley Flood on 2014-04-02.
//  Copyright (c) 2014 Algonquin College. All rights reserved.
//

#include "KinematicPlatform.h"


KinematicPlatform::KinematicPlatform(b2Vec2 position, b2Vec2 size, b2Vec2 linearVelocity, b2Vec2 minLimits, b2Vec2 maxLimits) : GameObject()
{
    unsigned short platformMask = PlatformCategory | TurretCategory | ProjectileCategory;
    m_Body = Game::getInstance()->createBox(position, size, b2_kinematicBody, PlatformCategory, platformMask);
    m_Body->SetUserData(this);
    m_Body->GetFixtureList()->SetFriction(1.0f);

    //Set the bodies linear velocity
    m_Body->SetLinearVelocity(linearVelocity);
    
    //Set the min x and y limits
    m_MinLimits.x = minLimits.x;
    m_MinLimits.y = minLimits.y;
    
    //Set the min x and y limits
    m_MaxLimits.x = maxLimits.x;
    m_MaxLimits.y = maxLimits.y;
}

KinematicPlatform::~KinematicPlatform()
{

}
    
const char* KinematicPlatform::getType()
{
    return "KinematicPlatform";
}

void KinematicPlatform::update(double delta)
{
    GameObject::update(delta);
    
    //Check the bounds, reverse velocity if they have been reached
    if(getX() >= m_MaxLimits.x || getX() <= m_MinLimits.x)
    {
        m_Body->SetLinearVelocity(b2Vec2(m_Body->GetLinearVelocity().x * -1.0f, m_Body->GetLinearVelocity().y));
    }
    
    if(getY() >= m_MaxLimits.y || getY() <= m_MinLimits.y)
    {
        m_Body->SetLinearVelocity(b2Vec2(m_Body->GetLinearVelocity().x, m_Body->GetLinearVelocity().y * -1.0f));
    }
}
