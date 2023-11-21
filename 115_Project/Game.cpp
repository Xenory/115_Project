#include "Game.h"
#include <tuple>

Game::Game(const string& mapFile) 
{
    string filename = "Map.txt";

    tuple<int, int> result = countRowsAndColumns(filename);

    int numRows = get<0>(result);
    int numCol = get<1>(result);

    n = numRows * numCol;

    map = new Map;

    ifstream file(mapFile);
    string contents((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
  
    if (!file) 
    {
        cerr << "Error: Unable to open map file." << endl;
        exit(1);
    }
    for (int i = 0; i < n; i++) 
    {
        map->getNode(i)->landType = contents.c_str()[i];
    }

    // INITIALIZE PLAYER AT LOCATION IN MATRIX player = new Player(x,y);
}

void Game::run()
{
    char userInput;
    bool Continue = true;
    while (Continue)
    {
        map->printMatrix();

        cout << "-----ACTION MENU-----\n" << "Quit (q)\n" << "Move Up (w)\n" << "Move Down (s)\n" << "Move Left (a)\n" << "Move Right (d)\n" << "Skip Turn (space)\n" << "Input: ";
        cin >> userInput;

        if (userInput == 'q')       // Quit
        {
            Continue = false;
        }
        else if (userInput == 'w')  // Up
        {

        }
        else if (userInput == 's')  // Down
        {

        }
        else if (userInput == 'a')  // Left
        {

        }
        else if (userInput == 'd')  // Right
        {

        }
        else if (userInput == ' ') // Skip
        {

        }
        else
        {
            cout << "Invalid Input" << endl;
        }
    }
}