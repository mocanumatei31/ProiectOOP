#ifndef PROIECTOOP_GAME_H
#define PROIECTOOP_GAME_H
#include "player.h"

class Game {
    Player player;
public:
    Game();
    //Game(const Game &other);
    ~Game();
    Game &operator=(const Game &other);
    friend std::ostream& operator <<(std::ostream& out, const Game& game);
    void CharacterCreation();
    void Battle();
    void Shop();
    void HubArea();
};

#endif //PROIECTOOP_GAME_H
