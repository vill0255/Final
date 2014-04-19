#ifndef GAME_H
#define GAME_H

#include "../Constants/Constants.h"
#include <vector>
#include "../Screen Manager/Screen.h"
#include "../Libraries/Box2D/Box2D.h"

enum Categories
{
	PlatformCategory = 1,
	TurretCategory = 2,
	ProjectileCategory = 4
};

class GameObject;
class ParallaxBackground;
class OpenGLTexture;
class Turret;

class Game : public Screen, public b2ContactListener
{
public:
	static Game* getInstance();	

	//Game lifecycle methods
	void update(double delta);
	void paint();
	void touchEvent(TouchEvent touchEvent, float locationX, float locationY, float previousX, float previousY);

	//Reset methods
	void reset();

	//Conveniance methods to access the screen's width and height
	float getScreenWidth();
	float getScreenHeight();
	float getScale();

	//Loading methods
	bool isLoading();

	//Game Object Helpers
	void addGameObject(GameObject* addGameObject);

	//Box2D helper methods
	b2Body* createPhysicsBody(const b2BodyDef* bodyDef, const b2FixtureDef* fixtureDef = NULL);
	void destroyPhysicsBody(b2Body* body);

	b2Joint* createJoint(const b2JointDef* jointDef);
	void destroyJoint(b2Joint* joint);

	b2Body* createBox(b2Vec2 position, b2Vec2 size, b2BodyType bodyType, unsigned short category, unsigned short mask);
	b2Body* createBox(b2Vec2 position, b2Vec2 size, float angle, b2BodyType bodyType, unsigned short category, unsigned short mask);

	b2Body* createCircle(b2Vec2 position, float radius, b2BodyType bodyType, unsigned short category, unsigned short mask);
	b2Body* createCircle(b2Vec2 position, float radius, float angle, b2BodyType bodyType, unsigned short category, unsigned short mask);

	b2Vec2 getGravity();

	void rayCast(b2RayCastCallback* rayCastCallback, b2Vec2 point1, b2Vec2 point2);

	//b2ContactListener methods
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);

	//Screen name, must be implemented, it's a pure
	//virtual method in the Screen class
	const char* getName();

private:
	Game();
	~Game();

	//Load method, called once every load step
	void load();

	//Singleton instance static member variable
	static Game* m_Instance;

	//Load step member variable
	int m_LoadStep;

	//Box2D members
	b2World* m_World;
	b2DebugDraw* m_DebugDraw;

	std::vector<GameObject*> m_GameObjects;
	Turret* m_Turret;
};

#endif