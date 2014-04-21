#include "BackgroundLayer.h"
#include "../Utils/Utils.h"

BackgroundLayer::BackgroundLayer(float speed, float x, float y) :
m_Texture1X(0.0f),
m_Texture2X(0.0f),
m_PreviousSegment(-1)
{
	m_Speed = speed;
	setX(x);
	setY(y);

}

BackgroundLayer::~BackgroundLayer()
{
	for (int i = 0; i < m_TextureSegments.size(); i++)
	{
		delete m_TextureSegments[i];
	}
	m_TextureSegments.clear();

	m_ActiveSegments.clear();
}

const char* BackgroundLayer::getType()
{
	return "BackgroundLayer";
}

void BackgroundLayer::update(double delta)
{
	//Determine width of current texture
	int width = (m_ActiveSegments[0]->getSourceWidth());

	if (m_Texture1X <= -width)
	{
		//remove segment from active
		m_ActiveSegments.erase(m_ActiveSegments.begin());

		//Initilize random number generation
		GDRandom random;
		random.randomizeSeed();

		int randTexIndex = 0;

		//If texture is the same as the previous one continue to randomize
		do	{

			float randomNumber = random.random() * 1000;
			//Calculate random texture
			randTexIndex = (int)randomNumber % m_TextureSegments.size();

		} while (randTexIndex == m_PreviousSegment);

		//Add texture to active array
		m_ActiveSegments.push_back(m_TextureSegments[randTexIndex]);

		//Remember this texture for next random choosing
		m_PreviousSegment = randTexIndex;

		//Reset texture positions
		m_Texture1X = 0;
		m_Texture2X = m_ActiveSegments[0]->getSourceWidth();
	}

	//Increment position
	m_Texture1X -= m_Speed * (float)delta;
	m_Texture2X -= m_Speed * (float)delta;
}

void BackgroundLayer::paint()
{
	if (m_ActiveSegments.size() == 2)
	{
		OpenGLRenderer::getInstance()->drawTexture(m_ActiveSegments[0], (int)m_Texture1X, getY());
		OpenGLRenderer::getInstance()->drawTexture(m_ActiveSegments[1], (int)m_Texture2X, getY());
	}
}

void BackgroundLayer::reset()
{
	//Clear active segments
	m_ActiveSegments.clear();

	//Assign two random segments
	for (int i = 0; i < 2; i++)
	{
		//Initilize random number generation
		GDRandom random;
		random.randomizeSeed();

		int randTexIndex = 0;

		//If texture is the same as the previous one continue to randomize
		do	{

			float randomNumber = random.random() * 1000;
			//Calculate random texture
			randTexIndex = (int)randomNumber % m_TextureSegments.size();

		} while (randTexIndex == m_PreviousSegment);

		//Add texture to active array
		m_ActiveSegments.push_back(m_TextureSegments[randTexIndex]);

		//Remember this texture for next random choosing
		m_PreviousSegment = randTexIndex;
	}


	//Reset positions
	m_Texture1X = 0;
	m_Texture2X = m_ActiveSegments[0]->getSourceWidth();
}

void BackgroundLayer::addTexture(const char* texturePath)
{
	//Create new texture
	OpenGLTexture * texture = new OpenGLTexture(texturePath);

	//Add to segments array
	m_TextureSegments.push_back(texture);
}
