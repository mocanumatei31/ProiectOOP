#include "game.h"
#include <iostream>
Game::Game()=default;
Game::Game(const Game& other):player(other.player){}
Game::~Game(){}
Game& Game::operator=(const Game& other)
{
    player=other.player;
    return *this;
}
std::ostream& operator <<(std::ostream& out, const Game& game)
{
    out<<game.player;
    return out;
}
void Game::CharacterCreation()
{
    std::cout<<"Welcome, Adventurer. Please enter your name.\n";
    std::cin>>player;
    std::cout<<"This is your profile:\n";
    std::cout<<player;
}
void Game::Battle()
{
    Enemy enemy{"Enemy", 100, 100, 1, 1, 1};
    std::cout<<"This is your opponent:\n";
    std::cout<<enemy<<"\n";
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
    while(player.isAlive() && enemy.isAlive())
    {
        while(true)
        {
            std::cout<<"Please choose an action:\n";
            std::cout<<"1.Punch\n";
            std::cout<<"2.Use Weapon\n";
            std::cout<<"3.Check Current Stats\n";
            std::cout<<"4.Flee\n";
            std::cin>>op;
            bool checkWeapon=true;
            bool invalid=false;
            switch(op)
            {
                case 1:
                    player.NormalAttack(enemy);
                    break;
                case 2:
                    checkWeapon=player.isWeaponFunctional();
                    int attackType;
                    std::cout<<"Choose your Attack Type\n";
                    std::cout<<"1.Light Attack\n";
                    std::cout<<"2.Normal Attack\n";
                    std::cin>>attackType;
                    switch(attackType)
                    {
                        case 1:
                            player.LightWeaponAttack(enemy);
                            break;
                        case 2:
                            player.NormalWeaponAttack(enemy);
                            break;
                        default:
                            invalid=true;
                            std::cout<<"Invalid Input\n";
                            break;
                    }
                    break;
                case 3:
                    std::cout<<*this;
                    break;
                case 4:
                    fled=true;
                    break;
                default:
                    std::cout<<"Invalid Input\n";
                    break;
            }
            if(op==1 || op==4 || (op==2 && checkWeapon && !invalid) ) break;
        }
        if(fled) break;
        if(!enemy.isAlive())
            break;
        enemy.NormalAttack(player);
    }
    if(fled) std::cout<<"You Fled The Battlefield.\n";
    if(player.isAlive() && !fled)
    {
        std::cout<<"You Win!\n";
        std::cout<<"You received 50 Coins\n";
        player.GainCurrency(50);
    }
    else std::cout<<"You Lose!\n";
}
void Game::Shop()
{
    std::cout<<"Welcome to the Shop\n";
    while(true)
    {
        player.ShowCurrencyAmount();
        std::cout<<"What will you buy?\n";
        std::cout<<"1.Sword (Price: 250)\n";
        std::cout<<"2.Spear (Price: 175)\n";
        std::cout<<"3.Longsword (Price: 350)\n";
        std::cout<<"4.Dagger(Price: 100)\n";
        std::cout<<"5.Leave\n";
        int op;
        std::cin>>op;
        int currencyCheck;
        switch(op)
        {
            case 1:
            {
                currencyCheck=player.SpendCurrency(250);
                if(currencyCheck==-1)
                {
                    std::cout<<"You don't have enough money to buy this.\n";
                    break;
                }
                Weapon w;
                player.WeaponChange(w);
                std::cout<<"You bought a Sword\n";
                break;
            }
            case 2:
            {
                currencyCheck = player.SpendCurrency(175);
                if (currencyCheck == -1) {
                    std::cout << "You don't have enough money to buy this.\n";
                    break;
                }
                Weapon w{"Spear", 125, 125};
                player.WeaponChange(w);
                std::cout << "You bought a Spear\n";
                break;
            }
            case 3:
            {
                currencyCheck = player.SpendCurrency(350);
                if (currencyCheck == -1) {
                    std::cout << "You don't have enough money to buy this.\n";
                    break;
                }
                Weapon w{"Longsword", 150, 200};
                player.WeaponChange(w);
                std::cout << "You bought a Longsword\n";
                break;
            }
            case 4:
            {
                currencyCheck = player.SpendCurrency(100);
                if (currencyCheck == -1) {
                    std::cout << "You don't have enough money to buy this.\n";
                    break;
                }
                Weapon w{"Dagger", 100, 100};
                player.WeaponChange(w);
                std::cout << "You bought a Dagger\n";
                break;
            }
            case 5:
                return;
            default:
                std::cout<<"Invalid input\n";
        }
    }
}
void Game::HubArea()
{
    srand(time(NULL));
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
                player.HP_Fill();
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

