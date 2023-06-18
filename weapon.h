#ifndef PROIECTOOP_WEAPON_H
#define PROIECTOOP_WEAPON_H

#include <iostream>

template<typename T>
class Weapon{
    std::string type;
    T condition, base_damage;
public:
    explicit Weapon(const std::string& type_="Dagger",T condition_=100, T base_damage_=100);
    Weapon(const Weapon<T>& other);
    template<typename U>
    friend std::ostream& operator <<(std::ostream& out, const Weapon<U>& weapon);
    ~Weapon();
    Weapon& operator=(const Weapon& other);
    bool isFunctional() const;
    T AttackDamage() const;
    T get_condition() const;
    std::string get_type();
    void set_condition(T x);
    void ConditionDecrease(int x);
};

template<typename T>
Weapon<T>::Weapon(const std::string& type_,T condition_, T base_damage_):type(type_),condition(condition_),base_damage(base_damage_){}
template<typename T>
Weapon<T>::Weapon(const Weapon& other):type(other.type), condition(other.condition), base_damage(other.base_damage){}
template<typename U>
std::ostream& operator <<(std::ostream& out, const Weapon<U>& weapon)
{
    out<<"Weapon stats:\n";
    out<<"Weapon Type: "<< weapon.type<<'\n';
    out<<"Condition: "<< weapon.condition<<"\\100\n";
    out<<"Base Damage: "<< weapon.base_damage<<"\n";
    return out;
}
template<typename T>
Weapon<T>::~Weapon(){}
template<typename T>
Weapon<T>& Weapon<T>::operator=(const Weapon& other)
{
    condition=other.condition;
    base_damage=other.base_damage;
    type=other.type;
    return *this;
}
template<typename T>
T Weapon<T>::get_condition() const
{
    return condition;
}
template<typename T>
std::string Weapon<T>::get_type()
{
    return type;
}
template<typename T>
void Weapon<T>::set_condition(T x)
{
    condition=x;
}
template<typename T>
bool Weapon<T>::isFunctional() const
{
    return condition>0;
}
template<typename T>
T Weapon<T>::AttackDamage() const
{
    return base_damage - (100 - condition) * base_damage / 100;
}
template<typename T>
void Weapon<T>::ConditionDecrease(int x)
{
    condition=std::max(0,condition-x);
}

class Weapon_Factory
{
public:
    static Weapon<int> spear();
    static Weapon<int> sword();
    static Weapon<int> dagger();
    static Weapon<int> longsword();
    static Weapon<int> mace();
};
#endif //PROIECTOOP_WEAPON_H
