#include <iostream>
#include "entity.h"
#include "player.h"
#include "exceptions.h"
#include "weapon.h"

Player::Player(const std::string& Name_, int HP_, int MaxHP_, int STR_, int DEF_, int AGI_):Entity(Name_, HP_, MaxHP_, STR_, DEF_, AGI_){}

Player::Player(const Player &other)=default;
Player& Player::operator=(const Player& other)=default;

std::ostream& operator <<(std::ostream& out, const Player& p)
{
    out<<p.Name<<"'s stats:\n";
    out<<"HP: "<<p.HP<<"/"<<p.MaxHP<<"\n";
    out<<"Strength: "<<p.STR<<"\n";
    out<<"Defence: "<<p.DEF<<"\n";
    out<<"Agility: "<<p.AGI<<"\n";
    out<<"Your Money: "<<p.currency<<"\n";
    out<<p.weapon;
    return out;
}


std::istream& operator >>(std::istream& in, Player& p)
{
    in>>p.Name;
    return in;
}

Player::~Player()= default;

void Player::NormalWeaponAttack(std::shared_ptr<Entity>& e)
{
    if(!weapon.isFunctional()) throw WeaponError("You can't use a broken weapon\n");
    std::cout<<Name<<" used Weapon Attack\n";
    if(e->hasAvoidedAttack())
    {
        std::cout<<"It missed!\n";
        return;
    }
    int attackDamage=std::max(0,weapon.AttackDamage()-e->NormalAttackDefense());
    e->HP_Depletion(attackDamage);
    std::cout<<"It has dealt "<<attackDamage<<" Damage\n";
    weapon.ConditionDecrease(5);
}

void Player::LightWeaponAttack(std::shared_ptr<Entity>& e)
{
    if(!weapon.isFunctional()) throw WeaponError("You can't use a broken weapon\n");
    std::cout<<Name<<" used Light Weapon Attack\n";
    if(e->hasAvoidedAttack())
    {
        std::cout<<"It missed!\n";
        return;
    }
    int attackDamage=std::max(0,weapon.AttackDamage()/3*2-e->NormalAttackDefense());
    e->HP_Depletion(attackDamage);
    std::cout<<"It has dealt "<<attackDamage<<" Damage\n";
    weapon.ConditionDecrease(3);
}

void Player::WeaponChange(const Weapon<int> &newWeapon)
{
    weapon=newWeapon;
}

void Player::GainCurrency(int x)
{
    currency+=x;
}

void Player::SpendCurrency(int x)
{
    if(currency<x) throw CurrencyError("You don't have enough money to buy this.\n");
    currency-=x;
}

void Player::ShowCurrencyAmount() const
{
    std::cout<<"Your Money: "<<currency<<"\n";
}

void Player::ResetStats()
{
    HP_Fill();
}

void Player::ShowAvailableAttacks()
{
    std::cout<<"Choose your Attack Type\n";
    std::cout<<"1.Light Attack\n";
    std::cout<<"2.Normal Attack\n";
}
