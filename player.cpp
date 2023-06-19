#include <iostream>
#include "entity.h"
#include "player.h"
#include "exceptions.h"
#include "weapon.h"

Player::Player(const std::string& Name_, int HP_, int MaxHP_, int STR_, int DEF_, int AGI_):Entity(Name_, HP_, MaxHP_, STR_, DEF_, AGI_)
{
    rangedWeapon=Weapon_Factory::bow();
    meleeWeapon=Weapon_Factory::dagger();
}

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
    p.meleeWeapon.ShowStats();
    p.rangedWeapon.ShowStats();
    return out;
}


std::istream& operator >>(std::istream& in, Player& p)
{
    in>>p.Name;
    return in;
}

Player::~Player()= default;

int Player::get_currency() const
{
    return currency;
}

int Player::get_weaponcondition()
{
    return meleeWeapon.get_condition();
}

std::string Player::get_meleeweapontype()
{
    return meleeWeapon.get_type();
}
std::string Player::get_rangedweapontype()
{
    return rangedWeapon.get_type();
}

int Player::get_ammo()
{
    return rangedWeapon.get_ammo();
}


void Player::NormalWeaponAttack(std::shared_ptr<Entity>& e)
{
    if(!meleeWeapon.isFunctional()) throw WeaponError("You can't use a broken weapon\n");
    std::cout<<Name<<" used Weapon Attack\n";
    if(e->hasAvoidedAttack())
    {
        std::cout<<"It missed!\n";
        return;
    }
    int attackDamage=std::max(0,meleeWeapon.AttackDamage()-e->NormalAttackDefense());
    e->HP_Depletion(attackDamage);
    std::cout<<"It has dealt "<<attackDamage<<" Damage\n";
    meleeWeapon.ConditionDecrease(5);
}

void Player::LightWeaponAttack(std::shared_ptr<Entity>& e)
{
    if(!meleeWeapon.isFunctional()) throw WeaponError("You can't use a broken weapon\n");
    std::cout<<Name<<" used Light Weapon Attack\n";
    if(e->hasAvoidedAttack())
    {
        std::cout<<"It missed!\n";
        return;
    }
    int attackDamage=std::max(0,meleeWeapon.AttackDamage()/3*2-e->NormalAttackDefense());
    e->HP_Depletion(attackDamage);
    std::cout<<"It has dealt "<<attackDamage<<" Damage\n";
    meleeWeapon.ConditionDecrease(3);
}

void Player::MeleeWeaponChange(const MeleeWeapon& newWeapon)
{
    meleeWeapon=newWeapon;
}

void Player::RangedWeaponChange(const RangedWeapon& newWeapon)
{
    rangedWeapon=newWeapon;
}

int Player::RangedAttack(std::shared_ptr<Entity>& e)
{
    if(!rangedWeapon.hasAmmo()) return 0;
    std::cout<<Name<<" used Ranged Attack\n";
    rangedWeapon.useAmmo();
    if(e->hasAvoidedAttack())
    {
        std::cout<<"It missed!\n";
        return 1;
    }
    int attackDamage=std::max(0,rangedWeapon.AttackDamage()-e->NormalAttackDefense());
    e->HP_Depletion(attackDamage);
    std::cout<<"It has dealt "<<attackDamage<<" Damage\n";
    return 1;
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
    rangedWeapon.ReplenishAmmo();
    HP_Fill();
}

void Player::ShowAvailableAttacks()
{
    std::cout<<"Choose your Attack Type\n";
    std::cout<<"1.Light Attack\n";
    std::cout<<"2.Normal Attack\n";
}
