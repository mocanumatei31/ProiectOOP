#ifndef PROIECTOOP_GAME_H
#define PROIECTOOP_GAME_H
#include "player.h"
#include <memory>
#include <vector>

class Game {
    std::shared_ptr<Player> player;
    std::vector<std::shared_ptr<Enemy>> enemy_list;
    int curr_level=0;
    bool beatDefaultEnemies=false;
public:
    Game();
    Game(const Game &other)=delete;
    Game& operator=(const Game& other)=delete;
    ~Game();
    static Game& get_game();
    void CharacterCreation();
    void CreateEnemy();
    void InitializeEnemyList();
    std::shared_ptr<Enemy> EnemySelect();
    void Battle();
    void Shop();
    void HubArea();
};

#endif //PROIECTOOP_GAME_H
