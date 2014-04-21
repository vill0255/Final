#include "Game.h"
#include "GameObject.h"
#include "../OpenGL/OpenGL.h"
#include "../Constants/Constants.h"
#include "../Utils/Utils.h"
#include "../Screen Manager/ScreenManager.h"
#include "Ground.h"
#include "StaticPlatform.h"
#include "KinematicPlatform.h"
#include "Turret.h"
#include <vector>

Game* Game::m_Instance = NULL;

Game* Game::getInstance()
{
	//Singleton design pattern ensures that there is only 1 instance of the game
	if (m_Instance == NULL)
	{
		m_Instance = new Game();
	}
	return m_Instance;
}

Game::Game() :
m_LoadStep(0),
m_sensorBody(NULL),
m_World(NULL),
m_DebugDraw(NULL),
m_Turret(NULL)
{
	m_BackgroundTexture = new OpenGLTexture("background");
}

Game::~Game()
{
	if(m_BackgroundTexture !=NULL)
	{
		delete m_BackgroundTexture;
		m_BackgroundTexture = 0;
	}

	for (int i = 0; i < m_GameObjects.size(); i++)
	{
		delete m_GameObjects.at(i);
		m_GameObjects.at(i) = NULL;
	}
	m_GameObjects.clear();

	//Delete the debug draw instance
	if (m_DebugDraw != NULL)
	{
		delete m_DebugDraw;
		m_DebugDraw = NULL;
	}

	//Delete the Box2D world instance, MAKES SURE this is the last object deleted
	if (m_World != NULL)
	{
		//Destroy all the bodies in the world
		b2Body* body = m_World->GetBodyList();
		while (body != NULL)
		{
			//Destroy the body and get the next body (if there is one)
			b2Body* nextBody = body->GetNext();
			destroyPhysicsBody(body);
			body = nextBody;
		}

		//Finally delete the world
		delete m_World;
		m_World = NULL;
	}
}

