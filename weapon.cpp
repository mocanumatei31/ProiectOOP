#include "weapon.h"

MeleeWeapon::MeleeWeapon(const std::string &type_, int condition_, int base_damage_): Weapon(type_,base_damage_),condition(condition_){}
void MeleeWeapon::set_condition(int x)
{
    condition=x;
}
bool MeleeWeapon::isFunctional() const
{
    return condition>0;
}
int MeleeWeapon::AttackDamage() const
{
    return base_damage - (100 - condition) * base_damage / 100;
}
void MeleeWeapon::ConditionDecrease(int x)
{
    condition=std::max(0,condition-x);
}
int MeleeWeapon::get_condition() const
{
    return condition;
}
void MeleeWeapon::ShowStats() const {
    std::cout<<*this;
    std::cout<<"Weapon Condition: "<<condition<<"/100\n";
}

RangedWeapon::RangedWeapon(const std::string &type_, int base_damage_, int ammo_): Weapon(type_,base_damage_), ammo(ammo_), maxammo(ammo_){}
int RangedWeapon::AttackDamage() const
{
    return base_damage;
}
void RangedWeapon::ReplenishAmmo()
{
    ammo=maxammo;
}
bool RangedWeapon::hasAmmo()
{
    return ammo>0;
}
int RangedWeapon::get_ammo() const
{
    return ammo;
}
void RangedWeapon::ShowStats() const {
    std::cout<<*this;
    std::cout<<"Ammo: "<<ammo<<"/"<<maxammo<<"\n";
}
void RangedWeapon::useAmmo()
{
    ammo--;
}
MeleeWeapon Weapon_Factory::dagger() {return MeleeWeapon("Dagger", 100, 100);}
MeleeWeapon Weapon_Factory::spear() {return MeleeWeapon("Spear", 125, 125);}
MeleeWeapon Weapon_Factory::sword() {return MeleeWeapon("Sword", 100, 150);}
MeleeWeapon Weapon_Factory::longsword() {return MeleeWeapon("Longsword", 150, 200);}
MeleeWeapon Weapon_Factory::mace() {return MeleeWeapon("Mace", 80, 250);}
RangedWeapon Weapon_Factory::bow() {return RangedWeapon("Bow", 30, 3);}
RangedWeapon Weapon_Factory::crossbow() {return RangedWeapon("Crossbow", 100, 1);}
RangedWeapon Weapon_Factory::gun() {return RangedWeapon("Gun", 125, 5);}