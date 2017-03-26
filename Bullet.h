#ifndef __PlayerBullet__
#define __PlayerBullet__

#include <utility>

#include "ShooterObject.h"

class PlayerBullet : public ShooterObject
{
public:

	PlayerBullet() : ShooterObject() {}
	virtual ~PlayerBullet() {}

	virtual std::string type() { return "PlayerBullet"; }
	virtual void load(std::unique_ptr<LoaderParams> const &pParams, Vector2D heading)
	{
		ShooterObject::load(std::move(pParams));
		m_heading = heading;
	}

	virtual void draw()
	{
		ShooterObject::draw();
	}

	virtual void collision()
	{
		m_bDying = true;
	}

	virtual void update()
	{
		if (!m_bDying)
		{
			m_velocity.setX(m_heading.getX());
			m_velocity.setY(m_heading.getY());
			ShooterObject::update();
		}
		else
		{
			m_velocity.setX(0);
			m_velocity.setY(0);
			doDyingAnimation();
		}
	}

	virtual void clean()
	{
		ShooterObject::clean();
	}

private:

	Vector2D m_heading;
};


class EnemyBullet : public PlayerBullet
{
public:

	EnemyBullet() : PlayerBullet() {}
	virtual ~EnemyBullet() {}
	virtual std::string type() { return "EnemyBullet"; }
};
#endif 