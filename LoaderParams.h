/* This is the class wrapping the object loading arguments. */

#ifndef __LoaderParams__
#define __LoaderParams__

#include <string>

class LoaderParams
{
public:

	LoaderParams() = default;
	LoaderParams(int x, int y, int width, int height, std::string textureID,
		int numFrames, int callbackID = 0, int animSpeed = 0) :
		m_x(x), m_y(y), m_width(width), m_height(height), m_textureID(textureID),
		m_numFrames(numFrames), m_callbackID(callbackID), m_animSpeed(animSpeed)
	{}

	int getX() const { return m_x; }
	int getY() const { return m_y; }
	int getWidth() const { return m_width; }
	int getHeight() const { return m_height; }
	std::string getTextureID() const { return m_textureID; }
	int getNumFrames() const { return m_numFrames; }
	int getCallbackID() const { return m_callbackID; }
	int getAnimSpeed() const { return m_animSpeed; }

private:

	int m_x = 0;
	int m_y = 0;
	int m_width = 0;
	int m_height = 0;
	int m_numFrames = 0;
	int m_callbackID = 0;
	int m_animSpeed = 0;
	std::string m_textureID;
};
#endif // !__LoaderParams__

