#ifndef __MainMenuState__
#define __MainMenuState__

#include "MenuState.h"

class MainMenuState : public MenuState
{
public:

	virtual ~MainMenuState() {}
	
	virtual bool onEnter();
	virtual bool onExit();
	virtual void update();
	virtual void render();
	virtual std::string getStateID(void) const { return s_menuID; }

private:

	static const std::string s_menuID;

	static void s_menuToPlay(void);
	static void s_exit(void);

};

#endif