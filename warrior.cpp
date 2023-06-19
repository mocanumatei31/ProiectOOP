#include <iostream>
#include "warrior.h"
#include "exceptions.h"

Warrior::Warrior(const std::string &Name_, int HP_, int MaxHP_, int STR_, int DEF_, int AGI_):Player(Name_, HP_, MaxHP_, STR_, DEF_, AGI_){}

std::shared_ptr<Entity> Warrior::clone() const
{
    return std::make_shared<Warrior>(*this);
}

void Warrior::NormalAttack(std::shared_ptr<Entity>& e)
{
    std::cout<<Name<<" used Normal Attack\n";
    if(e->hasAvoidedAttack())
    {
        std::cout<<"It missed!\n";
        return;
    }
    if(rageMeter<5 && !rage) rageMeter++;
    e->HP_Depletion(std::max(0,NormalAttackStrength()+50*(int)rage-e->NormalAttackDefense()));
    std::cout<<"It has dealt "<<std::max(0,NormalAttackStrength()+50*(int)rage-e->NormalAttackDefense())<<" Damage\n";
}

void Warrior::NormalWeaponAttack(std::shared_ptr<Entity>& e)
{
    if(!meleeWeapon.isFunctional()) throw WeaponError("You can't use a broken weapon\n");
    std::cout<<Name<<" used Weapon Attack\n";
    if(e->hasAvoidedAttack())
    {
        std::cout<<"It missed!\n";
        return;
    }
    if(rageMeter<5 && !rage) rageMeter++;
    e->HP_Depletion(std::max(0,meleeWeapon.AttackDamage()+50*(int)rage-e->NormalAttackDefense()));
    std::cout<<"It has dealt "<<std::max(0,meleeWeapon.AttackDamage()+50*(int)rage-e->NormalAttackDefense())<<" Damage\n";
    meleeWeapon.ConditionDecrease(5);
}

void Warrior::LightWeaponAttack(std::shared_ptr<Entity>& e)
{
    if(!meleeWeapon.isFunctional()) throw WeaponError("You can't use a broken weapon\n");
    std::cout<<Name<<" used Light Weapon Attack\n";
    if(e->hasAvoidedAttack())
    {
        std::cout<<"It missed!\n";
        return;
    }
    if(rageMeter<5 && !rage) rageMeter++;
    e->HP_Depletion(std::max(0,meleeWeapon.AttackDamage()/3*2+50*(int)rage-e->NormalAttackDefense()));
    std::cout<<"It has dealt "<<std::max(0,meleeWeapon.AttackDamage()/3*2+50*(int)rage-e->NormalAttackDefense())<<" Damage\n";
    meleeWeapon.ConditionDecrease(3);

}
void Warrior::HeavyWeaponAttack(std::shared_ptr<Entity>& e)
{
    if(!meleeWeapon.isFunctional()) throw WeaponError("You can't use a broken weapon\n");
    std::cout<<Name<<" used Heavy Weapon Attack\n";
    if(e->hasAvoidedAttack())
    {
        std::cout<<"It missed!\n";
        return;
    }
    if(rageMeter<5 && !rage) rageMeter=std::min(5,rageMeter+2);
    int attackDamage=std::max(0,meleeWeapon.AttackDamage()*3/2+50*(int)rage-e->NormalAttackDefense());
    e->HP_Depletion(attackDamage);
    std::cout<<"It has dealt "<<attackDamage<<" Damage\n";
    meleeWeapon.ConditionDecrease(10);
}

bool Warrior::isRageFilled()
{
    return rageMeter == 5 && !rage;
}

void Warrior::activateRage()
{
    rage=true;
}

void Warrior::ApplyEffects()
{
    HP-=std::max(0,5*(int)(burn>0)-DEF);
    burn=std::max(0,burn-1);
    if(stun) stun=false;
    if(rageMeter>0 && rage)
    {
        rageMeter--;
        if(rageMeter==0) rage=false;
    }
}

void Warrior::ResetStats()
{
    Player::ResetStats();
    rage=false;
    rageMeter=0;
}

void Warrior::ShowStats()
{
    std::cout<<Name<<"'s stats:\n";
    std::cout<<"Class: Warrior\n";
    std::cout<<"HP: "<<HP<<"/"<<MaxHP<<"\n";
    std::cout<<"Strength: "<<STR<<"\n";
    std::cout<<"Defence: "<<DEF<<"\n";
    std::cout<<"Agility: "<<AGI<<"\n";
    std::cout<<"Rage Meter: "<<rageMeter<<"/5"<<"\n";
    std::cout<<"Your Money: "<<currency<<"\n";
    meleeWeapon.ShowStats();
    rangedWeapon.ShowStats();
}

void Warrior::ShowAvailableAttacks()
{
    Player::ShowAvailableAttacks();
    std::cout<<"3.Heavy Attack\n";
}
void Warrior::ShowAvailableActions()
{
    std::cout<<"Please choose an action:\n";
    std::cout<<"1.Punch\n";
    std::cout<<"2.Use Melee Weapon\n";
    std::cout<<"4.Use Ranged Attack\n";
    std::cout<<"5.Check Current Stats\n";
    std::cout<<"6.Flee\n";
    if(isRageFilled())std::cout<<"Rage Meter is Full! Press 9 to unlock\n";
}
