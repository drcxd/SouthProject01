#include "ObjectLayer.h"
#include "Game.h"

void ObjectLayer::update(Level *pLevel)
{
	m_collisionManager.checkPlayerEnemyBulletCollision(pLevel->getPlayer());
	m_collisionManager.checkEnemyPlayerBulletCollision((const std::vector<GameObject*>&)m_gameObjects);
	m_collisionManager.checkPlayerEnemyCollision(pLevel->getPlayer(), (const std::vector<GameObject*>&)m_gameObjects);

	if (!m_gameObjects.empty())
	{
		for (auto it = m_gameObjects.begin(); it != m_gameObjects.end();)
		{
			if ((*it)->getPosition().getY() > 0)
			{
				(*it)->setUpdating(true);
				(*it)->update();
			}
			else
			{
				if ((*it)->type() != std::string("Player"))
				{
					(*it)->setUpdating(false);
					(*it)->scroll(TheGame::Instance()->getScrollSpeed());
				}
				else
					(*it)->update();
			}

			if (/*(*it)->getPosition().getY() < (0 - (*it)->getHeight()) ||*/
				(*it)->getPosition().getY() > TheGame::Instance()->getGameHeight() ||
				(*it)->dead())
			{
				delete *it;
				it = m_gameObjects.erase(it);
			}
			else
			{
				++it;
			}
		}
	}
}

void ObjectLayer::render()
{
	for (auto i : m_gameObjects)
		i->draw();
}

ObjectLayer:: ~ObjectLayer()
{
	for (auto i : m_gameObjects)
		delete i;
	m_gameObjects.clear();
}