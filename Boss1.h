#ifndef __Boss1__
#define __Boss1__

#include "Enemy.h"
#include "Game.h"

class Boss1 : public Enemy
{
public:

	virtual ~Boss1() {}

	Boss1() : Enemy()
	{
		m_health = 10;
		m_dyingTime = 100;
		m_bulletFiringSpeed = 100;

		m_moveSpeed = 2;

		m_entered = false;
	}

	virtual void load(std::unique_ptr<LoaderParams> const &pParams)
	{
		ShooterObject::load(std::move(pParams));
	}

	virtual void collision()
	{
		if (m_entered)
		{
			m_health -= 1;
			std::cerr << "Boss1 collision\n";
			if (m_health == 0)
			{
				if (!m_bPlayedDeathSound)
				{
					m_bDying = true;; // death procession
				}
			}
		}
	}

	virtual void update()
	{
		if (!m_entered)
		{
			scroll(TheGame::Instance()->getScrollSpeed());
			
			if (m_position.getY() > 0)
				m_entered = true;
		}
		else
		{
			if (!m_bDying)
			{
				ShooterObject::update();
			}
			else
			{
				scroll(TheGame::Instance()->getScrollSpeed());
				if (m_dyingCounter == m_dyingTime)
				{
					m_bDead = true;
					TheGame::Instance()->setLevelComplete(true);
				}
				m_dyingCounter++;
			}
		}
	}

private:

	bool m_entered;
};

class Boss1Creator : public BaseCreator
{
	GameObject *createGameObject() const
	{
		return new Boss1();
	}
};

#endif