#ifndef __Fairy__
#define __Fairy__

#include "Enemy.h"
#include "Game.h"
#include "BulletHandler.h"
#include "GameObjectFactory.h"

class Fairy : public Enemy
{
public:

	virtual ~Fairy() {}

	Fairy() : Enemy()
	{
		m_dyingTime = 50;
		m_health = 3;
		m_moveSpeed = 3;
		m_bulletFiringSpeed = 50;
	}

	virtual void collision()
	{
		m_health -= 1;

		if (m_health == 0)
			if (!m_bPlayedDeathSound)
				m_bDying = true;
	}

	virtual void update()
	{
		if (!m_bDying)
		{
			scroll(TheGame::Instance()->getScrollSpeed());
			m_velocity.setY(m_moveSpeed);

			if (m_bulletCounter == m_bulletFiringSpeed)
			{
				TheBulletHandler::Instance()->addEnemyBullet(m_position.getX() - 10, m_position.getY(), 10, 10, "bullet1",
					1, Vector2D(0, 3));
				TheBulletHandler::Instance()->addEnemyBullet(m_position.getX() + 10, m_position.getY(), 10, 10, "bullet1",
					1, Vector2D(0, 3));
				m_bulletCounter = 0;
			}
			++m_bulletCounter;
		}
		else
		{
			m_velocity.setY(0);
			doDyingAnimation();
		}
		ShooterObject::update();
	}
};

class FairyCreator : public BaseCreator
{
	GameObject *createGameObject() const
	{
		return new Fairy();
	}
};

#endif