#ifndef PARALLAX_BACKGROUND_H
#define PARALLAX_BACKGROUND_H

#include "GameObject.h"
#include "BackgroundLayer.h"
#include <vector>

class ParallaxBackground : GameObject
{
public:
	ParallaxBackground(float xPos, float yPos);
	~ParallaxBackground();

	const char* getType();

	void update(double delta);
	void paint();
	void reset();

	void addLayer(float speed);

	std::vector<BackgroundLayer*> getLayers();

protected:

	std::vector<BackgroundLayer*> m_BkgLayers;

};

#endif