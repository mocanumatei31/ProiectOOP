#include <iostream>
#include "game.h"

int main()
{
    auto& game=Game::get_game();
    game.CharacterCreation();
    game.InitializeEnemyList();
    game.HubArea();
    return 0;
}