void Game::load()
{
	switch (m_LoadStep)
	{
	case GameLoadStepInitial:
	{
		//TODO: Load game content required for future load steps here
	}
		break;

	case GameLoadStepWorld:
	{
		//Define the gravity vector.
		b2Vec2 gravity;
		gravity.Set(GAME_GRAVITY_X, GAME_GRAVITY_Y);

		//Construct the Box2d world object, which will
		//holds and simulates the rigid bodies
		m_World = new b2World(gravity);
		m_World->SetContinuousPhysics(GAME_PHYSICS_CONTINUOUS_SIMULATION);
		m_World->SetContactListener(this);

#if _DEBUG
		//Create the debug draw for Box2d
		m_DebugDraw = new b2DebugDraw(b2Helper::box2dRatio());

		//Set the debug draw flags
		uint32 flags = 0;
		flags += b2Draw::e_shapeBit;
		flags += b2Draw::e_jointBit;
		flags += b2Draw::e_centerOfMassBit;
		m_DebugDraw->SetFlags(flags);

		//Set the Box2d world debug draw instance
		m_World->SetDebugDraw(m_DebugDraw);
#endif
	}
		break;		

	case GameLoadStepSensors:
	{	
		
	}
		break;

	case GameLoadStepGround:
	{
		//Define the ground body.
		b2BodyDef groundBodyDef;
		groundBodyDef.position.Set(0.0f, 0.0f); // bottom-left corner

		//Define the ground box shape.
		b2EdgeShape groundShape;
		b2Vec2 vertex1 = b2Vec2(0.0f, 0.0f);
		b2Vec2 vertex2 = b2Helper::screenSpaceToBox2dSpace(getScreenWidth(), 0.0f);
		groundShape.Set(vertex1, vertex2);

		//Initialize the ground fixture def
		b2FixtureDef groundFixture;
		groundFixture.shape = &groundShape;
		groundFixture.friction = 1.0f;
		groundFixture.density = 0.0f;
		groundFixture.restitution = 0.2f;

		//Call the body factory which allocates memory for the ground body
		//from a pool and creates the ground box shape (also from a pool).
		//The body is also added to the world.
		b2Body* ground = createPhysicsBody(&groundBodyDef, &groundFixture);
		addGameObject(new Ground(ground));
	}
		break;
		
	case GameLoadStepPlatforms:
	{
		//cannon platform
		float x = getScreenWidth() * 0.01f;
		float y = getScreenHeight() * 0.1f;
		addGameObject(new StaticPlatform(b2Helper::screenSpaceToBox2dSpace(x, y), b2Vec2(5.5f, 2.0f)));
		
		//roof
		x = getScreenWidth() * 0.523f;
		y = getScreenHeight() * 0.99f;
		addGameObject(new StaticPlatform(b2Helper::screenSpaceToBox2dSpace(x, y), b2Vec2(19.0f, 0.2f), 180.0f));

		//far right pole pole
		x = getScreenWidth() * 0.95f;
		y = getScreenHeight() * 0.15f;
		addGameObject(new StaticPlatform(b2Helper::screenSpaceToBox2dSpace(x, y), b2Vec2(3.0f, 0.3f),  90.0f));

		//2nd from the right pole
		x = getScreenWidth() * 0.90f;
		y = getScreenHeight() * 0.15f;
		addGameObject(new StaticPlatform(b2Helper::screenSpaceToBox2dSpace(x, y), b2Vec2(3.0f, 0.3f),  90.0f));

		//3rd from the right pole
		x = getScreenWidth() * 0.83f;
		y = getScreenHeight() * 0.15f;
		addGameObject(new StaticPlatform(b2Helper::screenSpaceToBox2dSpace(x, y), b2Vec2(9.0f, 0.3f),  90.0f));

		//4th from the right pole
		x = getScreenWidth() * 0.78f;
		y = getScreenHeight() * 0.15f;
		addGameObject(new StaticPlatform(b2Helper::screenSpaceToBox2dSpace(x, y), b2Vec2(6.0f, 0.3f),  90.0f));
		
		//5th from the right
		x = getScreenWidth() * 0.70f;
		y = getScreenHeight() * 0.15f;
		addGameObject(new StaticPlatform(b2Helper::screenSpaceToBox2dSpace(x, y), b2Vec2(4.5f, 0.3f),  90.0f));
		
		//6th from the right
		x = getScreenWidth() * 0.64f;
		y = getScreenHeight() * 0.15f;
		addGameObject(new StaticPlatform(b2Helper::screenSpaceToBox2dSpace(x, y), b2Vec2(5.0f, 0.3f),  90.0f));
		
		//7th from the right
		x = getScreenWidth() * 0.56f;
		y = getScreenHeight() * 0.15f;
		addGameObject(new StaticPlatform(b2Helper::screenSpaceToBox2dSpace(x, y), b2Vec2(7.5f, 0.3f),  90.0f));
		
		//8th from the right
		x = getScreenWidth() * 0.50f;
		y = getScreenHeight() * 0.15f;
		addGameObject(new StaticPlatform(b2Helper::screenSpaceToBox2dSpace(x, y), b2Vec2(6.7f, 0.3f),  90.0f));
		
		//9th from the right
		x = getScreenWidth() * 0.43f;
		y = getScreenHeight() * 0.15f;
		addGameObject(new StaticPlatform(b2Helper::screenSpaceToBox2dSpace(x, y), b2Vec2(4.5f, 0.3f),  90.0f));
		
		//10th from the right
		x = getScreenWidth() * 0.36f;
		y = getScreenHeight() * 0.15f;
		addGameObject(new StaticPlatform(b2Helper::screenSpaceToBox2dSpace(x, y), b2Vec2(5.5f, 0.3f),  90.0f));
		
		//right wall
		x = getScreenWidth() * 0.999f;
		y = getScreenHeight() * 0.5f;
		addGameObject(new StaticPlatform(b2Helper::screenSpaceToBox2dSpace(x, y), b2Vec2(10.0f, 0.2f), 90.0f));
							
		x = getScreenWidth() * 0.5f;
		y = getScreenHeight() * 0.55f;
		float minX = getScreenWidth() * 0.350f;
		float maxX = getScreenWidth() * 0.650f;
		float minY = getScreenHeight() * 0.450f;
		float maxY = getScreenHeight() * 0.60f;
		addGameObject(new KinematicPlatform(b2Helper::screenSpaceToBox2dSpace(x, y), b2Vec2(2.0f, 0.2f), b2Vec2(2.5f, 0.0f), b2Vec2(minX, minY), b2Vec2(maxX, maxY)));

		x = getScreenWidth() * 0.7f;
		y = getScreenHeight() * 0.75f;
		 minX = getScreenWidth() * 0.40f;
		 maxX = getScreenWidth() * 0.750f;
		addGameObject(new KinematicPlatform(b2Helper::screenSpaceToBox2dSpace(x, y), b2Vec2(1.0f, 0.5f), b2Vec2(0.5f, 0.0f), b2Vec2(minX, y), b2Vec2(maxX, y)));

		x = getScreenWidth() *0.990f;
		y = getScreenHeight() * 0.50f;
	     minX = getScreenWidth() * 0.80f;
		 maxX = getScreenWidth() * 0.990f;
		addGameObject(new KinematicPlatform(b2Helper::screenSpaceToBox2dSpace(x, y), b2Vec2(2.0f, 0.5f), b2Vec2(2.5f, 0.0f), b2Vec2(minX, y), b2Vec2(maxX, y)));
	}

		break;

	case GameLoadStepTurret:
	{
		float x = getScreenWidth() * 0.0625f;
		float y = getScreenHeight() * 0.25f;
		m_Turret = new Turret(x, y);
		addGameObject(m_Turret);
	}
		break;

	case GameLoadStepFinal:
	{
		reset();
	}
		break;

	default:
		break;
	}

	//Increment the load step
	m_LoadStep++;
}

