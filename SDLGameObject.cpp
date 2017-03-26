#include "SDLGameObject.h"
#include "TextureManager.h"
#include "Game.h"

void SDLGameObject::draw(void)
{
	TheTextureManager::Instance()->drawFrame(m_textureID,
		static_cast<int>(m_position.getX()),
		static_cast<int>(m_position.getY()),
		m_width, m_height, m_currentRow, m_currentFrame,
		TheGame::Instance()->getRenderer());
}

void SDLGameObject::update(void) 
{
	m_velocity += m_acceleration;
	m_position += m_velocity;
}

void SDLGameObject::clean(void) {}

void SDLGameObject::load(const LoaderParams *pParams)
{
	m_position = Vector2D(static_cast<float>(pParams->getX()), static_cast<float>(pParams->getY()));
	m_velocity = Vector2D(0, 0);
	m_acceleration = Vector2D(0, 0);
	m_width = pParams->getWidth();
	m_height = pParams->getHeight();
	m_textureID = pParams->getTextureID();
	m_currentRow = 1;
	m_currentFrame = 0;
	m_numFrames = pParams->getNumFrames();
}