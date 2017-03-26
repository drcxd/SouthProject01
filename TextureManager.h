#ifndef __TextureManager__
#define __TextureManager__

#include <string>
#include <map>

#include <SDL.h>

class TextureManager
{
public:
	
	bool load(const std::string &fileName, const std::string &id, SDL_Renderer *pRenderer);
	void draw(const std::string &id, int x, int y, int width, int height, SDL_Renderer *pRenderer,
		SDL_RendererFlip flip = SDL_FLIP_NONE);
	void drawFrame(const std::string &id, int x, int y, int width, int height, int currentRow,
		int currentFrame, SDL_Renderer *pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

	static TextureManager* Instance()
	{
		if (s_pInstance == nullptr)
		{
			s_pInstance = new TextureManager();
			return s_pInstance;
		}

		return s_pInstance;
	}

private:

	TextureManager() {}

	static TextureManager* s_pInstance;

	std::map<std::string, SDL_Texture*> m_textureMap;
};

typedef TextureManager TheTextureManager;
#endif // !__TextureManager__
