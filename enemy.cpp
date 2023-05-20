#include <iostream>
#include "enemy.h"

Enemy::Enemy(const std::string &Name_, int HP_, int MaxHP_, int STR_, int DEF_, int AGI_):Entity(Name_, HP_, MaxHP_, STR_, DEF_, AGI_){}
std::ostream& operator <<(std::ostream& out, const Enemy& e)
{
    out<<e.Name<<"'s stats:\n";
    out<<"HP: "<<e.HP<<"/"<<e.MaxHP<<"\n";
    out<<"Strength: "<<e.STR<<"\n";
    out<<"Defence: "<<e.DEF<<"\n";
    out<<"Agility: "<<e.AGI<<"\n";
    return out;
}
std::shared_ptr<Entity> Enemy::clone() const
{
    return std::make_shared<Enemy>(*this);
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
Enemy::~Enemy()= default;

std::string Enemy::get_name()
{
    return Name;
}

Enemy Enemy_Factory::troll(){ return Enemy("Troll",1000,1000,9,8,1);}
Enemy Enemy_Factory::ogre(){ return Enemy("Ogre",750,750,4,7,3);}
Enemy Enemy_Factory::knight(){ return Enemy("Knight",350,350,6,4,5);}
Enemy Enemy_Factory::ninja(){ return Enemy("Ninja",170,170,4,4,9);}
Enemy Enemy_Factory::goblin(){ return Enemy("Goblin",150,150,3,3,3);}

Enemy_Builder::Enemy_Builder()
{
    enemy=std::make_shared<Enemy>(Enemy());
}

void Enemy_Builder::ShowCurrentState()
{
    std::cout<<*enemy;
}

Enemy_Builder& Enemy_Builder::Name(const std::string& Name_)
{
    enemy->Name = Name_;
    return *this;
}
Enemy_Builder& Enemy_Builder::HP(int HP_)
{
    enemy->HP = enemy->MaxHP = HP_;
    return *this;
}
Enemy_Builder& Enemy_Builder::STR(int STR_)
{
    enemy->STR = STR_;
    return *this;
}
Enemy_Builder& Enemy_Builder::DEF(int DEF_)
{
    enemy->DEF = DEF_;
    return *this;
}
Enemy_Builder& Enemy_Builder::AGI(int AGI_)
{
    enemy->AGI = AGI_;
    return *this;
}
std::shared_ptr<Enemy> Enemy_Builder::build()
{
    std::shared_ptr<Enemy> enemyFinal = enemy;
    enemy = std::make_shared<Enemy>(Enemy());
    return enemyFinal;
}
