#include <iostream>
#include "services/GameServices.h"
using namespace std;

int main()
{
    GameServices *gameService = new GameServices(4);
    gameService->fillRandomCell();
    gameService->fillRandomCell();
    gameService->displayBoard();
    while (true)
    {
        cout << "Enter the move 0-left, 1-right, 2-top, 3-bottom" << endl;
        int move;
        cin >> move;
        gameService->makeMove(move);
        if (gameService->checkWin())
        {
            cout << "You won!" << endl;
            return 0;
        }
        if (!gameService->checkEmptyCell())
        {
            cout << "Game Over!" << endl;
            return 0;
        }
        gameService->fillRandomCell();
        gameService->displayBoard();
    }

    return 0;
}
