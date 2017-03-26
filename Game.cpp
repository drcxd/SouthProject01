#include <iostream>

#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "tinyxml.h"

#include "Game.h"
#include "InputHandler.h"
#include "MainMenuState.h"
#include "GameObjectFactory.h"
#include "Button.h"
#include "Player.h"
#include "Boss1.h"
#include "Fairy.h"

Game *Game::s_pInstance = nullptr; // Skeleton pointer to asure there is only one instance

Game::Game() :
	m_pWindow(nullptr),
	m_pRenderer(nullptr),
	m_bRunning(false),
	m_pGameStateMachine(0),
	m_playerLives(3),
	m_scrollSpeed(0.8f),
	m_bLevelComplete(false),
	m_bChangingState(false)
{
	// hardcode here and initializer list
	m_levelFiles.push_back("data/map1.tmx");

	m_currentLevel = 1;
}

Game::~Game()
{
	m_pRenderer = nullptr;
	m_pWindow = nullptr;
}
 
bool Game::init(const char *title, int xpos, int ypos,
		int width, int height, int flags)
{
    
	m_gameWidth = width;
	m_gameHeight = height;

	// Initialize SDL create window, renderer and set render color
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
	  std::cerr << "Failed when initializing SDL. Error: " 
		  << SDL_GetError() << std::endl;
	  return false;
    }
    else
    {
		m_pWindow = SDL_CreateWindow(title, xpos, ypos, width,
					       height, flags);
		if (m_pWindow == nullptr)
		{
			   std::cerr << "Failed when creating window. Error: "
				 << SDL_GetError() << std::endl;
			return false;
		}
		else
		{
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);

			if (m_pRenderer == nullptr)
			{
				std::cout << "Failed when creating renderer. Error: "
					<< SDL_GetError() << std::endl;
				return false;
			}
			else
			{
				SDL_SetRenderDrawColor(m_pRenderer, 255, 255,
						255, 255);
			}
		}
    }

	 // Init extended parts: img and ttf TODO: we will also initialize audio
	 // subsystem here too
	 if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0)
	 {
		 std::cerr << "Failed when initializing SDL_image.\n";
		 return false;
	 }

	 if (TTF_Init() != 0)
	 {
		 std::cerr << "Failed when initializing SDL_ttf.\n";
		 return false;
	 }

	 if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	 {
		 std::cerr << "Failed when initializing SDL_mixer.\n SDL_mixer Error: " << Mix_GetError() << std::endl;
		 return false;
	 }

	 // Add sound effects here and move them other better place in the future

	 // Register types for the game
	 TheGameObjectFactory::Instance()->registerType("Button", new ButtonCreator());
	 TheGameObjectFactory::Instance()->registerType("Player", new PlayerCreator());
	 TheGameObjectFactory::Instance()->registerType("Boss1", new Boss1Creator());
	 TheGameObjectFactory::Instance()->registerType("Fairy", new FairyCreator());

	 // Create game state machine and push a menu state.
	 m_pGameStateMachine = new GameStateMachine();
	 m_pGameStateMachine->changeState(new MainMenuState());

	 // Set running bool true
     m_bRunning = true;

     return true;
}

void Game::render(void)
{
	SDL_RenderClear(m_pRenderer);

	// We call game statae machine render function actually do everything
	m_pGameStateMachine->render();

	SDL_RenderPresent(m_pRenderer);
}

void Game::update(void)
{
	// Acturally we call game state machine update function to do every thing
	m_pGameStateMachine->update();
}

void Game::handleEvents(void)
{
	TheInputHandler::Instance()->update();
}

// Destroy window and renderer
void Game::clean(void)
{
	std::cerr << "Cleanning game\n";

	// Destroy window
	SDL_DestroyWindow(m_pWindow);
	m_pWindow = nullptr;

	// Destroy renderer
	SDL_DestroyRenderer(m_pRenderer);
	m_pRenderer = nullptr;

	IMG_Quit();
	Mix_Quit();
	TTF_Quit();
	SDL_Quit();
	m_bRunning = false;
}

void Game::setCurrentLevel(int currentLevel)
{
	m_currentLevel = currentLevel;
	// code that load new level
	TheGame::Instance()->getStateMachine()->changeState(new MainMenuState());
	m_bLevelComplete = false;
}