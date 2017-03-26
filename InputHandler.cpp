#include "InputHandler.h"
#include "Game.h"

InputHandler* InputHandler::s_pInstance = NULL;

InputHandler::InputHandler(void) : m_bEnterPressed(false), m_bUpPressed(false), m_bDownPressed(false)
{
	m_keystates = nullptr;
	for (int i = 0; i < 3; i++)
		m_mouseButtonStates.push_back(false);
}

void InputHandler::update(void)
{
	SDL_Event event; // Variable to hold every event 
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			TheGame::Instance()->clean();
			break;
		case SDL_KEYDOWN:
			onKeyDown();
			break;
		case SDL_KEYUP:
			onKeyUp(event);
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT)
				m_mouseButtonStates[LEFT] = true;
			if (event.button.button == SDL_BUTTON_MIDDLE)
				m_mouseButtonStates[MIDDLE] = true;
			if (event.button.button == SDL_BUTTON_RIGHT)
				m_mouseButtonStates[RIGHT] = true;
			break;
		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_LEFT)
				m_mouseButtonStates[LEFT] = false;
			if (event.button.button == SDL_BUTTON_MIDDLE)
				m_mouseButtonStates[MIDDLE] = false;
			if (event.button.button == SDL_BUTTON_RIGHT)
				m_mouseButtonStates[RIGHT] = false;
			break;
		case SDL_MOUSEMOTION:
			m_mousePosition.first = event.motion.x;
			m_mousePosition.second = event.motion.y;
		default:
			break;
		}
	}
}

void InputHandler::clean(void)
{}

bool InputHandler::isKeyDown(SDL_Scancode key)
{
	if (m_keystates != nullptr)
		if (m_keystates[key] == 1)
			return true;

	return false;
}

void InputHandler::onKeyDown(void)
{
	m_keystates = SDL_GetKeyboardState(0);
}

void InputHandler::onKeyUp(SDL_Event event)
{
	switch (event.key.keysym.scancode)
	{
	case SDL_SCANCODE_RETURN: m_bEnterPressed = true; break;
	case SDL_SCANCODE_UP: m_bUpPressed = true; break;
	case SDL_SCANCODE_DOWN: m_bDownPressed = true; break;
	}
}

void InputHandler::reset()
{
	m_mouseButtonStates[LEFT] = false;
	m_mouseButtonStates[RIGHT] = false;
	m_mouseButtonStates[MIDDLE] = false;
}