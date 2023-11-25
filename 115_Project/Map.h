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
	
	void movePlayerUp();
	void movePlayerDown();
	void movePlayerLeft();
	void movePlayerRight();

};

tuple<int, int> countRowsAndColumns(const string& filename);
double getSymbolWeight(char symbol);
