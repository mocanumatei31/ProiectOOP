#ifndef PROIECTOOP_ROGUE_H
#define PROIECTOOP_ROGUE_H

#include "player.h"

class Rogue: public Player
{
public:
    explicit Rogue(const std::string &Name_ = "", int HP_ = 150, int MaxHP_ = 150, int STR_ = 1, int DEF_ = 4, int AGI_ = 6);
    std::shared_ptr<Entity> clone() const override;
    void NormalAttack (std::shared_ptr<Entity>& e) override;
    void NormalWeaponAttack(std::shared_ptr<Entity>& e) override;
    void LightWeaponAttack(std::shared_ptr<Entity>& e) override;
    void ResetStats() override;
    void ShowStats() override;
    void ShowAvailableActions() override;
};

#endif //PROIECTOOP_ROGUE_H
