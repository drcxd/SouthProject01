#ifndef __PauseMenu__
#define __PauseMenu__

#include "MenuState.h"

class PauseMenu : public MenuState
{
public:

	virtual bool onEnter(void);
	virtual bool onExit(void);
	virtual void update(void);
	virtual std::string getStateID(void) const { return s_menuID; }

private:

	static const std::string s_menuID;
	bool m_bExit = false;

	static void s_resume(void);
	static void s_save(void);
	static void s_load(void);
	static void s_quit(void);
};

#endif // !__PauseMenu__
