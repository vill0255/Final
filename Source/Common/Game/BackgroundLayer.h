#ifndef BACKGROUND_LAYER_H
#define BACKGROUND_LAYER_H

#include "GameObject.h"
#include "../OpenGL/OpenGL.h"
#include <vector>

class BackgroundLayer : GameObject
{
public:
	BackgroundLayer(float speed, float x, float y);
	~BackgroundLayer();

	const char* getType();

	void update(double delta);
	void paint();
	void reset();

	void addTexture(const char* texturePath);

protected:
	std::vector<OpenGLTexture*> m_TextureSegments;
	std::vector<OpenGLTexture*> m_ActiveSegments;
	int m_PreviousSegment;
	float m_Speed;
	float m_Texture1X;
	float m_Texture2X;
};

#endif