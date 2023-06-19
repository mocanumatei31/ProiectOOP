#ifndef PROIECTOOP_WEAPON_H
#define PROIECTOOP_WEAPON_H

#include <iostream>
#include <memory>

template<typename T>
class Weapon{
protected:
    std::string type;
    int base_damage;
public:
    explicit Weapon(const std::string& type_="", int base_damage_=100);
    Weapon(const Weapon<T>& other);
    template<typename U>
    friend std::ostream& operator <<(std::ostream& out, const Weapon<U>& weapon);
    virtual ~Weapon();
    Weapon& operator=(const Weapon& other);
    virtual int AttackDamage() const=0;
    virtual void ShowStats() const=0;
    std::string get_type();
};

template<typename T>
Weapon<T>::Weapon(const std::string& type_, int base_damage_):type(type_),base_damage(base_damage_){}
template<typename T>
Weapon<T>::Weapon(const Weapon& other):type(other.type), base_damage(other.base_damage){}
template<typename U>
std::ostream& operator <<(std::ostream& out, const Weapon<U>& weapon)
{
    out<<"Weapon stats:\n";
    out<<"Weapon Type: "<< weapon.type<<'\n';
    out<<"Base Damage: "<< weapon.base_damage<<"\n";
    return out;
}
template<typename T>
Weapon<T>::~Weapon(){}
template<typename T>
Weapon<T>& Weapon<T>::operator=(const Weapon& other)
{
    base_damage=other.base_damage;
    type=other.type;
    return *this;
}

template<typename T>
std::string Weapon<T>::get_type()
{
    return type;
}

class RangedWeapon: public Weapon<RangedWeapon>
{
    int ammo, maxammo;
public:
    RangedWeapon(const std::string& type_="Bow", int base_damage_=30, int ammo_=3);
    void ReplenishAmmo();
    int AttackDamage() const override;
    void ShowStats() const override;
    bool hasAmmo();
    int get_ammo() const;
    void useAmmo();
};

class MeleeWeapon: public Weapon<MeleeWeapon>
{
    int condition;
public:
    MeleeWeapon(const std::string& type_="Dagger",int condition_=100, int base_damage_=100);
    void set_condition(int x);
    void ConditionDecrease(int x);
    int get_condition() const;
    bool isFunctional() const;
    int AttackDamage() const override;
    void ShowStats() const override;

};

class Weapon_Factory
{
public:
    static MeleeWeapon spear();
    static MeleeWeapon sword();
    static MeleeWeapon dagger();
    static MeleeWeapon longsword();
    static MeleeWeapon mace();
    static RangedWeapon bow();
    static RangedWeapon crossbow();
    static RangedWeapon gun();
};
#endif //PROIECTOOP_WEAPON_H
