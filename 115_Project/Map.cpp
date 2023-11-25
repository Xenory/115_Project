#include "Map.h"
#include<tuple>
#include<vector>


const double WALL_WEIGHT = 100;         // #
const double PLAIN_WEIGHT = 10;         // ' '
const double GRASS_WEIGHT = 15;         // -
const double ENEMY_WEIGHT = 100;        //X
const double PLAYER_WEIGHT = 0;         //O
const double HIDDEN_WEIGHT = 100;       //enemies can not go through hidden 

Map::Map() 
{
    string filename = "Map.txt";

    ifstream file(filename);  // Open the file for reading

    if (!file.is_open()) {
        cerr << "Error: Unable to open the file." << endl;
        return;
    }

    vector<string> lines;
    string line;
    int maxColumns = 0;

    // Read the file line by line and store the lines in a vector
    while (getline(file, line)) {
        lines.push_back(line);
        maxColumns = max(maxColumns, static_cast<int>(line.length()));
        
    }

    numRows = static_cast<int>(lines.size());
    numCol = maxColumns;

    // Allocate memory for mapMatrix
    mapMatrix = new char* [numRows];
    for (int i = 0; i < numRows; i++) {
        mapMatrix[i] = new char[numCol];
    }

    // Fill the mapMatrix with the characters from the lines
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCol; j++) {
            if (j < lines[i].length()) {
                mapMatrix[i][j] = lines[i][j];
            }
            else {
                mapMatrix[i][j] = '#';  // Fill with space if line is shorter
            }
        }
    }
    

    //populate graph based on the mapMatrix 

    myMap = new GraphAL(numRows * numCol);          //create a graph to populate

    for (int i = 0; i < numRows; i++) 
    {
        for (int j = 0; j < numCol; j++) 
        {
            char currentChar = mapMatrix[i][j];
            int currentNode = i * numCol + j;

            double weight = getSymbolWeight(currentChar);
            myMap->setNodeWeight(currentNode, weight);
            myMap->setLandType(currentNode, currentChar);

            // Add edges for up, down, left, right for non-wall characters
            
                // up
                if (i > 0) {
                    int adjacentNode = (i - 1) * numCol + j;
                    char adjacentChar = mapMatrix[i - 1][j];
                    double adjWeight = getSymbolWeight(adjacentChar);
                    myMap->setDirectedEdge(currentNode, adjacentNode, adjWeight, adjacentChar);
                    myMap->setDirectedEdge(adjacentNode, currentNode, weight, currentChar);
                }

                // down
                if (i < numRows - 1) {
                    int adjacentNode = (i + 1) * numCol + j;
                    char adjacentChar = mapMatrix[i + 1][j];
                    double adjWeight = getSymbolWeight(adjacentChar);
                    myMap->setDirectedEdge(currentNode, adjacentNode, adjWeight, adjacentChar);
                    myMap->setDirectedEdge(adjacentNode, currentNode, weight, currentChar);
                }

                // left
                if (j > 0) {
                    int adjacentNode = i * numCol + (j - 1);
                    char adjacentChar = mapMatrix[i][j - 1];
                    double adjWeight = getSymbolWeight(adjacentChar);
                    myMap->setDirectedEdge(currentNode, adjacentNode, adjWeight, adjacentChar);
                    myMap->setDirectedEdge(adjacentNode, currentNode, weight, currentChar);
                }

                // right
                if (j < numCol - 1) {
                    int adjacentNode = i * numCol + (j + 1);
                    char adjacentChar = mapMatrix[i][j + 1];
                    double adjWeight = getSymbolWeight(adjacentChar);
                    myMap->setDirectedEdge(currentNode, adjacentNode, adjWeight, adjacentChar);
                    myMap->setDirectedEdge(adjacentNode, currentNode, weight, currentChar);
                }
            
                // Initialize Player at Location
                if (currentChar == 'O')
                {
                    player = new Player(i, j, myMap->retrieveEdge(currentNode, currentNode));
                    player->printPos();
                }

        }
    }

    //cout << endl;

    //displayMap();       //prints node weight and landtype

    //cout << "\n\n";
    //myMap->Display();   //prints adjacency list of graph
    

    file.close();  // Close the file when done

}


void Map::printMatrix() {
    cout << "Debug: numRows = " << numRows << ", numCol = " << numCol << endl;  // Debug output
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCol; j++) {
            cout << mapMatrix[i][j];
        }
        cout << endl;
    }
    cout << "Debug: End of printMatrix function" << endl;  // Debug output

}

//Map::Map(int n)
//{
//	mapSize = n;
//	myMap = new GraphAL(n);
//	
//}

void Map::displayMap()
{
    cout << "displayMap" << endl;
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCol; j++) {
            int currentNode = i * numCol + j;
            char landtype = myMap->getNodeLandtype(currentNode);
         
            double weight = myMap->getNodeWeight(currentNode);
            cout << "Node " << currentNode << " Weight: " << weight << " Landtype: " << landtype <<endl;
        }
        cout << endl;
    }
}

nodeAL* Map::getNode(int vertex)
{
	return myMap->retrieveEdge(vertex, vertex);
}

//-----------------------------------------------------------------
tuple<int, int> countRowsAndColumns(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error: Unable to open the file." << endl;
        return make_tuple(0, 0);
    }

    vector<string> lines;
    string line;
    int maxColumns = 0;

    while (getline(file, line)) {
        lines.push_back(line);
        maxColumns = max(maxColumns, static_cast<int>(line.length()));
    }

    int numRows = static_cast<int>(lines.size());
    return make_tuple(numRows, maxColumns);
}

