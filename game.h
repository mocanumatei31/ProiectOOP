#ifndef PROIECTOOP_GAME_H
#define PROIECTOOP_GAME_H
#include "player.h"
#include "enemy.h"
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
    void ChooseCharacter();
    void LoadFile(const std::string& filename);
    void LoadCharacter(int gameBegin);
    bool isFileEmpty(const std::string& filename);
    std::string FileOutput(const std::string& filename);
    void WriteFile(const std::string& filename);
    void SaveCharacter();
    void CharacterCreation();
    void CreateEnemy();
    void InitializeEnemyList(const std::string& filename);
    std::shared_ptr<Enemy> EnemySelect();
    void Battle();
    void Shop();
    void HubArea();
};

#endif //PROIECTOOP_GAME_H
