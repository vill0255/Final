#include "ParallaxBackground.h"
#include "../OpenGL/OpenGL.h"

ParallaxBackground::ParallaxBackground(float xPos, float yPos)
{
	setX(xPos);
	setY(yPos);
}

ParallaxBackground::~ParallaxBackground()
{
	for (int i = 0; i < m_BkgLayers.size(); i++)
	{
		delete m_BkgLayers[i];
	}
	m_BkgLayers.clear();
}

void ParallaxBackground::update(double delta)
{
	for (int i = 0; i < m_BkgLayers.size(); i++)
	{
		m_BkgLayers[i]->update(delta);
	}
}

void ParallaxBackground::paint()
{
	for (int i = 0; i < m_BkgLayers.size(); i++)
	{
		m_BkgLayers[i]->paint();
	}
}

void ParallaxBackground::reset()
{
	for (int i = 0; i < m_BkgLayers.size(); i++)
	{
		m_BkgLayers[i]->reset();
	}
}

const char* ParallaxBackground::getType()
{
	return "ParallaxBackground";
}

void ParallaxBackground::addLayer(float speed)
{
	BackgroundLayer * layer = new BackgroundLayer(speed, getX(), getY());
	m_BkgLayers.push_back(layer);
}

std::vector<BackgroundLayer*> ParallaxBackground::getLayers()
{
	return m_BkgLayers;
}