#ifndef PROIECTOOP_ENEMY_H
#define PROIECTOOP_ENEMY_H

#include "entity.h"
#include <iostream>
#include<memory>

class Enemy:public Entity
{
    friend class Enemy_Builder;
public:
    std::shared_ptr<Entity> clone() const override;
    explicit Enemy(const std::string &Name_="", int HP_=100, int MaxHP_=100, int STR_=1, int DEF_=1, int AGI_=1);
    friend std::ostream& operator <<(std::ostream& out, const Enemy& e);
    Enemy& operator=(const Enemy& other);
    ~Enemy() override;
    std::string get_name();
};

class Enemy_Factory
{
public:
    static Enemy troll();
    static Enemy ogre();
    static Enemy knight();
    static Enemy ninja();
    static Enemy goblin();
};

class Enemy_Builder {
private:
    std::shared_ptr<Enemy> enemy;
public:
    Enemy_Builder();
    Enemy_Builder(const Enemy_Builder& other) = delete;
    Enemy_Builder& operator=(const Enemy_Builder& other) = delete;
    void ShowCurrentState();
    Enemy_Builder& Name(const std::string& Name_);
    Enemy_Builder& HP(int HP_);
    Enemy_Builder& STR(int STR_);
    Enemy_Builder& DEF(int DEF_);
    Enemy_Builder& AGI(int AGI_);
    std::shared_ptr<Enemy> build();
};


#endif //PROIECTOOP_ENEMY_H
