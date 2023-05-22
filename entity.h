#ifndef PROIECTOOP_ENTITY_H
#define PROIECTOOP_ENTITY_H

#include<iostream>
#include <memory>

class Entity
{
protected:
    std::string Name;//Character's Name
    int HP, MaxHP, STR, DEF, AGI;//Character's Attributes
    int burn=0;
    bool stun=false;
    Entity(const Entity& other);
    Entity& operator=(const Entity& other);
public:
    virtual std::shared_ptr<Entity> clone() const=0;
    explicit Entity(const std::string &Name_ = "", int HP_ = 100, int MaxHP_ = 100, int STR_ = 1, int DEF_ = 1, int AGI_ = 1);
    virtual void NormalAttack(std::shared_ptr<Entity>& e);
    void NameCharacter(const std::string& name);
    virtual ~Entity();
    void HP_Depletion(int x);
    bool isAlive() const;
    int NormalAttackStrength() const;
    int NormalAttackDefense() const;
    void HP_Fill();
    bool hasAvoidedAttack() const;
    bool isStunned() const;
    virtual void ApplyEffects();
    void Burn();
    void StunDebuff();
    std::string get_name();
};

#endif //PROIECTOOP_ENTITY_H
