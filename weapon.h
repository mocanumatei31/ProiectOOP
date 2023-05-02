#ifndef PROIECTOOP_WEAPON_H
#define PROIECTOOP_WEAPON_H

#include <iostream>

class Weapon{
    std::string type;
    int condition, base_damage;
    //bool isEquipped;
public:
    explicit Weapon(const std::string& type_="Dagger",int condition_=100, int base_damage_=100);
    Weapon(const Weapon& other);
    friend std::ostream& operator <<(std::ostream& out, const Weapon& weapon);
    ~Weapon();
    Weapon& operator=(const Weapon& other);
    bool isFunctional() const;
    int AttackDamage() const;
    void ConditionDecrease(int x);
};


#endif //PROIECTOOP_WEAPON_H
