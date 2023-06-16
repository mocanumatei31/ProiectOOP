#include "weapon.h"

template class Weapon<int>;

Weapon<int> Weapon_Factory::dagger() {return Weapon<int>("Dagger", 100, 100);}
Weapon<int> Weapon_Factory::spear() {return Weapon<int>("Spear", 125, 125);}
Weapon<int> Weapon_Factory::sword() {return Weapon<int>("Sword", 100, 150);}
Weapon<int> Weapon_Factory::longsword() {return Weapon<int>("Longsword", 150, 200);}
Weapon<int> Weapon_Factory::mace() {return Weapon<int>("Mace", 80, 250);}