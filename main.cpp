#include <iostream>

class Enemy;

class Weapon{
    std::string type;
    int condition, base_damage;
    //bool isEquipped;
public:
    Weapon(const std::string& type_="Sword",int condition_=100, int base_damage_=150):type(type_),condition(condition_),base_damage(base_damage_){}
    Weapon(const Weapon& other):type(other.type), condition(other.condition), base_damage(other.base_damage){}
    friend std::ostream& operator <<(std::ostream& out, const Weapon& weapon)
    {
        out<<"Weapon stats:\n";
        out<<"Weapon Type: "<< weapon.type<<'\n';
        out<<"Condition: "<< weapon.condition<<"\\100\n";
        out<<"Base Damage: "<< weapon.base_damage<<"\n";
        return out;
    }
    ~Weapon(){}
    Weapon& operator=(const Weapon& other)
    {
        condition=other.condition;
        base_damage=other.base_damage;
        type=other.type;
        return *this;
    }
    bool isFunctional()
    {
        return condition>0;
    }
    int AttackDamage()
    {
        return base_damage - (100 - condition) * base_damage / 100;
    }
    void ConditionDecrease(int x)
    {
        condition=std::max(0,condition-x);
    }
    //Currently unused
    /**void Equip()
    {
        isEquipped=true;
    }
    void Unequip()
    {
        isEquipped=false;
    }
    bool IsWeaponEquipped()
    {
        return isEquipped;
    }*/
};


class Player
{
    Weapon weapon;//Player Character's Equipped Weapon
    std::string Name;//Player Character's Name
    int HP, MaxHP, STR, DEF;//Player Character's Attributes
    int currency=0;//Player Character's Money
public:
    Player(const std::string& Name_="", int HP_=100, int MaxHP_=100, int STR_=1, int DEF_=1):Name(Name_), HP(HP_), MaxHP(MaxHP_), STR(STR_), DEF(DEF_){}
    Player(const Player& other):weapon(other.weapon), Name(other.Name), HP(other.HP), MaxHP(other.MaxHP), STR(other.STR), DEF(other.DEF){}
    friend std::ostream& operator <<(std::ostream& out, const Player& p)
    {
        out<<p.Name<<"'s stats:\n";
        out<<"HP: "<<p.HP<<"/"<<p.MaxHP<<"\n";
        out<<"Strength: "<<p.STR<<"\n";
        out<<"Defence: "<<p.DEF<<"\n";
        out<<"Your Money: "<<p.currency<<"\n";
        out<<p.weapon;
        return out;
    }
    friend std::istream& operator >>(std::istream& in, Player& p)
    {
        in>>p.Name;
        return in;
    }
    Player& operator=(const Player& other)
    {
        Name=other.Name;
        HP=other.HP;
        MaxHP=other.MaxHP;
        STR=other.STR;
        DEF=other.DEF;
        weapon=other.weapon;
        return *this;
    }
    ~Player(){}
    void HP_Depletion(const int x)
    {
        HP=std::max(0,HP-x);
    }
    bool isAlive()
    {
        return HP>0;
    }
    void NormalAttack(Enemy& e);
    void NormalWeaponAttack(Enemy& e);
    void LightWeaponAttack(Enemy& e);
    int NormalAttackStrength()
    {
        return 25+25*STR/10;
    }
    int NormalAttackDefense()
    {
        return 25 * DEF / 10;
    }
    void HP_Fill()
    {
        HP=MaxHP;
    }
    bool isWeaponFunctional()
    {
        return weapon.isFunctional();
    }
    void WeaponChange(const Weapon &newWeapon)
    {
        weapon=newWeapon;
    }
    void GainCurrency(int x)
    {
        currency+=x;
    }
    //Decreases currency and returns 1 if Player has enough currency to make payment
    //Otherwise returns -1
    int SpendCurrency(int x)
    {
        if(currency-x>=0)
        {
            currency-=x;
            return 1;
        }
        else return -1;
    }
    void ShowCurrencyAmount()
    {
        std::cout<<"Your Money: "<<currency<<"\n";
    }
};

