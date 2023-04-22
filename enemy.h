#ifndef PROIECTOOP_ENEMY_H
#define PROIECTOOP_ENEMY_H

#include "entity.h"
#include <iostream>

class Enemy:public Entity
{
public:
    Enemy(const std::string &Name_="", int HP_=0, int MaxHP_=0, int STR_=0, int DEF_=0, int AGI_=0);
    friend std::ostream& operator <<(std::ostream& out, const Enemy& e);
    Enemy& operator=(const Enemy& other);
    ~Enemy();
};

#endif //PROIECTOOP_ENEMY_H
