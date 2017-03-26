#include "GameStateMachine.h"

void GameStateMachine::pushState(GameState *pState)
{
	m_gameStates.push_back(pState);
	m_gameStates.back()->onEnter();
}

void GameStateMachine::changeState(GameState *pState)
{
	if (!m_gameStates.empty())
	{
		if (m_gameStates.back()->getStateID() == pState->getStateID())
		{
			return;
		}

		if (m_gameStates.back()->onExit())
		{
			delete m_gameStates.back(); // Here we recollect the resource we distributed before
			m_gameStates.pop_back();
		}
	}

	m_gameStates.push_back(pState);
	m_gameStates.back()->onEnter();
}

void GameStateMachine::popState(void)
{
	if (!m_gameStates.empty())
	{
		if (m_gameStates.back()->onExit())
		{
			delete m_gameStates.back(); // Here we recollect the resource we distributed before
			m_gameStates.pop_back();
		}
	}
}

void GameStateMachine::update(void)
{
	if (!m_gameStates.empty())
	{
		m_gameStates.back()->update();
	}
}

void GameStateMachine::render(void)
{
	if (!m_gameStates.empty())
	{
		m_gameStates.back()->render();
	}
}