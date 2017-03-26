#ifndef __GameObjectFactory__
#define __GameObjectFactory__

#include <string>
#include <map>
#include <iostream>

#include "GameObject.h"

class BaseCreator
{
public:

	virtual GameObject *createGameObject() const = 0;
	virtual ~BaseCreator() {}
};

class GameObjectFactory
{
public:

	static GameObjectFactory *Instance()
	{
		if (s_pInstance == nullptr)
			s_pInstance = new GameObjectFactory();
		return s_pInstance;
	}

	bool registerType(std::string typeID, BaseCreator *pCreator)
	{
		std::map<std::string, BaseCreator *>::iterator it = m_creators.find(typeID);

		if (it != m_creators.end())
		{
			delete pCreator;
			return false;
		}

		m_creators[typeID] = pCreator;

		return true;
	}

	GameObject *create(std::string typeID)
	{
		auto it = m_creators.find(typeID);

		if (it == m_creators.end())
		{
			std::cerr << "Can't find type: " << typeID << std::endl;
			return nullptr;
		}

		BaseCreator *pCreator = (*it).second;
		return pCreator->createGameObject();
	}

private:

	static GameObjectFactory *s_pInstance;
	std::map<std::string, BaseCreator *> m_creators;
};

typedef GameObjectFactory TheGameObjectFactory;

#endif // !__GameObjectFactory__