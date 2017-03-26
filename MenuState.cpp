#include "MenuState.h"

void MenuState::render(void)
{
	for (auto i = m_gameObjects.begin(); i != m_gameObjects.end(); ++i)
		(*i)->draw();
}