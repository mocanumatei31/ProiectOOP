#include <iostream>
#include "mage.h"

Mage::Mage(const std::string &Name_, int HP_, int MaxHP_, int STR_, int DEF_, int AGI_, int MANA_):Player(Name_, HP_, MaxHP_, STR_, DEF_, AGI_), MANA(MANA_){}

std::ostream& operator <<(std::ostream& out, const Mage& p)
{
    out<<p.Name<<"'s stats:\n";
    out<<"Class: Mage\n";
    out<<"HP: "<<p.HP<<"/"<<p.MaxHP<<"\n";
    out<<"Strength: "<<p.STR<<"\n";
    out<<"Defence: "<<p.DEF<<"\n";
    out<<"Agility: "<<p.AGI<<"\n";
    out<<"Mana: "<<p.MANA<<"\n";
    out<<"Your Money: "<<p.currency<<"\n";
    out<<p.weapon;
    return out;
}

int Mage::Fireball(std::shared_ptr<Entity>& e)
{
    if(MANA<10)
    {
        std::cout<<"Not Enough Mana!\n";
        return 0;
    }
    MANA-=10;
    std::cout<<Name<<" has used Fireball Spell\n";
    if(e->hasAvoidedAttack())
    {
        std::cout<<"It Missed!\n";
        return 1;
    }
    e->HP_Depletion(std::max(0,5*NormalAttackStrength()-e->NormalAttackDefense()));
    std::cout<<"It has dealt "<<std::max(0,5*NormalAttackStrength()-e->NormalAttackDefense())<<" Damage\n";
    e->Burn();
    return 1;
}

void Mage::NormalAttack(std::shared_ptr<Entity>& e)
{
    std::cout<<Name<<" used Basic Spell\n";
    if(e->hasAvoidedAttack())
    {
        std::cout<<"It missed!\n";
        return;
    }
    e->HP_Depletion(std::max(0,NormalAttackStrength()-e->NormalAttackDefense()));
    std::cout<<"It has dealt "<<std::max(0,NormalAttackStrength()-e->NormalAttackDefense())<<" Damage\n";
}

int Mage::Stun(std::shared_ptr<Entity>& e)
{
    if(MANA<15)
    {
        std::cout<<"Not Enough Mana!\n";
        return 0;
    }
    MANA-=15;
    int stunSuccess=rand()%20;
    std::cout<<Name<<" used Stun\n";
    if(stunSuccess==0)
    {
        std::cout<<"It failed!\n";
        return 1;
    }
    if(e->hasAvoidedAttack())
    {
        std::cout<<"It Missed!\n";
        return 1;
    }
    e->StunDebuff();
    return 1;
}

int Mage::MagicShield()
{
    if(MANA<25)
    {
        std::cout<<"Not Enough Mana!\n";
        return 0;
    }
    std::cout<<Name<<" used Magic Shield\n";
    MANA-=25;
    DEF+=3;
    shieldTime=3;
    return 1;
}

int Mage::Heal()
{
    if(MANA<30)
    {
        std::cout<<"Not Enough Mana!\n";
        return 0;
    }
    MANA-=30;
    std::cout<<Name<<" used Heal\n";
    HP_Fill();
    return 1;
}

void Mage::ApplyEffects()
{
    HP-=std::max(0,5*(int)(burn>0)-DEF);
    burn=std::max(0,burn-1);
    if(stun) stun=false;
    if(shieldTime>0)
    {
        DEF--;
        shieldTime--;
    }
}

void Mage::ResetStats()
{
    HP_Fill();
    DEF=2;
    MANA=50;
    shieldTime=0;
}

void Mage::ShowStats()
{
    std::cout<<Name<<"'s stats:\n";
    std::cout<<"Class: Mage\n";
    std::cout<<"HP: "<<HP<<"/"<<MaxHP<<"\n";
    std::cout<<"Strength: "<<STR<<"\n";
    std::cout<<"Defence: "<<DEF<<"\n";
    std::cout<<"Agility: "<<AGI<<"\n";
    std::cout<<"Mana: "<<MANA<<"/50"<<"\n";
    std::cout<<"Your Money: "<<currency<<"\n";
    std::cout<<weapon;
}