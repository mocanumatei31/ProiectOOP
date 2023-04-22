#ifndef PROIECTOOP_ENTITY_H
#define PROIECTOOP_ENTITY_H

#include<iostream>

class Entity
{
protected:
    std::string Name;//Character's Name
    int HP, MaxHP, STR, DEF, AGI;//Character's Attributes
public:
    explicit Entity(const std::string &Name_ = "", int HP_ = 100, int MaxHP_ = 100, int STR_ = 1, int DEF_ = 1, int AGI_ = 1);
    virtual void NormalAttack(Entity& e);
    void HP_Depletion(int x);
    bool isAlive();
    int NormalAttackStrength();
    int NormalAttackDefense();
    void HP_Fill();
    bool hasAvoidedAttack();
};

#endif //PROIECTOOP_ENTITY_H
