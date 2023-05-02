#include <iostream>
#include "warrior.h"

Warrior::Warrior(const std::string &Name_, int HP_, int MaxHP_, int STR_, int DEF_, int AGI_):Player(Name_, HP_, MaxHP_, STR_, DEF_, AGI_){}
std::ostream& operator <<(std::ostream& out, const Warrior& p)
{
    out<<p.Name<<"'s stats:\n";
    out<<"Class: Warrior\n";
    out<<"HP: "<<p.HP<<"/"<<p.MaxHP<<"\n";
    out<<"Strength: "<<p.STR<<"\n";
    out<<"Defence: "<<p.DEF<<"\n";
    out<<"Agility: "<<p.AGI<<"\n";
    out<<"Your Money: "<<p.currency<<"\n";
    out<<"Rage meter: "<<p.rageMeter<<"/5\n";
    out<<p.weapon;
    return out;
}
void Warrior::NormalAttack(std::shared_ptr<Entity>& e)
{
    if(e->isStunned())
    {
        std::cout<<Name<<" is stunned\n";
        return;
    }
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
    if(weapon.isFunctional())
    {
        std::cout<<Name<<" used Weapon Attack\n";
        if(e->hasAvoidedAttack())
        {
            std::cout<<"It missed!\n";
            return;
        }
        if(rageMeter<5 && !rage) rageMeter++;
        e->HP_Depletion(std::max(0,weapon.AttackDamage()+50*(int)rage-e->NormalAttackDefense()));
        std::cout<<"It has dealt "<<std::max(0,weapon.AttackDamage()+50*(int)rage-e->NormalAttackDefense())<<" Damage\n";
        weapon.ConditionDecrease(5);
    }
    else
    {
        std::cout<<"You can't use a broken weapon\n";
    }
}

void Warrior::LightWeaponAttack(std::shared_ptr<Entity>& e)
{
    if(weapon.isFunctional())
    {
        std::cout<<Name<<" used Light Weapon Attack\n";
        if(e->hasAvoidedAttack())
        {
            std::cout<<"It missed!\n";
            return;
        }
        if(rageMeter<5 && !rage) rageMeter++;
        e->HP_Depletion(std::max(0,weapon.AttackDamage()/3*2+50*(int)rage-e->NormalAttackDefense()));
        std::cout<<"It has dealt "<<std::max(0,weapon.AttackDamage()/3*2+50*(int)rage-e->NormalAttackDefense())<<" Damage\n";
        weapon.ConditionDecrease(3);
    }
    else
    {
        std::cout<<"You can't use a broken weapon\n";
    }
}
void Warrior::HeavyWeaponAttack(std::shared_ptr<Entity>& e)
{
    if(weapon.isFunctional())
    {
        std::cout<<Name<<" used Heavy Weapon Attack\n";
        if(e->hasAvoidedAttack())
        {
            std::cout<<"It missed!\n";
            return;
        }
        if(rageMeter<5 && !rage) rageMeter=std::min(5,rageMeter+2);
        e->HP_Depletion(std::max(0,weapon.AttackDamage()*3/2+50*(int)rage-e->NormalAttackDefense()));
        std::cout<<"It has dealt "<<std::max(0,weapon.AttackDamage()*3/2+50*(int)rage-e->NormalAttackDefense())<<" Damage\n";
        weapon.ConditionDecrease(10);
    }
    else
    {
        std::cout<<"You can't use a broken weapon\n";
    }
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
    HP_Fill();
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
    std::cout<<weapon;
}