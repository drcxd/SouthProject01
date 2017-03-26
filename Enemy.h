#ifndef __Enemy__
#define __Enemy__

#include "ShooterObject.h"

class Enemy : public ShooterObject
{
public:

	virtual std::string type() { return "Enemy"; }

protected:

	int m_health = 0;

	Enemy() = default;
	virtual ~Enemy() {}
};

#endif // !__
