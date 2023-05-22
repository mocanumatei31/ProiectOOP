#include "rogue.h"
#include "exceptions.h"

Rogue::Rogue(const std::string &Name_, int HP_, int MaxHP_, int STR_, int DEF_, int AGI_):Player(Name_, HP_, MaxHP_, STR_, DEF_, AGI_){}

std::shared_ptr<Entity> Rogue::clone() const
{
    return std::make_shared<Rogue>(*this);
}

void Rogue::NormalAttack(std::shared_ptr<Entity>& e)
{
    std::cout<<Name<<" used Normal Attack\n";
    if(e->hasAvoidedAttack())
    {
        std::cout<<"It missed!\n";
        return;
    }
    int attackDamage=std::max(0,NormalAttackStrength()-e->NormalAttackDefense());
    e->HP_Depletion(attackDamage);
    std::cout<<"It has dealt "<<attackDamage<<" Damage\n";
    int additionalSlashCheck=rand()%5;
    if(additionalSlashCheck<=1)
    {
        std::cout<<"Additional Rogue Slash Triggered\n";
        e->HP_Depletion(attackDamage);
        std::cout<<"It has dealt an additional "<<attackDamage<<" Damage\n";
    }
}

void Rogue::NormalWeaponAttack(std::shared_ptr<Entity>& e)
{
    if(!weapon.isFunctional()) throw WeaponError("You can't use a broken weapon\n");
    std::cout<<Name<<" used Weapon Attack\n";
    if(e->hasAvoidedAttack())
    {
        std::cout<<"It missed!\n";
        return;
    }
    int attackDamage=std::max(0,weapon.AttackDamage()-e->NormalAttackDefense());
    e->HP_Depletion(attackDamage);
    std::cout<<"It has dealt "<<attackDamage<<" Damage\n";
    weapon.ConditionDecrease(5);
    int additionalSlashCheck=rand()%5;
    if(additionalSlashCheck<=1)
    {
        std::cout<<"Additional Rogue Slash Triggered\n";
        e->HP_Depletion(attackDamage);
        std::cout<<"It has dealt an additional "<<attackDamage<<" Damage\n";
    }
}

void Rogue::LightWeaponAttack(std::shared_ptr<Entity>& e)
{
    if(!weapon.isFunctional()) throw WeaponError("You can't use a broken weapon\n");
    std::cout<<Name<<" used Light Weapon Attack\n";
    if(e->hasAvoidedAttack())
    {
        std::cout<<"It missed!\n";
        return;
    }
    int attackDamage=std::max(0,weapon.AttackDamage()/3*2-e->NormalAttackDefense());
    e->HP_Depletion(attackDamage);
    std::cout<<"It has dealt "<<attackDamage<<" Damage\n";
    weapon.ConditionDecrease(3);
    int additionalSlashCheck=rand()%5;
    if(additionalSlashCheck<=1)
    {
        std::cout<<"Additional Rogue Slash Triggered\n";
        e->HP_Depletion(attackDamage);
        std::cout<<"It has dealt an Additional "<<attackDamage<<" Damage\n";
    }
}

void Rogue::ResetStats()
{
    Player::ResetStats();
}

void Rogue::ShowAvailableAttacks()
{
    Player::ShowAvailableAttacks();
}

void Rogue::ShowStats()
{
    std::cout<<Name<<"'s stats:\n";
    std::cout<<"Class: Rogue\n";
    std::cout<<"HP: "<<HP<<"/"<<MaxHP<<"\n";
    std::cout<<"Strength: "<<STR<<"\n";
    std::cout<<"Defence: "<<DEF<<"\n";
    std::cout<<"Agility: "<<AGI<<"\n";
    std::cout<<"Your Money: "<<currency<<"\n";
    std::cout<<weapon;
}

void Rogue::ShowAvailableActions()
{
    std::cout<<"Please choose an action:\n";
    std::cout<<"1.Punch\n";
    std::cout<<"2.Use Weapon\n";
    std::cout<<"4.Check Current Stats\n";
    std::cout<<"5.Flee\n";
}
