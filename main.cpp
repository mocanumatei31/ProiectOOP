#include <iostream>
#include "game.h"

int main()
{
    auto& game=Game::get_game();
    game.ChooseCharacter();
    game.HubArea();
    return 0;
}
