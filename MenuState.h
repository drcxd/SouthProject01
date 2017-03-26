#ifndef __MenuState__
#define __MenuState__

#include <vector>

#include "GameState.h"
#include "GameObject.h"

class MenuState : public GameState
{
public:

	virtual ~MenuState() {}
	// virtual void update(void);
	virtual void render(void);

protected:

	std::vector<GameObject *> m_gameObjects;
};

#endif