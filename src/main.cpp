#include <iostream>

#include "game.hpp"

int main()
{   
    Game game(10, 10, 10, 40, 5);
    game.event();
    return 0;
}