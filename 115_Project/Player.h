#pragma once
#include<iostream>
#include "GraphAL.h"
using namespace std;

class Player
{
private:
	int xPos;
	int yPos;
	nodeAL *playerNode;
	nodeAL *beneathPlayerNode;
public:
	Player();
	Player(int x, int y, nodeAL* pnode );

	void printPos();


	nodeAL* getPlayerNode() { return playerNode; }
	void setBeneathPlayerNode(nodeAL* current) { beneathPlayerNode = current; }
	nodeAL* getBeneathPlayerNode() { return beneathPlayerNode; }
};

