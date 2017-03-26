#ifndef __Player__
#define __Player__

#include "ShooterObject.h"
#include "GameObjectFactory.h"

class Player : public ShooterObject
{
public:

	Player();
	virtual ~Player() {}

	virtual void load(std::unique_ptr<LoaderParams> const &pParams);
	virtual void draw();
	virtual void update();
	virtual void clean();

	virtual void collision();
	virtual std::string type() { return "Player"; }

private:

	void ressurect();
	void handleInput();
	void handleAnimation();

	bool m_invulnerable;
	int m_invulnerableTime;
	int m_invulnerableCounter;
};

class PlayerCreator : public BaseCreator
{
	GameObject *createGameObject() const
	{
		return new Player();
	}
};

#endif // !__Player__
