#ifndef GAME_CONSTANTS_H
#define GAME_CONSTANTS_H

#include "../../OpenGL/OpenGLColor.h"

//Game Constants
extern const char* GAME_SCREEN_NAME;

enum
{
	GameLoadStepInitial = 0,
	GameLoadStepWorld,
	GameLoadStepSensors,
	GameLoadStepGround,
	GameLoadStepPlatforms,
	GameLoadStepTurret,
	GameLoadStepFinal,
	GameLoadStepCount
};
typedef unsigned int GameLoadSteps;


extern const float GAME_GRAVITY_X;
extern const float GAME_GRAVITY_Y;

extern const char* GAME_PHYSICS_EDITOR_FILENAME;
extern const float GAME_PHYSICS_PIXELS_TO_METERS_RATIO;
extern const bool GAME_PHYSICS_CONTINUOUS_SIMULATION;
extern const int GAME_PHYSICS_VELOCITY_ITERATIONS;
extern const int GAME_PHYSICS_POSITION_ITERATIONS;

#endif 