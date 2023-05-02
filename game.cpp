#include "game.h"
#include "warrior.h"
#include "mage.h"
#include "player.h"
#include <iostream>
#include <memory>
#include<typeinfo>
#include<cstring>
Game::Game()=default;
//Game::Game(const Game& other):player(other.player){}
Game::~Game()= default;
Game& Game::operator=(const Game& other)= default;
void Game::CharacterCreation()
{
    std::cout<<"Welcome, Adventurer. Please enter your name.\n";
    std::string phname;
    std::cin>>phname;
    while(true)
    {
        std::cout<<"Please choose a class:\n";
        std::cout<<"1.Warrior\n";
        std::cout<<"2.Mage\n";
        int op;
        std::cin>>op;
        switch(op)
        {
            case 1:
            {
                player=std::make_shared<Warrior>(Warrior());
                break;
            }
            case 2:
            {
                Mage ph;
                player=std::make_shared<Mage>(Mage());
                break;
            }
            default:
                std::cout<<"Invalid Input\n";
                break;
        }
        if(op==1 || op==2) break;
    }
    player->NameCharacter(phname);
    std::cout<<"This is your profile:\n";
    std::cout<<*player;
}
void Game::Battle()
{
    std::shared_ptr<Enemy> enemy;
    enemy=std::make_shared<Enemy>("Enemy", 100, 100, 1, 1, 1);
    std::cout<<"This is your opponent:\n";
    std::cout<<*enemy<<"\n";
    std::cout<<"Please choose an action:\n";
    std::cout<<"1.Fight\n";
    std::cout<<"2.Leave\n";
    int op;
    std::cin>>op;
    while(true)
    {
        switch(op)
        {
            case 1:
                std::cout<<"Let the fight begin!\n";
                break;
            case 2:
                std::cout<<"Let us fight another time.\n";
                return;
            default:
                std::cout<<"Invalid input\n";
                break;
        }
        if(op==1) break;
    }
    bool fled=false;
    while(player->isAlive() && enemy->isAlive())
    {
        while(true)
        {
            if(strcmp(typeid(*player).name(),"4Mage")==0)
            {
                int spellType, spellPass;
                std::cout<<"Please choose an action:\n";
                std::cout<<"1.Punch\n";
                std::cout<<"2.Use Weapon\n";
                std::cout<<"3.Use Spell\n";
                std::cout<<"4.Check Current Stats\n";
                std::cout<<"5.Flee\n";
                std::cin>>op;
                bool checkWeapon=true;
                bool invalid=false;
                switch(op)
                {
                    case 1:
                    {
                        std::shared_ptr<Entity>ph=enemy;
                        player->NormalAttack(ph);
                        break;
                    }
                    case 2:
                        checkWeapon=player->isWeaponFunctional();
                        int attackType;
                        std::cout<<"Choose your Attack Type\n";
                        std::cout<<"1.Light Attack\n";
                        std::cout<<"2.Normal Attack\n";
                        std::cin>>attackType;
                        switch(attackType)
                        {
                            case 1:
                            {
                                std::shared_ptr<Entity>ph=enemy;
                                player->LightWeaponAttack(ph);
                                break;
                            }
                            case 2:
                            {
                                std::shared_ptr<Entity>ph=enemy;
                                player->NormalWeaponAttack(ph);
                                break;
                            }
                            default:
                                invalid=true;
                                std::cout<<"Invalid Input\n";
                                break;
                        }
                        break;
                    case 3:
                    {
                        while(true)
                        {
                            std::cout<<"Choose what spell to use\n";
                            std::cout<<"1.Fireball(Mana Cost: 10)\n";
                            std::cout<<"2.Stun(Mana Cost: 15)\n";
                            std::cout<<"3.Magic Shield(Mana Cost: 25)\n";
                            std::cout<<"4.Heal(Mana Cost: 30)\n";
                            std::cout<<"5.Go Back\n";
                            std::cin>>spellType;
                            switch(spellType)
                            {
                                case 1:
                                {
                                    std::shared_ptr<Entity>ph=enemy;
                                    spellPass=dynamic_pointer_cast<Mage>(player)->Fireball(ph);
                                    break;
                                }
                                case 2:
                                {
                                    std::shared_ptr<Entity>ph=enemy;
                                    spellPass=dynamic_pointer_cast<Mage>(player)->Stun(ph);
                                    break;
                                }
                                case 3:
                                {
                                    spellPass=dynamic_pointer_cast<Mage>(player)->MagicShield();
                                    break;
                                }
                                case 4:
                                {
                                    spellPass=dynamic_pointer_cast<Mage>(player)->Heal();
                                    break;
                                }
                                case 5:
                                {
                                    break;
                                }
                                default:
                                    std::cout<<"Invalid Input\n";
                                    break;
                            }
                            if(spellType==5 || (0<spellType && spellType<5 && spellPass==1)) break;
                        }
                        break;
                    }
                    case 4:
                        dynamic_pointer_cast<Mage>(player)->ShowStats();
                        break;
                    case 5:
                        fled=true;
                        break;
                    default:
                        std::cout<<"Invalid Input\n";
                        break;
                }
                if(op==1 || op==5 || (op==2 && checkWeapon && !invalid) || (op==3 && spellPass==1)) break;
            }
            else if(strcmp(typeid(*player).name(),"7Warrior")==0)
            {
                std::cout<<"Please choose an action:\n";
                std::cout<<"1.Punch\n";
                std::cout<<"2.Use Weapon\n";
                std::cout<<"3.Check Current Stats\n";
                std::cout<<"4.Flee\n";
                if(dynamic_pointer_cast<Warrior>(player)->isRageFilled())std::cout<<"Rage Meter is Full! Press 9 to unlock\n";
                std::cin>>op;
                bool checkWeapon=true;
                bool invalid=false;
                switch(op)
                {
                    case 1:
                    {
                        std::shared_ptr<Entity>ph=enemy;
                        player->NormalAttack(ph);
                        break;
                    }
                    case 2:
                        checkWeapon=player->isWeaponFunctional();
                        int attackType;
                        std::cout<<"Choose your Attack Type\n";
                        std::cout<<"1.Light Attack\n";
                        std::cout<<"2.Normal Attack\n";
                        std::cout<<"3.Heavy Attack\n";
                        std::cin>>attackType;
                        switch(attackType)
                        {
                            case 1:
                            {
                                std::shared_ptr<Entity>ph=enemy;
                                player->LightWeaponAttack(ph);
                                break;
                            }
                            case 2:
                            {
                                std::shared_ptr<Entity>ph=enemy;
                                player->NormalWeaponAttack(ph);
                                break;
                            }
                            case 3:
                            {
                                std::shared_ptr<Entity>ph=enemy;
                                dynamic_pointer_cast<Warrior>(player)->HeavyWeaponAttack(ph);
                                break;
                            }
                            default:
                                invalid=true;
                                std::cout<<"Invalid Input\n";
                                break;
                        }
                        break;
                    case 3:
                        dynamic_pointer_cast<Warrior>(player)->ShowStats();
                        break;
                    case 4:
                        fled=true;
                        break;
                    case 9:
                        if(dynamic_pointer_cast<Warrior>(player)->isRageFilled())
                        {
                            dynamic_pointer_cast<Warrior>(player)->activateRage();
                            std::cout<<"Rage Mode Activated\n";
                        }
                        else std::cout<<"Invalid Input\n";
                        break;
                    default:
                        std::cout<<"Invalid Input\n";
                        break;
                }
                if(op==1 || op==4 || (op==2 && checkWeapon && !invalid)) break;
            }
        }
        if(fled) break;
        if(!enemy->isAlive())
            break;
        std::shared_ptr<Entity>ph=player;
        enemy->NormalAttack(ph);
        enemy->ApplyEffects();
        if(!enemy->isAlive())
            break;
        player->ApplyEffects();
    }
    if(fled) std::cout<<"You Fled The Battlefield.\n";
    if(player->isAlive() && !fled)
    {
        std::cout<<"You Win!\n";
        std::cout<<"You received 50 Coins\n";
        player->GainCurrency(50);
    }
    else std::cout<<"You Lose!\n";
}
void Game::Shop()
{
    std::cout<<"Welcome to the Shop\n";
    while(true)
    {
        player->ShowCurrencyAmount();
        std::cout<<"What will you buy?\n";
        std::cout<<"1.Dagger (Price: 100)\n";
        std::cout<<"2.Spear (Price: 175)\n";
        std::cout<<"3.Sword (Price: 250)\n";
        std::cout<<"4.Longsword (Price: 350)\n";
        std::cout<<"5.Mace (Price: 425)\n";
        std::cout<<"6.Leave\n";
        int op;
        std::cin>>op;
        int currencyCheck;
        switch(op)
        {
            case 1:
            {
                currencyCheck = player->SpendCurrency(100);
                if (currencyCheck == -1) {
                    std::cout << "You don't have enough money to buy this.\n";
                    break;
                }
                Weapon w{"Dagger", 100, 100};
                player->WeaponChange(w);
                std::cout << "You bought a Dagger\n";
                break;
            }
            case 2:
            {
                currencyCheck = player->SpendCurrency(175);
                if (currencyCheck == -1) {
                    std::cout << "You don't have enough money to buy this.\n";
                    break;
                }
                Weapon w{"Spear", 125, 125};
                player->WeaponChange(w);
                std::cout << "You bought a Spear\n";
                break;
            }
            case 3:
            {
                currencyCheck=player->SpendCurrency(250);
                if(currencyCheck==-1)
                {
                    std::cout<<"You don't have enough money to buy this.\n";
                    break;
                }
                Weapon w("Sword", 100, 150);
                player->WeaponChange(w);
                std::cout<<"You bought a Sword\n";
                break;
            }
            case 4:
            {
                currencyCheck = player->SpendCurrency(350);
                if (currencyCheck == -1) {
                    std::cout << "You don't have enough money to buy this.\n";
                    break;
                }
                Weapon w{"Longsword", 150, 200};
                player->WeaponChange(w);
                std::cout << "You bought a Longsword\n";
                break;
            }
            case 5:
            {
                currencyCheck = player->SpendCurrency(425);
                if (currencyCheck == -1) {
                    std::cout << "You don't have enough money to buy this.\n";
                    break;
                }
                Weapon w{"Mace", 80, 250};
                player->WeaponChange(w);
                std::cout << "You bought a Mace\n";
                break;
            }
            case 6:
                return;
            default:
                std::cout<<"Invalid input\n";
        }
    }
}
void Game::HubArea()
{
    srand(time(nullptr));
    while(true)
    {
        std::cout<<"Where will you go?\n";
        std::cout<<"1.Arena\n";
        std::cout<<"2.Shop\n";
        std::cout<<"3.Leave\n";
        int op;
        std::cin>>op;
        switch(op)
        {
            case 1:
                if(strcmp(typeid(*player).name(),"4Mage")==0) std::static_pointer_cast<Mage>(player)->ResetStats();
                else std::static_pointer_cast<Warrior>(player)->ResetStats();
                Battle();
                break;
            case 2:
                Shop();
                break;
            case 3:
                std::cout<<"Goodbye!\n";
                return;
            default:
                std::cout<<"Invalid Input\n";
                break;
        }
    }
}

