#include "CollisionManager.h"
#include "Collision.h"
#include "Player.h"
#include "Enemy.h"
#include "BulletHandler.h"

void CollisionManager::checkPlayerEnemyBulletCollision(Player *pPlayer)
{
	SDL_Rect *pRect1 = new SDL_Rect();
	pRect1->x = int(pPlayer->getPosition().getX());
	pRect1->y = int(pPlayer->getPosition().getY());
	pRect1->w = pPlayer->getWidth();
	pRect1->h = pPlayer->getHeight();

	for (auto i : TheBulletHandler::Instance()->getEnemyBullets())
	{
		SDL_Rect *pRect2 = new SDL_Rect();
		pRect2->x = int(i->getPosition().getX());
		pRect2->y = int(i->getPosition().getY());
		pRect2->w = i->getWidth();
		pRect2->h = i->getHeight();

		if (RectRect(pRect1, pRect2))
			if (!pPlayer->dying() && !i->dying())
			{
				i->collision();
				pPlayer->collision();
			}

		delete pRect2;
	}

	delete pRect1;
}

void CollisionManager::checkEnemyPlayerBulletCollision(const std::vector<GameObject *> &objects)
{
	for (auto i : objects)
	{
		if (i->type() != std::string("Enemy") || !i->updating())
			continue;

		SDL_Rect *pRect1 = new SDL_Rect();
		pRect1->x = int(i->getPosition().getX());
		pRect1->y = int(i->getPosition().getY());
		pRect1->w = i->getWidth();
		pRect1->h = i->getHeight();

		for (auto j : TheBulletHandler::Instance()->getPlayerBullets())
		{
			SDL_Rect *pRect2 = new SDL_Rect();
			pRect2->x = int(j->getPosition().getX());
			pRect2->y = int(j->getPosition().getY());
			pRect2->w = j->getWidth();
			pRect2->h = j->getHeight();
			if (RectRect(pRect1, pRect2))
			{
				std::cerr << "Collision detected!\n";
				if (!i->dying() && !j->dying())
				{
					i->collision();
					j->collision();
				}
			}
			delete pRect2;
		}
		delete pRect1;
	}
}

void CollisionManager::checkPlayerEnemyCollision(Player *pPlayer, const std::vector<GameObject *> &objects)
{
	SDL_Rect *pRect1 = new SDL_Rect();
	pRect1->x = int(pPlayer->getPosition().getX());
	pRect1->y = int(pPlayer->getPosition().getY());
	pRect1->w = pPlayer->getWidth();
	pRect1->h = pPlayer->getHeight();

	for (auto i : objects)
	{
		if (i->type() != std::string("Enemy") || !i->updating())
			continue;

		SDL_Rect* pRect2 = new SDL_Rect();
		pRect2->x = int(i->getPosition().getX());
		pRect2->y = int(i->getPosition().getY());
		pRect2->w = i->getWidth();
		pRect2->h = i->getHeight();

		if (RectRect(pRect1, pRect2))
			if (!i->dead() && !i->dying())
			{
				pPlayer->collision();
				i->collision();
			}

		delete pRect2;
	}

	delete pRect1;
}