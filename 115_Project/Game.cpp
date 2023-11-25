#include "Game.h"
#include <tuple>

Game::Game()
{
    map = new Map();
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

        switch (userInput) 
        {
            case 'w': 
                map->movePlayerUp();      // move up
                map->moveEnemies();
                break;
            case 's': 
                map->movePlayerDown();    // move down
                map->moveEnemies();
                break;
            case 'a': 
                map->movePlayerLeft();    // move left
                map->moveEnemies();
                break;
            case 'd': 
                map->movePlayerRight();   // move right
                map->moveEnemies();
                break;
            default: cout << "Input Error!" << endl;
                break;
            case 'q':  Continue = false;        // quit
                break;
        }
        //system("CLS");
    }
}