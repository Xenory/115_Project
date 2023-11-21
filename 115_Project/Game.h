#pragma once
#include "Map.h"

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
	Map* map;
	int n;		//map size

public:

	Game(const string& mapFile);
	void run();
};

