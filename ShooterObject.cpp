#include "ShooterObject.h"
#include "Game.h"
#include "Vector2D.h"

void ShooterObject::load(std::unique_ptr<LoaderParams> const &pParams)
{
	m_position = Vector2D((float)pParams->getX(), (float)pParams->getY());
	m_width = pParams->getWidth();
	m_height = pParams->getHeight();
	m_textureID = pParams->getTextureID();
	m_numFrames = pParams->getNumFrames();
}

void ShooterObject::doDyingAnimation()
{
	scroll(TheGame::Instance()->getScrollSpeed());

	m_currentFrame = int(((SDL_GetTicks() / (1000 / 3)) % m_numFrames));

	if (m_dyingCounter == m_dyingTime)
		m_bDead = true;
	m_dyingCounter++;
}

void ShooterObject::draw()
{
	TheTextureManager::Instance()->drawFrame(m_textureID,
		static_cast<int>(m_position.getX()),
		static_cast<int>(m_position.getY()),
		m_width, m_height, m_currentRow, m_currentFrame,
		TheGame::Instance()->getRenderer());
}

void ShooterObject::update()
{
	m_velocity += m_acceleration;
	m_position += m_velocity;
}