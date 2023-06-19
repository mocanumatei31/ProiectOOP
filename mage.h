#ifndef PROIECTOOP_MAGE_H
#define PROIECTOOP_MAGE_H
#include "player.h"
#include "entity.h"

class Mage : public Player
{
    int MANA;
    int shieldTime=0;
public:
    explicit Mage(const std::string &Name_ = "", int HP_ = 150, int MaxHP_ = 150, int STR_ = 2, int DEF_ = 2, int AGI_ = 2, int MANA_=50);
    std::shared_ptr<Entity> clone() const override;
    int Stun(std::shared_ptr<Entity>& e);
    void NormalAttack (std::shared_ptr<Entity>& e) override;
    int Fireball(std::shared_ptr<Entity>& e);
    int MagicShield();
    int Heal();
    void ShowStats() override;
    void ApplyEffects() override;
    void ResetStats() override;
    void ShowAvailableActions() override;
};

#endif //PROIECTOOP_MAGE_H
