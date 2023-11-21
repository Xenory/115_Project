#pragma once
#include "Map.h"
#include "Player.h"

// TERRAIN TYPES
const char WALL = '#';
const char PLAIN = ' ';
const char GRASS = '-';
const char ENEMY = 'X';
const char PLAYER = 'O';
const char HIDDEN = 'H';

class Game
{

private:
	Player* player;
	Map* map;
	int n;		//map size

public:

	Game(const string& mapFile);
	void run();
};

