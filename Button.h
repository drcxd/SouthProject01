#ifndef __Button__
#define __Button__

#include "ShooterObject.h"
#include "GameObjectFactory.h"

class Button : public ShooterObject
{
public:

	Button() = default;
	virtual ~Button() {}

	virtual void draw(void);
	virtual void update(void);
	virtual void clean(void);
	virtual void load(std::unique_ptr<LoaderParams> const &pParams);

	void setCallback(void(*callback)()) { m_callback = callback; }
	int getCallbackID(void) { return m_callbackID; }

private:

	enum button_state
	{
		MOUSE_OUT = 0,
		MOUSE_ON = 1,
		CLICKED = 2
	};

	bool m_bReleased = true;
	int m_callbackID = 0;
	void(*m_callback)() = nullptr;
};


class ButtonCreator : public BaseCreator
{
	GameObject *createGameObject() const
	{
		return new Button();
	}
};


#endif