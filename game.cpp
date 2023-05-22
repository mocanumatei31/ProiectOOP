#include "game.h"
#include "enemy.h"
#include "warrior.h"
#include "mage.h"
#include "rogue.h"
#include "player.h"
#include "enemy.h"
#include "exceptions.h"
#include "weapon.h"
#include "entity.h"
#include <iostream>
#include <memory>
#include <string>
#include <stdexcept>

Game::Game()=default;
Game::~Game()= default;
Game& Game::get_game()
{
    static Game game;
    return game;
}

void Game::InitializeEnemyList()
{
    enemy_list.push_back(std::make_shared<Enemy>(Enemy_Factory::goblin()));
    enemy_list.push_back(std::make_shared<Enemy>(Enemy_Factory::ninja()));
    enemy_list.push_back(std::make_shared<Enemy>(Enemy_Factory::knight()));
    enemy_list.push_back(std::make_shared<Enemy>(Enemy_Factory::ogre()));
    enemy_list.push_back(std::make_shared<Enemy>(Enemy_Factory::troll()));
}

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
        std::cout<<"3.Rogue\n";
        int op;
        std::string op_;
        std::cin>>op_;
        try
        {
            op=std::stoi(op_);
        }
        catch(std::logic_error&)
        {
            op=-1;
        }
        switch(op)
        {
            case 1:
            {
                player=std::make_shared<Warrior>(Warrior());
                break;
            }
            case 2:
            {
                player=std::make_shared<Mage>(Mage());
                break;
            }
            case 3:
            {
                player=std::make_shared<Rogue>(Rogue());
                break;
            }
            default:
                std::cout<<"Invalid Input\n";
                break;
        }
        if(op==1 || op==2 || op==3) break;
    }
    player->NameCharacter(phname);
    std::cout<<"This is your profile:\n";
    player->ShowStats();
}

void Game::CreateEnemy()
{
    Enemy_Builder enemybuilder;
    std::string Name;
    std::cout<<"Welcome to the Enemy Creation Lab!\n";
    std::cout<<"Please Choose a Name for the Enemy\n";
    std::cin>>Name;
    enemybuilder.Name(Name);
    while(true)
    {
        std::cout<<"Please Choose an Action:\n";
        std::cout<<"1.Show Created Enemy's Current Info\n";
        std::cout<<"2.Change Enemy's Name\n";
        std::cout<<"3.Change Enemy's HP (Default Value: 100)\n";
        std::cout<<"4.Change Enemy's Strength (Default Value: 1)\n";
        std::cout<<"5.Change Enemy's Defence (Default Value: 1)\n";
        std::cout<<"6.Change Enemy's Agility (Default Value: 1)\n";
        std::cout<<"7.Save Created Enemy\n";
        std::cout<<"8.Discard Created Enemy\n";
        std::string op_;
        int op;
        std::cin>>op_;
        try
        {
            op=std::stoi(op_);
            switch(op)
            {
                case 1:
                    enemybuilder.ShowCurrentState();
                    break;
                case 2:
                {
                    std::cout<<"Please Enter the New Name:\n";
                    std::cin>>Name;
                    enemybuilder.Name(Name);
                    break;
                }
                case 3:
                {
                    int HP_;
                    std::string HPstring;
                    std::cout<<"Please Enter the New HP Value:\n";
                    std::cin>>HPstring;
                    HP_=std::stoi(HPstring);
                    enemybuilder.HP(HP_);
                    break;
                }
                case 4:
                {
                    int STR_;
                    std::string STRstring;
                    std::cout<<"Please Enter the New Strength Value:\n";
                    std::cin>>STRstring;
                    STR_=std::stoi(STRstring);
                    if(STR_<0 ||STR_>10) std::cout<<"Strength Can Only Be a Number From 0-10\n";
                    else enemybuilder.STR(STR_);
                    break;
                }
                case 5:
                {
                    int DEF_;
                    std::string DEFstring;
                    std::cout<<"Please Enter the New Defence Value:\n";
                    std::cin>>DEFstring;
                    DEF_=std::stoi(DEFstring);
                    if(DEF_<0 || DEF_>10) std::cout<<"Defence Can Only Be a Number From 0-10\n";
                    else enemybuilder.DEF(DEF_);
                    break;
                }
                case 6:
                {
                    int AGI_;
                    std::string AGIstring;
                    std::cout<<"Please Enter the New Agility Value:\n";
                    std::cin>>AGIstring;
                    AGI_=std::stoi(AGIstring);
                    if(AGI_<0 ||AGI_>10) std::cout<<"Agility Can Only Be a Number From 0-10\n";
                    else enemybuilder.AGI(AGI_);
                    break;
                }
                case 7:
                    enemy_list.push_back(enemybuilder.build());
                    std::cout<<"Enemy Saved.\n";
                    return;
                case 8:
                    return;
                default:
                    std::cout<<"Invalid Input\n";
                    break;
            }
        }
        catch(std::logic_error&)
        {
            std::cout<<"Invalid Input\n";
        }
    }
}

