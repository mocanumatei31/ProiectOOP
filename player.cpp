#include <iostream>
#include "player.h"

Player::Player(const std::string& Name_, int HP_, int MaxHP_, int STR_, int DEF_, int AGI_):Entity(Name_, HP_, MaxHP_, STR_, DEF_, AGI_){}
//Player::Player(const Player& other):weapon(other.weapon), Name(other.Name), HP(other.HP), MaxHP(other.MaxHP), STR(other.STR), DEF(other.DEF), AGI(other.AGI){}

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

Player& Player::operator=(const Player& other)
{
    Name=other.Name;
    HP=other.HP;
    MaxHP=other.MaxHP;
    STR=other.STR;
    DEF=other.DEF;
    AGI=other.AGI;
    weapon=other.weapon;
    return *this;
}

Player::~Player(){}

void Player::NormalWeaponAttack(Enemy& e)
{
    if(weapon.isFunctional())
    {
        std::cout<<Name<<" used Weapon Attack\n";
        if(e.hasAvoidedAttack())
        {
            std::cout<<"It missed!\n";
            return;
        }
        e.HP_Depletion(std::max(0,weapon.AttackDamage()-e.NormalAttackDefense()));
        std::cout<<"It has dealt "<<std::max(0,weapon.AttackDamage()-e.NormalAttackDefense())<<" Damage\n";
        weapon.ConditionDecrease(5);
    }
    else
    {
        std::cout<<"You can't use a broken weapon\n";
    }
}

void Player::LightWeaponAttack(Enemy& e)
{
    if(weapon.isFunctional())
    {
        std::cout<<Name<<" used Light Weapon Attack\n";
        if(e.hasAvoidedAttack())
        {
            std::cout<<"It missed!\n";
            return;
        }
        e.HP_Depletion(std::max(0,weapon.AttackDamage()/3*2-e.NormalAttackDefense()));
        std::cout<<"It has dealt "<<std::max(0,weapon.AttackDamage()/3*2-e.NormalAttackDefense())<<" Damage\n";
        weapon.ConditionDecrease(3);
    }
    else
    {
        std::cout<<"You can't use a broken weapon\n";
    }
}

bool Player::isWeaponFunctional()
{
    return weapon.isFunctional();
}

void Player::WeaponChange(const Weapon &newWeapon)
{
    weapon=newWeapon;
}

void Player::GainCurrency(int x)
{
    currency+=x;
}

//Decreases currency and returns 1 if Player has enough currency to make payment
//Otherwise returns -1
int Player::SpendCurrency(int x)
{
    if(currency-x>=0)
    {
        currency-=x;
        return 1;
    }
    else return -1;
}

void Player::ShowCurrencyAmount()
{
    std::cout<<"Your Money: "<<currency<<"\n";
}