void Game::update(double delta)
{
	//While the game is loading, the load method will be called once per update
	if (isLoading() == true)
	{
		load();
		return;
	}

	//Step the Box2D world this update cycle
	if (m_World != NULL)
	{
		m_World->Step(delta, GAME_PHYSICS_VELOCITY_ITERATIONS, GAME_PHYSICS_POSITION_ITERATIONS);
	}

	//Update the game's game objects
	for (int i = 0; i < m_GameObjects.size(); i++)
	{
		m_GameObjects.at(i)->update(delta);
	}
}

void Game::paint()
{	

	//While the game is loading, the load method will be called once per update
	if (isLoading() == true)
	{
		//Cache the screen width and height
		float screenWidth = getScreenWidth();
		float screenHeight = getScreenHeight();

		//Draw a black background, you could replace this
		//in the future with a full screen background texture
		OpenGLRenderer::getInstance()->setForegroundColor(OpenGLColorBlack());
		OpenGLRenderer::getInstance()->drawRectangle(0.0f, 0.0f, screenWidth, screenHeight);

		//Calculate the bar width and height, don't actually hard-code these
		float barWidth = 200.0f * getScale();
		float barHeight = 40.0f * getScale();
		float barX = (screenWidth - barWidth) / 2.0f;
		float barY = (screenHeight - barHeight) / 2.0f;

		//
		float percentageLoaded = (float)m_LoadStep / (float)(GameLoadStepCount - 1);
		float loadedWidth = barWidth * percentageLoaded;
		OpenGLRenderer::getInstance()->setForegroundColor(OpenGLColorYellow());
		OpenGLRenderer::getInstance()->drawRectangle(barX, barY, loadedWidth, barHeight);

		//
		OpenGLRenderer::getInstance()->setForegroundColor(OpenGLColorWhite());
		OpenGLRenderer::getInstance()->drawRectangle(barX, barY, barWidth, barHeight, false);

		return;
	}

	OpenGLRenderer::getInstance()->drawTexture(m_BackgroundTexture,0.0f,0.0f);

#if _DEBUG
	if (m_World != NULL)
	{
		m_World->DrawDebugData();
	}
#endif

	//Paint the game's game objects
	for (int i = 0; i < m_GameObjects.size(); i++)
	{
		m_GameObjects.at(i)->paint();
	}
}

void Game::touchEvent(TouchEvent touchEvent, float locationX, float locationY, float previousX, float previousY)
{
	m_Turret->touchEvent(touchEvent, locationX, locationY, previousX, previousY);
}

void Game::addGameObject(GameObject* gameObject)
{
	if (gameObject != NULL)
	{
		m_GameObjects.push_back(gameObject);
	}
}

b2Body* Game::createPhysicsBody(const b2BodyDef* bodyDef, const b2FixtureDef* fixtureDef)
{
	if (bodyDef != NULL)
	{
		b2Body* body = m_World->CreateBody(bodyDef);

		if (fixtureDef != NULL)
		{
			body->CreateFixture(fixtureDef);
		}

		return body;
	}
	return NULL;
}