class Enemy
{
    int HP, MaxHP, STR, DEF;//Enemy's basic attributes
public:
    Enemy(int HP_=0, int MaxHP_=0, int STR_=0, int DEF_=0):HP(HP_), MaxHP(MaxHP_), STR(STR_), DEF(DEF_){}
    Enemy(const Enemy& other):HP(other.HP), MaxHP(other.MaxHP), STR(other.STR), DEF(other.DEF){}
    friend std::ostream& operator <<(std::ostream& out, const Enemy& e)
    {
        out<<"Enemy's stats:\n";
        out<<"HP: "<<e.HP<<"/"<<e.MaxHP<<"\n";
        out<<"Strength: "<<e.STR<<"\n";
        out<<"Defence: "<<e.DEF<<"\n";
        return out;
    }
    Enemy& operator=(const Enemy& other)
    {
        HP=other.HP;
        MaxHP=other.MaxHP;
        STR=other.STR;
        DEF=other.DEF;
        return *this;
    }
    bool isAlive()
    {
        return HP>0;
    }
    void HP_Depletion(int x)
    {
        HP=std::max(0,HP-x);
    }
    ~Enemy(){}
    int NormalAttackStrength()
    {
        return 25+25*STR/10;
    }
    int NormalAttackDefense()
    {
        return 25*DEF/10;
    }
    void NormalAttack(Player& p);
};

void Player::NormalAttack(Enemy& e)
{
    e.HP_Depletion(std::max(0,NormalAttackStrength()-e.NormalAttackDefense()));
    std::cout<<Name<<" used Normal Attack\n";
    std::cout<<"It has dealt "<<std::max(0,NormalAttackStrength()-e.NormalAttackDefense())<<" Damage\n";
}

void Enemy::NormalAttack(Player& p)
{
    p.HP_Depletion(std::max(0,NormalAttackStrength()-p.NormalAttackDefense()));
    std::cout<<"Enemy used Normal Attack\n";
    std::cout<<"It has dealt "<<std::max(0,NormalAttackStrength()-p.NormalAttackDefense())<<" Damage\n";
}


void Player::NormalWeaponAttack(Enemy& e)
{
    if(weapon.isFunctional())
    {
        e.HP_Depletion(std::max(0,weapon.AttackDamage()-e.NormalAttackDefense()));
        std::cout<<Name<<" used Weapon Attack\n";
        std::cout<<"It has dealt "<<std::max(0,weapon.AttackDamage()-e.NormalAttackDefense())<<" Damage\n";
        weapon.ConditionDecrease(5);
    }
    else
    {
        std::cout<<"You can't use a broken weapon\n";
    }
}

void Player::LightWeaponAttack(Enemy& e)
{
    if(weapon.isFunctional())
    {
        e.HP_Depletion(std::max(0,weapon.AttackDamage()/3*2-e.NormalAttackDefense()));
        std::cout<<Name<<" used Light Weapon Attack\n";
        std::cout<<"It has dealt "<<std::max(0,weapon.AttackDamage()/3*2-e.NormalAttackDefense())<<" Damage\n";
        weapon.ConditionDecrease(3);
    }
    else
    {
        std::cout<<"You can't use a broken weapon\n";
    }
}

class Game
{
    Player player;
public:
    Game()=default;
    Game(const Game& other):player(other.player){}
    ~Game(){}
    Game& operator=(const Game& other)
    {
        player=other.player;
        return *this;
    }
    friend std::ostream& operator <<(std::ostream& out, const Game& game)
    {
        out<<game.player;
        return out;
    }
    void CharacterCreation()
    {
        std::cout<<"Welcome, Adventurer. Please enter your name.\n";
        std::cin>>player;
        std::cout<<"This is your profile:\n";
        std::cout<<player;
    }
    void Battle()
    {
        Enemy enemy{100, 100, 1, 1};
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
    void Shop()
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
    void HubArea()
    {
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
};

int main()
{
    Game game;
    game.CharacterCreation();
    game.HubArea();
    return 0;
}
