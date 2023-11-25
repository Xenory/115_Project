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
            case 'w': map->movePlayerUp();      // move up
                break;
            case 's': map->movePlayerDown();    // move down
                break;
            case 'a': map->movePlayerLeft();    // move left
                break;
            case 'd': map->movePlayerRight();   // move right
                break;
            default: cout << "Input Error!" << endl;
                break;
            case 'q':  Continue = false;        // quit
                break;
        }

    }
}