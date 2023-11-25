#include "Player.h"

Player::Player()
{
	xPos = 0;
	yPos = 0; 
	playerNode = new nodeAL();
	beneathPlayerNode = new nodeAL();

}

Player::Player(int x, int y, nodeAL *pnode)
{
	xPos = x;
	yPos = y;
	playerNode = new nodeAL(pnode->vertex, pnode->weight, pnode->landType);
	beneathPlayerNode = new nodeAL(playerNode->vertex,10, ' ');
}

void Player::printPos()
{
	cout << xPos<< "," << yPos<< endl;
	cout << "Player Node: " << playerNode->landType << " " << playerNode->vertex << " " << playerNode->weight << endl;
	cout << "Beneath Player Node: " << beneathPlayerNode->landType << " " << beneathPlayerNode->vertex << " " << beneathPlayerNode->weight << endl;
}