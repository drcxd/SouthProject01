#include "Level.h"

void Level::update()
{
	for (auto it = m_layers.begin(); it != m_layers.end(); ++it)
		(*it)->update(this);
}

void Level::render()
{
	for (auto it = m_layers.begin(); it != m_layers.end(); ++it)
		(*it)->render();
}

Level:: ~Level()
{
	for (auto i : m_layers)
		delete i;
	m_layers.clear();
}