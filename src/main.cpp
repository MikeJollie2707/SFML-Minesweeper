#include <iostream>

#include "game.hpp"

int main()
{   
    Game game(9, 9, 10, 40, 5);
    game.event();
    return 0;
}