void Game::destroyPhysicsBody(b2Body* body)
{
	//Safety check that aBody isn't NULL
	if (body != NULL)
	{
		//Destroy all the fixtures attached to the body
		b2Fixture* fixture = body->GetFixtureList();
		while (fixture != NULL)
		{
			b2Fixture* nextFixture = fixture->GetNext();
			body->DestroyFixture(fixture);
			fixture = nextFixture;
		}

		//Destroy the body
		m_World->DestroyBody(body);
	}
}

b2Joint* Game::createJoint(const b2JointDef* jointDef)
{
	if (jointDef != NULL)
	{
		return m_World->CreateJoint(jointDef);
	}
	return NULL;
}

void Game::destroyJoint(b2Joint* joint)
{
	if (joint != NULL)
	{
		m_World->DestroyJoint(joint);
	}
}

b2Body* Game::createBox(b2Vec2 position, b2Vec2 size, b2BodyType bodyType, unsigned short category, unsigned short mask)
{
	return createBox(position, size, 0.0f, bodyType, category, mask);
}

b2Body* Game::createBox(b2Vec2 position, b2Vec2 size, float angle, b2BodyType bodyType, unsigned short category, unsigned short mask)
{
	b2BodyDef bodyDef;
	bodyDef.type = bodyType;
	bodyDef.position = position;
	bodyDef.angle = MathUtils::degressToRadians(angle);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(size.x, size.y);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxShape;
	fixtureDef.density = 1.0f;
	fixtureDef.filter.categoryBits = category;
	fixtureDef.filter.maskBits = mask;

	b2Body* body = createPhysicsBody(&bodyDef, &fixtureDef);
	return body;
}

b2Body* Game::createCircle(b2Vec2 position, float radius, b2BodyType bodyType, unsigned short category, unsigned short mask)
{
	return createCircle(position, radius, 0.0f, bodyType, category, mask);
}

b2Body* Game::createCircle(b2Vec2 position, float radius, float angle, b2BodyType bodyType, unsigned short category, unsigned short mask)
{
	b2BodyDef bodyDef;
	bodyDef.type = bodyType;
	bodyDef.position = position;
	bodyDef.angle = MathUtils::degressToRadians(angle);

	b2CircleShape circleShape;
	circleShape.m_radius = radius;

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circleShape;
	fixtureDef.density = 1.0f;
	fixtureDef.filter.categoryBits = category;
	fixtureDef.filter.maskBits = mask;

	b2Body* body = createPhysicsBody(&bodyDef, &fixtureDef);
	return body;
}

b2Vec2 Game::getGravity()
{
	if (m_World != NULL)
	{
		return m_World->GetGravity();
	}
	return b2Vec2(0.0f, 0.0f);
}

void Game::rayCast(b2RayCastCallback* rayCastCallback, b2Vec2 point1, b2Vec2 point2)
{
	if (m_World != NULL)
	{
		m_World->RayCast(rayCastCallback, point1, point2);
	}
}

void Game::BeginContact(b2Contact* contact)
{
	/*b2Fixture* fixtureA = contact->GetFixtureA();
	b2Body * bodyA = fixtureA->GetBody();
	GameObject * gameObjectA = (GameObject*)bodyA->GetUserData();

	b2Fixture* fixtureB = contact->GetFixtureB();
	b2Body * bodyB = fixtureB->GetBody();
	GameObject * gameObjectB = (GameObject*)bodyB->GetUserData();

	if(gameObjectA != NULL && !strcmp(gameObjectA->getType(), "Ground") && strcmp(gameObjectB->getType(), "Turret"))
	{
	gameObjectA->setBodyType(b2_dynamicBody);
	}

	if(gameObjectB != NULL && !strcmp(gameObjectB->getType(), "Ground") && strcmp(gameObjectA->getType(), "Turret"))
	{
	gameObjectB->setBodyType(b2_dynamicBody);
	}*/
}

void Game::EndContact(b2Contact* contact)
{

}

void Game::reset()
{
	//TODO: Reset all game content here
}

float Game::getScreenWidth()
{
	return 1136.0f;
}

float Game::getScreenHeight()
{
	return 640.0f;
}

float Game::getScale()
{
	return 2.0f;
}

bool Game::isLoading()
{
	return m_LoadStep < GameLoadStepCount;
}

const char* Game::getName()
{
	return GAME_SCREEN_NAME;
}