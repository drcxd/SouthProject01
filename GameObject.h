/* The virtual class which only provide a pattern. */

#ifndef __GameObject__
#define __GameObject__

#include <string>
#include <memory>

#include <SDL.h>

#include "LoaderParams.h"
#include "Vector2D.h"

class GameObject
{
public:

	virtual ~GameObject() {}

	virtual void load(std::unique_ptr<LoaderParams> const &pParms) = 0;
	virtual void draw() = 0;
	virtual void update() = 0;
	virtual void clean() = 0;
	virtual void collision() = 0;
	virtual std::string type() = 0;
	Vector2D &getPosition() { return m_position; }
	int getWidth() { return m_width; }
	int getHeight() { return m_height; }
	void scroll(float scrollSpeed) { m_position.setY(m_position.getY() + scrollSpeed); }
	bool updating() { return m_bUpdating; }
	bool dead() { return m_bDead; }
	bool dying() { return m_bDying; }
	void setUpdating(bool updating) { m_bUpdating = updating; }


protected:

	GameObject() : m_position(0, 0),
		m_velocity(0, 0),
		m_acceleration(0, 0),
		m_width(0),
		m_height(0),
		m_currentRow(0),
		m_currentFrame(0),
		m_numFrames(1),
		m_bUpdating(false),
		m_bDead(false),
		m_bDying(false),
		m_angle(0),
		m_alpha(255)
	{}

	Vector2D m_position;
	Vector2D m_velocity;
	Vector2D m_acceleration;
	int m_width = 0;
	int m_height = 0;
	int m_currentRow = 0;
	int m_currentFrame = 0;
	int m_numFrames = 1;
	std::string m_textureID;
	bool m_bUpdating = false;
	bool m_bDead = false;
	bool m_bDying = false;
	double m_angle = 0;
	int m_alpha = 255;
};
#endif // !__GameObject__
