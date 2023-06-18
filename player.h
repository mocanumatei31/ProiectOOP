#ifndef PROIECTOOP_PLAYER_H
#define PROIECTOOP_PLAYER_H
#include<iostream>
#include "weapon.h"
#include "enemy.h"
#include "entity.h"

class Player:public Entity
{
protected:
    Weapon<int> weapon;//Player Character's Equipped Weapon
    int currency = 0;//Player Character's Money
    Player(const Player &other);
    Player& operator=(const Player& other);
public:
    explicit Player(const std::string &Name_ = "", int HP_ = 100, int MaxHP_ = 100, int STR_ = 1, int DEF_ = 1, int AGI_ = 1);
    friend std::ostream &operator<<(std::ostream &out, const Player &p);
    friend std::istream& operator >>(std::istream& in, Player& p);
    ~Player() override;
    virtual void NormalWeaponAttack(std::shared_ptr<Entity>& e);
    virtual void LightWeaponAttack(std::shared_ptr<Entity>& e);
    void WeaponChange(const Weapon<int> &newWeapon);
    int get_currency();
    int get_weaponcondition();
    std::string get_weapontype();
    void GainCurrency(int x);
    void SpendCurrency(int x);
    void ShowCurrencyAmount() const;
    virtual void ResetStats()=0;
    virtual void ShowAvailableAttacks()=0;
    virtual void ShowStats()=0;
    virtual void ShowAvailableActions()=0;
};

#endif //PROIECTOOP_PLAYER_H
