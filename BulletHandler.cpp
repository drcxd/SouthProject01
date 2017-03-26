#include "BulletHandler.h"
#include "Game.h"

#include <iostream>

BulletHandler *BulletHandler::s_pInstance = nullptr;

void BulletHandler::addPlayerBullet(int x, int y, int width, int height, std::string textureID,
	int numFrames, Vector2D heading)
{
	PlayerBullet *pPlayerBullet = new PlayerBullet();
	pPlayerBullet->load(std::unique_ptr<LoaderParams>(new LoaderParams(x, y, width, height, textureID, numFrames)), heading);
	// std::cerr << x << " " << y << " " << width << " " << height << " " << textureID << " " << heading.getX() << " " << heading.getY() << std::endl;

	m_playerBullets.push_back(pPlayerBullet);
}

void BulletHandler::addEnemyBullet(int x, int y, int width, int height, std::string textureID,
	int numFrames, Vector2D heading)
{
	EnemyBullet *pEnemyBullet = new EnemyBullet();
	pEnemyBullet->load(std::unique_ptr<LoaderParams>(new LoaderParams(x, y, width, height, textureID, numFrames)), heading);

	m_enemyBullets.push_back(pEnemyBullet);
}

void BulletHandler::updateBullets()
{
	for (auto it = m_playerBullets.begin(); it != m_playerBullets.end();)
	{
		if ((*it)->getPosition().getX() < 0 || (*it)->getPosition().getX() > TheGame::Instance()->getGameWidth() ||
			(*it)->getPosition().getY() < 0 || (*it)->getPosition().getY() > TheGame::Instance()->getGameHeight() ||
			(*it)->dead())
		{
			delete *it;
			it = m_playerBullets.erase(it);
		}
		else
		{
			(*it)->update();
			++it;
		}
	}

	for (auto it = m_enemyBullets.begin(); it != m_enemyBullets.end();)
	{
		if ((*it)->getPosition().getX() < 0 || (*it)->getPosition().getX() > TheGame::Instance()->getGameWidth() ||
			(*it)->getPosition().getY() < 0 || (*it)->getPosition().getY() > TheGame::Instance()->getGameHeight() ||
			(*it)->dead())
		{
			delete *it;
			it = m_enemyBullets.erase(it);
		}
		else
		{
			(*it)->update();
			++it;
		}
	}
}

void BulletHandler::drawBullets()
{
	for (auto i : m_playerBullets)
		i->draw();
	for (auto i : m_enemyBullets)
		i->draw();
}

void BulletHandler::clearBullets()
{
	m_enemyBullets.clear();
	m_playerBullets.clear();
}