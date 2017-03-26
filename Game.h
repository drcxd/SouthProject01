#ifndef __Game__
#define __Game__

#include <vector>

#include <SDL.h>

#include "TextureManager.h"
#include "GameObject.h"
#include "GameStateMachine.h"

class Game
{
public:

	 // Process control functions
     bool init(const char* title, int xpos, int ypos,
	       int width, int height, int flags);
	 void render(void);
     void update(void);
     void handleEvents(void);
	 void clean(void);

	 // Getters
	 SDL_Renderer *getRenderer() const { return m_pRenderer; }
	 SDL_Window *getWindow() const { return m_pWindow; }
	 GameStateMachine *getStateMachine(void) { return m_pGameStateMachine; }

	 void setPlayerLives(int lives) { m_playerLives = lives; }
	 int getPlayerLives() { return m_playerLives; }

	 void setCurrentLevel(int currentLevel);
	 int getCurrentLevel() const { return m_currentLevel; }

	 void setNextLevel(int nextLevel) { m_nextLevel = nextLevel; }
	 int getNextLevel() const { return m_nextLevel; }

	 void setLevelComplete(bool levelComplete) { m_bLevelComplete = levelComplete; }
	 bool getLevelComplete() const { return m_bLevelComplete; }

	 bool running() { return m_bRunning; }

	 int getGameWidth() const { return m_gameWidth; }
	 int getGameHeight() const { return m_gameHeight; }
	 float getScrollSpeed() { return m_scrollSpeed; }

	 bool changingState() { return m_bChangingState; }
	 void changingState(bool cs) { m_bChangingState = cs; }

	 const std::vector<std::string> &getLevelFiles() const { return m_levelFiles; }

	 // Skeleton
	 static Game *Instance()
	 {
		 if (s_pInstance == nullptr)
		 {
			 s_pInstance = new Game();
		 }

		 return s_pInstance;
	 }

private:
	
	bool m_bChangingState;

    SDL_Window *m_pWindow;
    SDL_Renderer *m_pRenderer;
	GameStateMachine *m_pGameStateMachine;

    bool m_bRunning;

	int m_gameWidth;
	int m_gameHeight;
	float m_scrollSpeed;

	int m_playerLives;

	int m_currentLevel;
	int m_nextLevel;
	bool m_bLevelComplete;

	std::vector<std::string> m_levelFiles;

	 static Game* s_pInstance;
	 Game();
	 ~Game();
};

typedef Game TheGame;

#endif __Game__
