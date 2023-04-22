#include <iostream>
#include "enemy.h"

Enemy::Enemy(const std::string &Name_, int HP_, int MaxHP_, int STR_, int DEF_, int AGI_):Entity(Name_, HP_, MaxHP_, STR_, DEF_, AGI_){}
std::ostream& operator <<(std::ostream& out, const Enemy& e)
{
    out<<"Enemy's stats:\n";
    out<<"HP: "<<e.HP<<"/"<<e.MaxHP<<"\n";
    out<<"Strength: "<<e.STR<<"\n";
    out<<"Defence: "<<e.DEF<<"\n";
    out<<"Agility: "<<e.AGI<<"\n";
    return out;
}
Enemy& Enemy::operator=(const Enemy& other)
{
    HP=other.HP;
    MaxHP=other.MaxHP;
    STR=other.STR;
    DEF=other.DEF;
    AGI=other.AGI;
    return *this;
}
Enemy::~Enemy(){}
