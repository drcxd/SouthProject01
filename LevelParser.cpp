#include "LevelParser.h"
#include "TextureManager.h"
#include "Game.h"
#include "ObjectLayer.h"
#include "GameObjectFactory.h"

Level *LevelParser::parseLevel(const char *levelFile)
{
	TiXmlDocument levelDoc;
	if (!levelDoc.LoadFile(levelFile))
	{
		std::cerr << levelDoc.ErrorDesc() << std::endl;
		return new Level();
	}

	Level *pLevel = new Level();

	TiXmlElement *pRoot = levelDoc.RootElement();

	for (auto e = pRoot->FirstChildElement()->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
			parseTextures(e);

	for (auto e = pRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
		if (e->Value() == std::string("objectgroup"))
			parseObjectLayer(e, pLevel->getLayers(), pLevel);

	return pLevel;
}

void LevelParser::parseTextures(TiXmlElement *pTextureRoot)
{
	//std::cerr << pTextureRoot->Attribute("value") << " " << pTextureRoot->Attribute("name") << std::endl;
	TheTextureManager::Instance()->load(pTextureRoot->Attribute("value"), pTextureRoot->Attribute("name"),
		TheGame::Instance()->getRenderer());
}

void LevelParser::parseObjectLayer(TiXmlElement *pObjectElement, std::vector<Layer *> *pLayers, Level *pLevel)
{
	ObjectLayer *pObjectLayer = new ObjectLayer();

	// now e points to <object
	for (auto e = pObjectElement->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("object"))
		{
			int x, y, width, height, numFrames, callbackID = 0, animSpeed = 0;
			std::string textureID;
			std::string type;

			e->Attribute("x", &x);
			e->Attribute("y", &y);
			y -= 1800; // hardcode to make the objects displayed in the right place
			type = e->Attribute("type");
			GameObject *pGameObject = TheGameObjectFactory::Instance()->create(type);

			// now properties points to <properties
			auto properties = e->FirstChildElement();
			for (auto property = properties->FirstChildElement(); property != nullptr;
				property = property->NextSiblingElement())
			{
				std::cerr << property->Attribute("name") << std::endl;
				if (property->Attribute("name") == std::string("numFrames"))
					property->Attribute("value", &numFrames);
				else if (property->Attribute("name") == std::string("textureHeight"))
					property->Attribute("value", &height);
				else if (property->Attribute("name") == std::string("textureWidth"))
					property->Attribute("value", &width);
				else if (property->Attribute("name") == std::string("textureID"))
					textureID = property->Attribute("value");
				else if (property->Attribute("name") == std::string("callbackID"))
					property->Attribute("value", &callbackID);
				else if (property->Attribute("name") == std::string("animSpeed"))
					property->Attribute("value", &animSpeed);
			}

			pGameObject->load(std::unique_ptr<LoaderParams>(new LoaderParams(x, y, width, height, textureID, numFrames, callbackID,
				animSpeed)));

			if (type == "Player")
				pLevel->setPlayer(dynamic_cast<Player *>(pGameObject));
				

			pObjectLayer->getGameObjects()->push_back(pGameObject);
		}
	}
	pLayers->push_back(pObjectLayer);
}