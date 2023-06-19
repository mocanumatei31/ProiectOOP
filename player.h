#ifndef PROIECTOOP_PLAYER_H
#define PROIECTOOP_PLAYER_H
#include<iostream>
#include "weapon.h"
#include "enemy.h"
#include "entity.h"

class Player:public Entity
{
    Player& operator=(const Player& other);
protected:
    MeleeWeapon meleeWeapon;//Player Character's Equipped Melee Weapon
    RangedWeapon rangedWeapon;//Player Character's Equipped Ranged Weapon
    int currency = 0;//Player Character's Money
    Player(const Player &other);
public:
    explicit Player(const std::string &Name_ = "", int HP_ = 100, int MaxHP_ = 100, int STR_ = 1, int DEF_ = 1, int AGI_ = 1);
    friend std::ostream &operator<<(std::ostream &out, const Player &p);
    friend std::istream& operator >>(std::istream& in, Player& p);
    ~Player() override;
    virtual void NormalWeaponAttack(std::shared_ptr<Entity>& e);
    virtual void LightWeaponAttack(std::shared_ptr<Entity>& e);
    int RangedAttack(std::shared_ptr<Entity>& e);
    void MeleeWeaponChange(const MeleeWeapon& newWeapon);
    void RangedWeaponChange(const RangedWeapon& newWeapon);
    int get_currency() const;
    int get_ammo();
    int get_weaponcondition();
    std::string get_rangedweapontype();
    std::string get_meleeweapontype();
    void GainCurrency(int x);
    void SpendCurrency(int x);
    void ShowCurrencyAmount() const;
    virtual void ResetStats()=0;
    virtual void ShowAvailableAttacks();
    virtual void ShowStats()=0;
    virtual void ShowAvailableActions()=0;
};

#endif //PROIECTOOP_PLAYER_H
