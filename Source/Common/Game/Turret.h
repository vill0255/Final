//
//  Turret.h
//  GameDevFramework
//
//  Created by Bradley Flood on 2014-04-02.
//  Copyright (c) 2014 Algonquin College. All rights reserved.
//

#ifndef __GameDevFramework__Turret__
#define __GameDevFramework__Turret__

#include "GameObject.h"
#include <vector>


class Turret : public GameObject
{
public:
    Turret(float x, float y);
    ~Turret();
    
    const char* getType();
    
    void update(double delta);
    void paint();

    void touchEvent(TouchEvent touchEvent, float locationX, float locationY, float previousX, float previousY);
    
    
private:
    b2Vec2 getTrajectoryPoint(float step);
    
	b2Body* m_sensorBody;
    b2Body* m_Barrel;
    b2RevoluteJoint* m_BarrelJoint;
    b2Vec2 m_ProjectileVelocity;
    bool m_CanRotate;
    std::vector<b2Vec2> m_TrajectoryPoints;
};

class TrajectoryRaycastCallback : public b2RayCastCallback
{
public:
    TrajectoryRaycastCallback() : didHit(false) {}
    
    float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction)
    {
        didHit = true;
        return fraction;
    }
    
    bool didHit;
};

#endif /* defined(__GameDevFramework__Turret__) */
