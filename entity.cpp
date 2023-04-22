#include <iostream>
#include "entity.h"

Entity::Entity(const std::string &Name_, int HP_, int MaxHP_, int STR_, int DEF_, int AGI_): Name(Name_), HP(HP_), MaxHP(MaxHP_), STR(STR_), DEF(DEF_) ,AGI(AGI_){}

void Entity::NormalAttack(Entity& e)
{
    std::cout<<Name<<" used Normal Attack\n";
    if(e.hasAvoidedAttack())
    {
        std::cout<<"It missed!\n";
        return;
    }
    e.HP_Depletion(std::max(0,NormalAttackStrength()-e.NormalAttackDefense()));
    std::cout<<"It has dealt "<<std::max(0,NormalAttackStrength()-e.NormalAttackDefense())<<" Damage\n";
}

void Entity::HP_Depletion(const int x)
{
    HP=std::max(0,HP-x);
}

bool Entity::isAlive()
{
    return HP>0;
}

int Entity::NormalAttackStrength()
{
    return 25+25*STR/10;
}

int Entity::NormalAttackDefense()
{
    return 25 * DEF / 10;
}

void Entity::HP_Fill()
{
    HP=MaxHP;
}

bool Entity::hasAvoidedAttack()
{
    int chance = rand()%40;
    return AGI>chance;
}