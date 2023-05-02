#ifndef PROIECTOOP_GAME_H
#define PROIECTOOP_GAME_H
#include "player.h"
#include <memory>

class Game {
    std::shared_ptr<Player> player;
public:
    Game();
    //Game(const Game &other);
    ~Game();
    Game &operator=(const Game &other);
    void CharacterCreation();
    void Battle();
    void Shop();
    void HubArea();
};

#endif //PROIECTOOP_GAME_H
