//
//  Projectile.cpp
//  GameDevFramework
//
//  
//  Copyright (c) 2014 Algonquin College. All rights reserved.
//

#include "Projectile.h"
#include "../Utils/Math/MathUtils.h"


Projectile::Projectile(b2Vec2 aPosition, float aAngle, b2Vec2 aLinearVelocity) : GameObject()
{
    unsigned short projectileMask = PlatformCategory | ProjectileCategory;
    b2Vec2 position = aPosition + b2Mul(b2Rot(aAngle), b2Vec2(2.5f,0));

    b2BodyDef projectileDef;
    projectileDef.type = b2_dynamicBody;
    projectileDef.position = position;

    b2CircleShape projectileShape;
	projectileShape.m_radius = 0.35f; // projectile shape

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &projectileShape;
    fixtureDef.density = 0.5f;
    fixtureDef.restitution = 0.0f;
    fixtureDef.friction = 1.0f;
    fixtureDef.filter.categoryBits = ProjectileCategory;
    fixtureDef.filter.maskBits = projectileMask;

    m_Body = Game::getInstance()->createPhysicsBody(&projectileDef, &fixtureDef);
    m_Body->SetUserData(this);

    b2Vec2 velocity = b2Mul(b2Rot(aAngle), aLinearVelocity);
    m_Body->SetLinearVelocity(velocity);
    m_Body->SetAngularVelocity(MathUtils::degressToRadians(180.0f));
}

Projectile::~Projectile()
{

}
    
const char* Projectile::getType()
{
    return "Projectile";
}