std::shared_ptr<Enemy> Game::EnemySelect()
{
    int length=(int)enemy_list.size();
    if(curr_level<=4) return enemy_list[curr_level];
    else
    {
        while(true)
        {
            std::cout<<"Please Choose an Enemy to Fight\n";
            for(int i=0;i<length;i++)
                std::cout<<i+1<<"."<<enemy_list[i]->get_name()<<"\n";
            std::string op_;
            int op;
            std::cin>>op_;
            try
            {
                op=std::stoi(op_);
            }
            catch(std::logic_error&)
            {
                op=-1;
            }
            if(op<1 || op>length) std::cout<<"Invalid Input\n";
            else return enemy_list[op-1];
        }
    }
}

void Game::Battle()
{
    auto enemy=std::static_pointer_cast<Enemy>(EnemySelect()->clone());
    std::cout<<"This is your opponent:\n";
    std::cout<<*enemy<<"\n";
    while(true)
    {
        std::cout<<"Please choose an action:\n";
        std::cout<<"1.Fight\n";
        std::cout<<"2.Leave\n";
        int op;
        std::string op_;
        std::cin>>op_;
        try
        {
            op=std::stoi(op_);
        }
        catch(std::logic_error&)
        {
            op=-1;
        }
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
            int spellType = 0, spellPass = 0;
            player->ShowAvailableActions();
            std::string op_;
            int op;
            std::cin >> op_;
            try
            {
                op = std::stoi(op_);
            }
            catch (std::logic_error&)
            {
                op = -1;
            }
            bool checkWeapon = true;
            bool invalid = false;
            switch (op)
            {
                case 1:
                {
                    std::shared_ptr<Entity> ph = enemy;
                    player->NormalAttack(ph);
                    break;
                }
                case 2:
                {
                    int attackType;
                    std::string attackType_;
                    player->ShowAvailableAttacks();
                    std::cin >> attackType_;
                    try
                    {
                        attackType = std::stoi(attackType_);
                        switch (attackType)
                        {
                            case 1:
                            {
                                std::shared_ptr<Entity> ph = enemy;
                                player->LightWeaponAttack(ph);
                                checkWeapon = true;
                                break;
                            }
                            case 2:
                            {
                                std::shared_ptr<Entity> ph = enemy;
                                player->NormalWeaponAttack(ph);
                                checkWeapon = true;
                                break;
                            }
                            case 3:
                            {
                                if (auto warrior = std::dynamic_pointer_cast<Warrior>(player))
                                {
                                    std::shared_ptr<Entity> ph = enemy;
                                    warrior->HeavyWeaponAttack(ph);
                                    checkWeapon = true;
                                }
                                else
                                {
                                    invalid = true;
                                    std::cout << "Invalid Input\n";
                                }
                                break;
                            }
                            default:
                                invalid = true;
                                std::cout << "Invalid Input\n";
                                break;
                        }
                    }
                    catch(std::logic_error&)
                    {
                        std::cout<<"Invalid Input\n";
                        invalid=true;
                    }
                    catch (WeaponError &err)
                    {
                        std::cout << err.what();
                        invalid=true;
                    }
                    break;
                }
                case 3:
                {
                    if (auto mage = std::dynamic_pointer_cast<Mage>(player))
                    {
                        while (true)
                        {
                            std::cout << "Choose what spell to use\n";
                            std::cout << "1.Fireball(Mana Cost: 10)\n";
                            std::cout << "2.Stun(Mana Cost: 15)\n";
                            std::cout << "3.Magic Shield(Mana Cost: 25)\n";
                            std::cout << "4.Heal(Mana Cost: 30)\n";
                            std::cout << "5.Go Back\n";
                            std::string spellType_;
                            std::cin >> spellType_;
                            try
                            {
                                spellType = std::stoi(spellType_);
                            }
                            catch (std::logic_error&)
                            {
                                spellType = -1;
                            }
                            switch (spellType)
                            {
                                case 1:
                                {
                                    std::shared_ptr<Entity> ph = enemy;
                                    spellPass = mage->Fireball(ph);
                                    break;
                                }
                                case 2:
                                {
                                    std::shared_ptr<Entity> ph = enemy;
                                    spellPass = mage->Stun(ph);
                                    break;
                                }
                                case 3:
                                {
                                    spellPass = mage->MagicShield();
                                    break;
                                }
                                case 4:
                                {
                                    spellPass = mage->Heal();
                                    break;
                                }
                                case 5:
                                {
                                    break;
                                }
                                default:
                                    std::cout << "Invalid Input\n";
                                    break;
                            }
                            if (spellType == 5 || (0 < spellType && spellType < 5 && spellPass == 1)) break;
                        }
                    }
                    else std::cout << "Invalid Input\n";
                    break;
                }
                case 4:
                    player->ShowStats();
                    break;
                case 5:
                    fled = true;
                    break;
                case 9:
                    if (auto warrior = dynamic_pointer_cast<Warrior>(player))
                    {
                        if (warrior->isRageFilled())
                        {
                            warrior->activateRage();
                            std::cout << "Rage Mode Activated\n";
                        }
                        else std::cout << "Invalid Input\n";
                    }
                    else std::cout << "Invalid Input\n";
                    break;
                default:
                    std::cout << "Invalid Input\n";
                    break;
            }
            if (op == 1 || op == 5 || (op == 2 && checkWeapon && !invalid) || (op == 3 && spellPass == 1)) break;
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
        std::cout<<"You received "<<100*(curr_level+1)<< " Coins\n";
        player->GainCurrency(100*(curr_level+1));
        if(curr_level<4) curr_level++;
        else if(curr_level==4)
        {
            beatDefaultEnemies=true;
            curr_level++;
        }
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
        std::string op_;
        std::cin>>op_;
        try
        {
            op = std::stoi(op_);
            switch (op)
            {
                case 1:
                {
                    player->SpendCurrency(100);
                    player->WeaponChange(Weapon_Factory::dagger());
                    std::cout << "You bought a Dagger\n";
                    break;
                }
                case 2:
                {
                    player->SpendCurrency(175);
                    player->WeaponChange(Weapon_Factory::spear());
                    std::cout << "You bought a Spear\n";
                    break;
                }
                case 3:
                {
                    player->SpendCurrency(250);
                    player->WeaponChange(Weapon_Factory::sword());
                    std::cout << "You bought a Sword\n";
                    break;
                }
                case 4:
                {
                    player->SpendCurrency(350);
                    player->WeaponChange(Weapon_Factory::longsword());
                    std::cout << "You bought a Longsword\n";
                    break;
                }
                case 5:
                {
                    player->SpendCurrency(425);
                    player->WeaponChange(Weapon_Factory::mace());
                    std::cout << "You bought a Mace\n";
                    break;
                }
                case 6:
                    return;
                default:
                    std::cout << "Invalid input\n";
            }
        }
        catch(std::logic_error&)
        {
            std::cout<<"Invalid Input\n";
        }
        catch (CurrencyError &err)
        {
            std::cout << err.what();
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
        if(beatDefaultEnemies) std::cout<<"3.Enemy Creation Lab\n";
        std::cout<<"4.Leave\n";
        int op;
        std::string op_;
        std::cin>>op_;
        try
        {
            op=std::stoi(op_);
        }
        catch(std::logic_error&)
        {
            op=-1;
        }
        switch(op)
        {
            case 1:
            {
                player->ResetStats();
                Battle();
                break;
            }
            case 2:
                Shop();
                break;
            case 3:
                if(beatDefaultEnemies) CreateEnemy();
                else std::cout<<"Invalid Input\n";
                break;
            case 4:
                std::cout<<"Goodbye!\n";
                return;
            default:
                std::cout<<"Invalid Input\n";
                break;
        }
    }
}

