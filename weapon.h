#ifndef PROIECTOOP_WEAPON_H
#define PROIECTOOP_WEAPON_H

#include <iostream>

class Weapon{
    std::string type;
    int condition, base_damage;
    //bool isEquipped;
public:
    Weapon(const std::string& type_="Sword",int condition_=100, int base_damage_=150);
    Weapon(const Weapon& other);
    friend std::ostream& operator <<(std::ostream& out, const Weapon& weapon);
    ~Weapon();
    Weapon& operator=(const Weapon& other);
    bool isFunctional();
    int AttackDamage();
    void ConditionDecrease(int x);
};


#endif //PROIECTOOP_WEAPON_H
