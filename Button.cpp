#include <utility>

#include "Button.h"
#include "InputHandler.h"

void Button::draw(void)
{
	ShooterObject::draw();
}

void Button::update(void)
{
	std::pair<int, int> mousePos = TheInputHandler::Instance()->getMousePosition();

	if (mousePos.first < m_position.getX() + m_width && mousePos.first > m_position.getX() &&
		mousePos.second < m_position.getY() + m_height && mousePos.second > m_position.getY())
	{
		if (TheInputHandler::Instance()->getMouseButtonState(LEFT) && m_bReleased)
		{
			if (m_callback != 0)
				m_callback();
			m_bReleased = false;
		}
		else if (!TheInputHandler::Instance()->getMouseButtonState(LEFT))
			m_bReleased = true;
	}
}

void Button::clean(void)
{
	ShooterObject::clean();
}

void Button::load(std::unique_ptr<LoaderParams> const &pParams)
{
	ShooterObject::load(pParams);
	m_callbackID = pParams->getCallbackID();
	m_currentFrame = MOUSE_OUT;
}