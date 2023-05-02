#include <iostream>
#include "entity.h"

Entity::Entity(const std::string &Name_, int HP_, int MaxHP_, int STR_, int DEF_, int AGI_): Name(Name_), HP(HP_), MaxHP(MaxHP_), STR(STR_), DEF(DEF_) ,AGI(AGI_){}

void Entity::NameCharacter(const std::string& name)
{
    Name=name;
}
void Entity::NormalAttack(std::shared_ptr<Entity>& e)
{
    if(isStunned())
    {
        std::cout<<Name<<" is stunned\n";
        return;
    }
    std::cout<<Name<<" used Normal Attack\n";
    if(e->hasAvoidedAttack())
    {
        std::cout<<"It missed!\n";
        return;
    }
    e->HP_Depletion(std::max(0,NormalAttackStrength()-e->NormalAttackDefense()));
    std::cout<<"It has dealt "<<std::max(0,NormalAttackStrength()-e->NormalAttackDefense())<<" Damage\n";
}

void Entity::HP_Depletion(const int x)
{
    HP=std::max(0,HP-x);
}

bool Entity::isAlive() const
{
    return HP>0;
}

int Entity::NormalAttackStrength() const
{
    return 25+25*STR/10;
}

int Entity::NormalAttackDefense() const
{
    return 25 * DEF / 10;
}

void Entity::HP_Fill()
{
    HP=MaxHP;
}

bool Entity::hasAvoidedAttack() const
{
    int chance = rand()%40;
    return AGI>chance;
}

void Entity::Burn()
{
    burn=3;
}

void Entity::StunDebuff()
{
    stun=true;
}

bool Entity::isStunned() const
{
    return stun;
}

//Applies all buffs/debuffs currently affecting the character
//Will be called at the end of each turn
void Entity::ApplyEffects()
{
    HP-=std::max(0,5*(int)(burn>0)-DEF);
    burn=std::max(0,burn-1);
    if(stun) stun=false;
}