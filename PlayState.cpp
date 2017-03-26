#include "PlayState.h"
#include "LevelParser.h"
#include "Game.h"
#include "InputHandler.h"
#include "BulletHandler.h"

const std::string PlayState::s_playID = "PLAY";

void PlayState::update(void)
{
	if (m_loadingComplete && !m_exiting)
	{
		TheBulletHandler::Instance()->updateBullets();

		if (pLevel != nullptr)
			pLevel->update();
	}
}

void PlayState::render(void)
{
	pLevel->render();

	TheBulletHandler::Instance()->drawBullets();
}

bool PlayState::onEnter(void)
{
	TheTextureManager::Instance()->load("image/bullet1.png", "bullet1", TheGame::Instance()->getRenderer());

	LevelParser levelParser;
	std::string levelFile;
	levelFile = TheGame::Instance()->getLevelFiles()[TheGame::Instance()->getCurrentLevel() - 1];
	pLevel = levelParser.parseLevel(levelFile.c_str());

	if (pLevel != nullptr)
		m_loadingComplete = true;

	return true;
}

bool PlayState::onExit(void)
{
	m_exiting = true;

	TheInputHandler::Instance()->reset();
	TheBulletHandler::Instance()->clearBullets();

	return true;
}
