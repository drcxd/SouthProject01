/* The base class of every actul game object presents in window. */

#include "GameObject.h"
#include "LoaderParams.h"
#include "Vector2D.h"

#ifndef __SDLGameObject__
#define __SDLGameObject__

class SDLGameObject : public GameObject
{
public:

	SDLGameObject() = default;

	virtual void draw(void);
	virtual void update(void);
	virtual void clean(void); 
	virtual void load(const LoaderParams *pParams);

protected:

	Vector2D m_position;
	Vector2D m_velocity;
	Vector2D m_acceleration;

	int m_height = 0;
	int m_width = 0;

	int m_currentFrame = 0;
	int m_currentRow = 1;
	int m_numFrames = 1;

	std::string m_textureID;
};
#endif // !__SDLGameObject__

