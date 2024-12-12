#include <iostream>
#include "Game.h"

int main()
{
    Game game;
    std::srand(static_cast<unsigned>(time(NULL)));
    while (game.running() && game.getEndGame()!= true) 
    {
        game.update();
        game.render();
    }

    // End of the application
    return 0;
}
