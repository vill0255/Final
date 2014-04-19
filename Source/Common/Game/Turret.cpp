//
//  Turret.cpp
//  GameDevFramework
//
//  Created by Bradley Flood on 2014-04-02.
//  Copyright (c) 2014 Algonquin College. All rights reserved.
//

#include "Turret.h"
#include "Projectile.h"
#include "../Utils/Math/MathUtils.h"

Turret::Turret(float x, float y) : GameObject(),
    m_Barrel(NULL),
    m_BarrelJoint(NULL),
    m_ProjectileVelocity(60.0f, 0.0),
    m_CanRotate(false)
{
    //Set the turret's mask
    unsigned short turretMask = PlatformCategory;

    //Initialize the bodydef
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = b2Helper::screenSpaceToBox2dSpace(x, y);
    bodyDef.angle = 0.0f;
    
    //Create the turret's body, and set the user data
    m_Body = Game::getInstance()->createPhysicsBody(&bodyDef);
    m_Body->SetUserData(this);
    
    //Initialize the circle shape
    b2CircleShape circleShape;
    circleShape.m_radius = 0.5f;
    
    //Initialze the fixture def, and attach it to the body
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circleShape;
    fixtureDef.density = 1.0f;
    fixtureDef.filter.categoryBits = TurretCategory;
    fixtureDef.filter.maskBits = turretMask;
    m_Body->CreateFixture(&fixtureDef);
   
    //Initialize the back box shape
    b2PolygonShape boxShape;
    boxShape.SetAsBox(0.5f, 0.5f, b2Vec2(-1.0f, -2.0f), 0.0f);
    
    //Set the box shape for the fixture, and attach it to the body
    fixtureDef.shape = &boxShape;
    fixtureDef.density = 1.0f;
    fixtureDef.restitution = 0.4f;
    fixtureDef.friction = 1.0f;
    fixtureDef.filter.categoryBits = TurretCategory;
    fixtureDef.filter.maskBits = turretMask;
    m_Body->CreateFixture(&fixtureDef);
    
    //Initialize the front box shape
    boxShape.SetAsBox(0.5f, 0.5f, b2Vec2(1.0f, -2.0f), 0.0f);
    
    //Set the box shape for the fixture, and attach it to the body
    fixtureDef.shape = &boxShape;
    fixtureDef.density = 1.0f;
    fixtureDef.restitution = 0.4f;
    fixtureDef.friction = 1.0f;
    fixtureDef.filter.categoryBits = TurretCategory;
    fixtureDef.filter.maskBits = turretMask;
    m_Body->CreateFixture(&fixtureDef);
    
    //Initialize the edge shape
    b2EdgeShape edgeShape;
    edgeShape.Set(b2Vec2(0.0f, 0.0f), b2Vec2(-1.0f, -2.0f));
    
    //Set the edge shape for the fixture, and attach it to the body
    fixtureDef.shape = &edgeShape;
    fixtureDef.density = 1.0f;
    fixtureDef.filter.categoryBits = TurretCategory;
    fixtureDef.filter.maskBits = turretMask;
    m_Body->CreateFixture(&fixtureDef);
    
    //Initialize the edge shape
    edgeShape.Set(b2Vec2(0.0f, 0.0f), b2Vec2(1.0f, -2.0f));
    
    //Set the edge shape for the fixture, and attach it to the body
    fixtureDef.shape = &edgeShape;
    fixtureDef.density = 1.0f;
    fixtureDef.filter.categoryBits = TurretCategory;
    fixtureDef.filter.maskBits = turretMask;
    m_Body->CreateFixture(&fixtureDef);
    
    //Initialize the barrel def
    b2BodyDef barrelDef;
    barrelDef.type = b2_dynamicBody;
    barrelDef.position = b2Helper::screenSpaceToBox2dSpace(x, y);
    barrelDef.angle = 0.0f;
    
    //Initialize the barrel shape
    b2PolygonShape barrelShape;
    barrelShape.SetAsBox(1.5f, 0.25f, b2Vec2(0.8f, 0.0f), 0.0f);
    
    //Set the barrel shape for the fixture
    fixtureDef.shape = &barrelShape;
    fixtureDef.density = 1.0f;
    fixtureDef.filter.categoryBits = TurretCategory;
    fixtureDef.filter.maskBits = turretMask;
    
    //Create the barrel body
    m_Barrel = Game::getInstance()->createPhysicsBody(&barrelDef, &fixtureDef);
    m_Barrel->SetUserData(this);
    
    //Initialize the revolute joint def
    b2RevoluteJointDef barrelJointDef;
    barrelJointDef.Initialize(m_Body, m_Barrel, m_Body->GetPosition());
    barrelJointDef.lowerAngle = 0.0f;
    barrelJointDef.upperAngle = MathUtils::degressToRadians(75.0f);
    barrelJointDef.enableLimit = true;
    
    //Create the revolute joint
    m_BarrelJoint = (b2RevoluteJoint*)Game::getInstance()->createJoint(&barrelJointDef);
    
    m_Barrel->SetTransform(m_Barrel->GetPosition(), MathUtils::degressToRadians(15));
}

