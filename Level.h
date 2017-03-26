#ifndef __Level__
#define __Level__

#include <vector>

#include "Layer.h"
#include "Player.h"

class Level
{
	friend class LevelParser;

public:

	// Level() = default;
	~Level();

	void update();
	void render();

	std::vector<Layer *> *getLayers() { return &m_layers; }
	Player *getPlayer() { return m_pPlayer; }
	void setPlayer(Player *pPlayer) { m_pPlayer = pPlayer; }

protected:

	std::vector<Layer*> m_layers;

private:

	Level() = default;
	Player *m_pPlayer;
};

#endif // !__Level__
