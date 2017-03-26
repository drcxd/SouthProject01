#ifndef __InputHandler__
#define __InputHandler__

#include <vector>
#include <utility>

#include <SDL.h>

enum mouse_buttons
{
	LEFT = 0,
	MIDDLE = 1,
	RIGHT = 2
};

class InputHandler
{
public:

	static InputHandler* Instance()
	{
		if (s_pInstance == NULL)
		{
			s_pInstance = new InputHandler();
		}

		return s_pInstance;
	}

	void update(void);
	void clean(void);
	void reset();

	bool isKeyDown(SDL_Scancode key);

	bool isEnterPressed(void) const { return m_bEnterPressed; }
	void setEnterFree(void) { m_bEnterPressed = false; }
	bool isUpPressed(void) const { return m_bUpPressed; }
	void setUpFree(void) { m_bUpPressed = false; }
	bool isDownPressed(void) const { return m_bDownPressed; }
	void setDownFree(void) { m_bDownPressed = false; }

	bool getMouseButtonState(int buttonNumber) { return m_mouseButtonStates[buttonNumber]; }
	std::pair<int, int> getMousePosition(void) { return m_mousePosition; }

	void onKeyDown(void);
	void onKeyUp(SDL_Event e);
	const Uint8* getKeyboardState(void) { return m_keystates; }

private:

	InputHandler(void);
	~InputHandler(void) {}

	bool m_bEnterPressed;
	bool m_bUpPressed;
	bool m_bDownPressed;

	static InputHandler *s_pInstance;

	const Uint8* m_keystates;

	std::vector<bool> m_mouseButtonStates;
	std::pair<int, int> m_mousePosition;
};

typedef InputHandler TheInputHandler;
#endif // !__InputHandler__
