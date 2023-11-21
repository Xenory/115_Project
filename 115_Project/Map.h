#pragma once
#include "GraphAL.h"
#include "Player.h"
class Map
{
private:
	Player* player;
	int mapSize;
	GraphAL* myMap;

public:

	Map();
	//Map(int n);
	
	nodeAL* getNode(int vertex);
	void displayMap();

	//creating matrix
	int numRows;
	int numCol;
	char** mapMatrix;

	void printMatrix();

	//creating Graph
	void updateGraph();
	
};

tuple<int, int> countRowsAndColumns(const string& filename);
double getSymbolWeight(char symbol);
