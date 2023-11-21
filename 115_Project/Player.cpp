#include "Player.h"

Player::Player()
{
	xPos = 0;
	yPos = 0; 
}

Player::Player(int x, int y)
{
	xPos = x;
	yPos = y;
}

void Player::printPos()
{
	cout << xPos << "," << yPos << endl;
}