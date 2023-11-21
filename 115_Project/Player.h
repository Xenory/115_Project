#pragma once
#include<iostream>
using namespace std;

class Player
{
private:
	int xPos;
	int yPos;

public:
	Player();
	Player(int x, int y);

	void printPos();
};

