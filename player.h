#ifndef PROIECTOOP_PLAYER_H
#define PROIECTOOP_PLAYER_H
#include<iostream>
#include "weapon.h"
#include "enemy.h"
#include "entity.h"

class Player:public Entity
{
    Weapon weapon;//Player Character's Equipped Weapon
    int currency = 0;//Player Character's Money
public:
    Player(const std::string &Name_ = "", int HP_ = 100, int MaxHP_ = 100, int STR_ = 1, int DEF_ = 1, int AGI_ = 1);
    //Player(const Player &other);
    friend std::ostream &operator<<(std::ostream &out, const Player &p);
    friend std::istream& operator >>(std::istream& in, Player& p);
    Player& operator=(const Player& other);
    ~Player();
    void NormalWeaponAttack(Enemy& e);
    void LightWeaponAttack(Enemy& e);
    bool isWeaponFunctional();
    void WeaponChange(const Weapon &newWeapon);
    void GainCurrency(int x);
    int SpendCurrency(int x);
    void ShowCurrencyAmount();
};

#endif //PROIECTOOP_PLAYER_H
