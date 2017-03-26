#ifndef __ShooterObject__
#define __ShooterObject__

#include "GameObject.h"

class ShooterObject : public GameObject
{
public:

	virtual ~ShooterObject() {}
	virtual void load(std::unique_ptr<LoaderParams> const &pParams);
	virtual void draw();
	virtual void update();
	virtual void clean() {}
	virtual void collision() {}
	virtual std::string type() { return "ShooterObject"; }

protected:
	
	// Won't creat ShooterObject instance
	ShooterObject() = default;
	// Draw animation for object being destroyed
	void doDyingAnimation();
	// how fast will this object fire bullets?
	int m_bulletFiringSpeed = 0;
	int m_bulletCounter = 0;
	// how fast will this object move?
	int m_moveSpeed = 0;
	// how long will the death animation takes?
	int m_dyingTime = 0;
	int m_dyingCounter = 0;
	// has the sound effect played?
	bool m_bPlayedDeathSound = false;
};

#endif // !__ShooterObject__