double getSymbolWeight(char symbol) 
{
    switch (symbol) 
    {
        case '#': return WALL_WEIGHT;
        case 'H': return HIDDEN_WEIGHT;
        case'-': return GRASS_WEIGHT;
        case'X' : return ENEMY_WEIGHT;
        case'O': return PLAYER_WEIGHT;
        case' ': return PLAIN_WEIGHT;
        default: return 1.0;

    }
}

void Map::movePlayerUp()
{
    int current = player->playerNode->vertex;
    int target = player->playerNode->vertex - numCol;

    if (myMap->retrieveEdge(target,target)->landType != '#' )
    {
        // update matrix
        mapMatrix[player->xPos][player->yPos] = player->beneathPlayerNode->landType;
        player->xPos--;
        mapMatrix[player->xPos][player->yPos] = player->playerNode->landType;

        // update graph
        myMap->retrieveEdge(current, current)->landType = player->beneathPlayerNode->landType;
        myMap->retrieveEdge(current, current)->weight = player->beneathPlayerNode->weight;

        player->beneathPlayerNode->landType = myMap->retrieveEdge(target, target)->landType;
        player->beneathPlayerNode->weight = myMap->retrieveEdge(target, target)->weight;
        player->beneathPlayerNode->vertex = myMap->retrieveEdge(target, target)->vertex;

        myMap->retrieveEdge(target, target)->landType = player->playerNode->landType;
        myMap->retrieveEdge(target, target)->weight = player->playerNode->weight;

        // update player class
        player->playerNode->vertex = target;

        displayMap();
        player->printPos();
    }
    else
    {
        cout << "Thats a wall dude" << endl;
    }
}

void Map::movePlayerDown()
{
    int current = player->playerNode->vertex;
    int target = player->playerNode->vertex + numCol;

    if (myMap->retrieveEdge(target, target)->landType != '#')
    {
        // update matrix
        mapMatrix[player->xPos][player->yPos] = player->beneathPlayerNode->landType;
        player->xPos++;
        mapMatrix[player->xPos][player->yPos] = player->playerNode->landType;

        // update graph
        myMap->retrieveEdge(current, current)->landType = player->beneathPlayerNode->landType;
        myMap->retrieveEdge(current, current)->weight = player->beneathPlayerNode->weight;

        player->beneathPlayerNode->landType = myMap->retrieveEdge(target, target)->landType;
        player->beneathPlayerNode->weight = myMap->retrieveEdge(target, target)->weight;
        player->beneathPlayerNode->vertex = myMap->retrieveEdge(target, target)->vertex;

        myMap->retrieveEdge(target, target)->landType = player->playerNode->landType;        
        myMap->retrieveEdge(target, target)->weight = player->playerNode->weight;

        // update player class
        player->playerNode->vertex = target;

        displayMap();
        player->printPos();
    }
    else
    {
        cout << "Thats a wall dude" << endl;
    }
}

void Map::movePlayerLeft()
{
    int current = player->playerNode->vertex;
    int target = player->playerNode->vertex-1;

    if (myMap->retrieveEdge(target, target)->landType != '#')
    {
        // update matrix
        mapMatrix[player->xPos][player->yPos] = player->beneathPlayerNode->landType;
        player->yPos--;
        mapMatrix[player->xPos][player->yPos] = player->playerNode->landType;

        // update graph
        myMap->retrieveEdge(current, current)->landType = player->beneathPlayerNode->landType;
        myMap->retrieveEdge(current, current)->weight = player->beneathPlayerNode->weight;

        player->beneathPlayerNode->landType = myMap->retrieveEdge(target, target)->landType;
        player->beneathPlayerNode->weight = myMap->retrieveEdge(target, target)->weight;
        player->beneathPlayerNode->vertex = myMap->retrieveEdge(target, target)->vertex;

        myMap->retrieveEdge(target, target)->landType = player->playerNode->landType;
        myMap->retrieveEdge(target, target)->weight = player->playerNode->weight;

        // update player class
        player->playerNode->vertex = target;

        displayMap();
        player->printPos();
    }
    else
    {
        cout << "Thats a wall dude" << endl;
    }
}

void Map::movePlayerRight()
{
    int current = player->playerNode->vertex;
    int target = player->playerNode->vertex + 1;

    if (myMap->retrieveEdge(target, target)->landType != '#')
    {
        // update matrix
        mapMatrix[player->xPos][player->yPos] = player->beneathPlayerNode->landType;
        player->yPos++;
        mapMatrix[player->xPos][player->yPos] = player->playerNode->landType;

        // update graph
        myMap->retrieveEdge(current, current)->landType = player->beneathPlayerNode->landType;
        myMap->retrieveEdge(current, current)->weight = player->beneathPlayerNode->weight;

        player->beneathPlayerNode->landType = myMap->retrieveEdge(target, target)->landType;
        player->beneathPlayerNode->weight = myMap->retrieveEdge(target, target)->weight;
        player->beneathPlayerNode->vertex = myMap->retrieveEdge(target, target)->vertex;

        myMap->retrieveEdge(target, target)->landType = player->playerNode->landType;
        myMap->retrieveEdge(target, target)->weight = player->playerNode->weight;

        // update player class
        player->playerNode->vertex = target;

        displayMap();
        player->printPos();
    }
    else
    {
        cout << "Thats a wall dude" << endl;
    }
}