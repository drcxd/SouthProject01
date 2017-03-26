#include "Player.h"
#include "Game.h"
#include "InputHandler.h"
#include "AudioManager.h"
#include "BulletHandler.h"

Player::Player() : ShooterObject(), m_invulnerable(false),
m_invulnerableTime(200), m_invulnerableCounter(0)
{
}

void Player::load(std::unique_ptr<LoaderParams> const &pParams)
{
	ShooterObject::load(pParams);
	m_bulletFiringSpeed = 13;
	m_moveSpeed = 3;
	m_bulletCounter = m_bulletFiringSpeed;
	m_dyingTime = 100;
}

void Player::draw()
{
	ShooterObject::draw();
}

void Player::clean()
{
	ShooterObject::clean();
}

void Player::collision()
{
	if (!m_invulnerable && !TheGame::Instance()->getLevelComplete())
	{
		// hardcode
		/*m_textureID = "largeexplosion";
		m_currentFrame = 0;
		m_numFrames = 9;
		m_width = 60;
		m_height = 60;
		m_bDying = true;*/

		std::cerr << "Player collision!\n";
	}
}

void Player::ressurect()
{
	TheGame::Instance()->setPlayerLives(TheGame::Instance()->getPlayerLives() - 1);

	m_position.setX(640);
	m_position.setY(100);
	m_bDying = false;

	m_textureID = "player";

	// hardcode
	m_currentFrame = 0;
	m_numFrames = 0;
	m_width = 101;
	m_height = 46;
	
	m_dyingCounter = 0;
	m_invulnerable = true;
}

void Player::handleInput()
{
	if (!m_bDead)
	{
		if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP) && m_position.getY() > 0)
			m_velocity.setY((float)-m_moveSpeed);
		else if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN) &&
			(m_position.getY() + m_height) < TheGame::Instance()->getGameHeight() - 10)
			m_velocity.setY((float)m_moveSpeed);

		if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT) && m_position.getX() > 0)
			m_velocity.setX((float)-m_moveSpeed);
		else if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT)
			&& (m_position.getX() + m_width) < TheGame::Instance()->getGameWidth())
			m_velocity.setX((float)m_moveSpeed);

		if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_SPACE))
		{
			if (m_bulletCounter == m_bulletFiringSpeed)
			{
				// hardcode
				// TheAudioManager::Instance()->playSound("shoot", 0);
				TheBulletHandler::Instance()->addPlayerBullet(int(m_position.getX()) + m_width / 2,
					int(m_position.getY()) + m_height, 10, 10, "bullet1", 1, Vector2D(0, -3));
				m_bulletCounter = 0;
			}

			m_bulletCounter++;
		}
		else
		{
			m_bulletCounter = m_bulletFiringSpeed;
		}
	}
}

void Player::handleAnimation()
{
	if (m_invulnerable)
	{
		if (m_invulnerableCounter == m_invulnerableTime)
		{
			m_invulnerable = false;
			m_invulnerableCounter = 0;
			m_alpha = 255;
		}
		else
		{
			if (m_alpha = 255)
				m_alpha = 0;
			else
				m_alpha = 255;
		}
		m_invulnerableCounter++;
	}
}

void Player::update()
{
	if (TheGame::Instance()->getLevelComplete())
	{
		if (m_position.getY() < 0)
			TheGame::Instance()->setCurrentLevel(TheGame::Instance()->getCurrentLevel() + 1);
		else
		{
			m_velocity.setY(-3);
			m_velocity.setX(0);
			ShooterObject::update();
			handleAnimation();
		}
	}
	else
	{
		if (!m_bDying)
		{
			m_velocity.setX(0);
			m_velocity.setY(0);

			handleInput();
			ShooterObject::update();
			handleAnimation();
		}
		else
		{
			m_currentFrame = int((SDL_GetTicks() / 100) % m_numFrames); // hardcode
			if (m_dyingCounter == m_dyingTime)
				ressurect();
			++m_dyingCounter;
		}
	}
}