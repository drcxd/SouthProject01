#include "tinyxml.h"

#include "MainMenuState.h"
#include "SDLGameObject.h"
#include "Game.h"
#include "AudioManager.h"
#include "Button.h"
#include "PlayState.h"
#include "StateParser.h"
#include "InputHandler.h"

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

const std::string MainMenuState::s_menuID = "MENU";

bool MainMenuState::onEnter(void)
{
	StateParser stateParser;
	stateParser.parseState("scripts/states.xml", s_menuID, &m_gameObjects, &m_textureIDList);

	static_cast<Button *>(m_gameObjects[0])->setCallback(s_menuToPlay);
	static_cast<Button *>(m_gameObjects[1])->setCallback(s_exit);

	m_loadingComplete = true;

	return true;
}

bool MainMenuState::onExit(void)
{
	m_exiting = true;

	while (!m_gameObjects.empty())
	{
		m_gameObjects.back()->clean();
		m_gameObjects.pop_back();
	}

	m_gameObjects.clear();
	TheInputHandler::Instance()->reset();

	return true;
}

void MainMenuState::render()
{
	MenuState::render();
}

void MainMenuState::update(void)
{
	for (auto i = m_gameObjects.begin(); i != m_gameObjects.end(); ++i)
	{
		(*i)->update();
		if (m_exiting)
			return;
	}
}

void MainMenuState::s_menuToPlay(void)
{
	TheGame::Instance()->getStateMachine()->changeState(new PlayState());
}

void MainMenuState::s_exit(void)
{
	TheGame::Instance()->clean();
}