#ifndef __LevelParser__
#define __LevelParser__

#include "tinyxml.h"

#include "Level.h"


class LevelParser
{
public:

	Level *parseLevel(const char *levelFile);
	
	void parseTextures(TiXmlElement *pTextureRoot);
	void parseObjectLayer(TiXmlElement *pObjectElement, std::vector<Layer *> *pLayers, Level *pLevel);

private:
};

#endif