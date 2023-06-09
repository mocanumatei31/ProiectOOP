#ifndef PROIECTOOP_WARRIOR_H
#define PROIECTOOP_WARRIOR_H

#include "player.h"

class Warrior: public Player
{
    int rageMeter=0;
    bool rage= false;
public:
    explicit Warrior(const std::string &Name_ = "", int HP_ = 250, int MaxHP_ = 250, int STR_ = 4, int DEF_ = 4, int AGI_ = 1);
    std::shared_ptr<Entity> clone() const override;
    void HeavyWeaponAttack(std::shared_ptr<Entity>& e);
    void NormalAttack(std::shared_ptr<Entity>& e) override;
    void NormalWeaponAttack(std::shared_ptr<Entity>& e) override;
    void LightWeaponAttack(std::shared_ptr<Entity>& e) override;
    void activateRage();
    bool isRageFilled();
    void ApplyEffects() override;
    void ResetStats() override;
    void ShowStats() override;
    void ShowAvailableAttacks() override;
    void ShowAvailableActions() override;
};

#endif //PROIECTOOP_WARRIOR_H