Turret::~Turret()
{

}
    
const char* Turret::getType()
{
    return "Turret";
}

void Turret::update(double delta)
{
    GameObject::update(delta);
    
    m_TrajectoryPoints.clear();
    
    TrajectoryRaycastCallback raycastCallback;
    
    for(int i = 0; i < 360; i ++)
    {
        b2Vec2 trajectoryPoint = getTrajectoryPoint(i);
        
        if(i > 0)
        {
            Game::getInstance()->rayCast(&raycastCallback, m_TrajectoryPoints.at(i-1), trajectoryPoint);
            if(raycastCallback.didHit == true)
            {
                m_TrajectoryPoints.push_back(trajectoryPoint);
                break;
            }
        }
        
        m_TrajectoryPoints.push_back(trajectoryPoint);
    }
}

void Turret::paint()
{
    GameObject::paint();
    
    for(int i = 1; i < m_TrajectoryPoints.size(); i ++)
    {
        b2Vec2 point1 = b2Helper::box2dSpaceToScreenSpace(m_TrajectoryPoints.at(i-1));
        b2Vec2 point2 = b2Helper::box2dSpaceToScreenSpace(m_TrajectoryPoints.at(i));
        OpenGLRenderer::getInstance()->drawLine(point1.x, point1.y, point2.x, point2.y);
    }
}

void Turret::touchEvent(TouchEvent touchEvent, float locationX, float locationY, float previousX, float previousY)
{
    if(locationX > Game::getInstance()->getScreenWidth() / 2.0f)
    {
        if(touchEvent == TouchEventBegan)
        {
            Game::getInstance()->addGameObject(new Projectile(m_Barrel->GetPosition(), m_Barrel->GetAngle(), m_ProjectileVelocity));
        }
    }
    else
    {
        if(touchEvent == TouchEventEnded || touchEvent == TouchEventCancelled)
        {
            m_CanRotate = false;
            return;
        }

        if(touchEvent == TouchEventBegan)
        {
            b2Vec2 point = b2Helper::screenSpaceToBox2dSpace(locationX, locationY);
            bool containsTouch = false;
            
            //Check all the fixtures attached to the barrel to test
            //if the touch location is inside the fixture
            b2Fixture* fixture = m_Barrel->GetFixtureList();
            while(fixture != NULL && containsTouch == false)
            {
                containsTouch = fixture->TestPoint(point);
                fixture = fixture->GetNext();
            }
            
            //Did the fixture contain the touch location
            if(containsTouch == true)
            {
                m_CanRotate = true;
            }
        }
        
        if(m_CanRotate == true && touchEvent == TouchEventMoved)
        {
            float lowerAngle = m_BarrelJoint->GetLowerLimit();
            float upperAngle = m_BarrelJoint->GetUpperLimit();
            int diffX = locationX - b2Helper::box2dSpaceToScreenSpace(m_Barrel->GetPosition().x);
            int diffY = locationY - b2Helper::box2dSpaceToScreenSpace(m_Barrel->GetPosition().y);
            float angle = min(max(atan2f(diffY, diffX), lowerAngle), upperAngle);

            m_Barrel->SetTransform(m_Barrel->GetPosition(), angle);
        }
    }
}

b2Vec2 Turret::getTrajectoryPoint(float step)
{
    b2Vec2 position = m_Barrel->GetPosition();
    float angle = m_Barrel->GetAngle();
    
    b2Vec2 initialPosition = position + b2Mul(b2Rot(angle), b2Vec2(2.5f, 0.0f));
    b2Vec2 initialVelocity = b2Mul(b2Rot(angle), m_ProjectileVelocity);
    
    float time = 1/ FRAMES_PER_SECOND;
    b2Vec2 stepVelocity = time * initialVelocity;
    b2Vec2 stepGravity = time * time * Game::getInstance()->getGravity();
    
    return initialPosition + step * stepVelocity + 0.5f * (step * step + step) * stepGravity;
}



















