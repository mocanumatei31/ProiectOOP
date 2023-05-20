#include "weapon.h"
#include <iostream>

Weapon::Weapon(const std::string& type_,int condition_, int base_damage_):type(type_),condition(condition_),base_damage(base_damage_){}
Weapon::Weapon(const Weapon& other):type(other.type), condition(other.condition), base_damage(other.base_damage){}
std::ostream& operator <<(std::ostream& out, const Weapon& weapon)
{
    out<<"Weapon stats:\n";
    out<<"Weapon Type: "<< weapon.type<<'\n';
    out<<"Condition: "<< weapon.condition<<"\\100\n";
    out<<"Base Damage: "<< weapon.base_damage<<"\n";
    return out;
}
Weapon::~Weapon(){}
Weapon& Weapon::operator=(const Weapon& other)
{
        condition=other.condition;
        base_damage=other.base_damage;
        type=other.type;
        return *this;
}
bool Weapon::isFunctional() const
{
    return condition>0;
}
int Weapon::AttackDamage() const
{
    return base_damage - (100 - condition) * base_damage / 100;
}
void Weapon::ConditionDecrease(int x)
{
    condition=std::max(0,condition-x);
}

Weapon Weapon_Factory::dagger() {return Weapon("Dagger", 100, 100);}
Weapon Weapon_Factory::spear() {return Weapon("Spear", 125, 125);}
Weapon Weapon_Factory::sword() {return Weapon("Sword", 100, 150);}
Weapon Weapon_Factory::longsword() {return Weapon("Longsword", 150, 200);}
Weapon Weapon_Factory::mace() {return Weapon("Mace", 80, 250);}