#include <iostream>

class Enemy;
class Weapon;

class Player
{
    std::string Name;//Player Character's Name
    int HP, MaxHP, STR, DEF;//Player Character's Attributes
public:
    Player(const std::string& Name_="", int HP_=100, int MaxHP_=100, int STR_=1, int DEF_=1):Name(Name_), HP(HP_), MaxHP(MaxHP_), STR(STR_), DEF(DEF_){}
    Player(const Player& other):Name(other.Name), HP(other.HP), MaxHP(other.MaxHP), STR(other.STR), DEF(other.DEF){}
    friend std::ostream& operator <<(std::ostream& out, const Player& p)
    {
        out<<p.Name<<"'s stats:\n";
        out<<"HP: "<<p.HP<<"/"<<p.MaxHP<<"\n";
        out<<"Strength: "<<p.STR<<"\n";
        out<<"Defence: "<<p.DEF<<"\n";
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
    void NormalWeaponAttack(Enemy& e, Weapon& weapon);
    void LightWeaponAttack(Enemy& e, Weapon& weapon);
    int NormalAttackStrength()
    {
        return 25+25*STR/10;
    }
    int NormalAttackDefense()
    {
        return 25 * DEF / 10;
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

class Weapon{
    int durability, base_damage;
    //bool isEquipped;
public:
    Weapon(int durability_=100, int base_damage_=150):durability(durability_),base_damage(base_damage_){}
    friend std::ostream& operator <<(std::ostream& out, const Weapon& weapon)
    {
        out<<"Weapon stats:\n";
        out<<"Durability: "<< weapon.durability<<"\\100\n";
        out<<"Base Damage: "<< weapon.base_damage<<"\n";
        return out;
    }
    bool isFunctional()
    {
       return durability>0;
    }
    int AttackDamage()
    {
        return base_damage - (100 - durability) * base_damage / 100;
    }
    void DurabilityDecrease(int x)
    {
        durability=std::max(0,durability-x);
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

void Player::NormalWeaponAttack(Enemy& e, Weapon& weapon)
{
    if(weapon.isFunctional())
    {
        e.HP_Depletion(std::max(0,weapon.AttackDamage()-e.NormalAttackDefense()));
        std::cout<<Name<<" used Weapon Attack\n";
        std::cout<<"It has dealt "<<std::max(0,weapon.AttackDamage()-e.NormalAttackDefense())<<" Damage\n";
        weapon.DurabilityDecrease(5);
    }
    else
    {
        std::cout<<"You can't use a broken weapon";
    }
}

void Player::LightWeaponAttack(Enemy& e, Weapon& weapon)
{
    if(weapon.isFunctional())
    {
        e.HP_Depletion(std::max(0,weapon.AttackDamage()/3*2-e.NormalAttackDefense()));
        std::cout<<Name<<" used Light Weapon Attack\n";
        std::cout<<"It has dealt "<<std::max(0,weapon.AttackDamage()/3*2-e.NormalAttackDefense())<<" Damage\n";
        weapon.DurabilityDecrease(3);
    }
    else
    {
        std::cout<<"You can't use a broken weapon";
    }
}

class Game
{
    Player player;
    Enemy enemy{100, 100, 1, 1};
    Weapon weapon;
public:
    Game()=default;
    Game(const Game& other):player(other.player), enemy(other.enemy), weapon(other.weapon){}
    ~Game(){}
    Game& operator=(const Game& other)
    {
        player=other.player;
        enemy=other.enemy;
        return *this;
    }
    friend std::ostream& operator <<(std::ostream& out, const Game& game)
    {
        out<<game.player;
        out<<game.enemy;
        return out;
    }
    void CharacterCreation()
    {
        std::cout<<"Welcome, Adventurer. Please enter your name.\n";
        std::cin>>player;
        std::cout<<"This is your profile:\n";
        std::cout<<player;
    }
    //Currently just showcasing fighting mechanics
    void Battle()
    {
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
        std::cout<<weapon;
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
                        checkWeapon=weapon.isFunctional();
                        int attackType;
                        std::cout<<"Choose your Attack Type\n";
                        std::cout<<"1.Light Attack\n";
                        std::cout<<"2.Normal Attack\n";
                        std::cin>>attackType;
                        switch(attackType)
                        {
                            case 1:
                                player.LightWeaponAttack(enemy,weapon);
                                break;
                            case 2:
                                player.NormalWeaponAttack(enemy,weapon);
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
        if(player.isAlive() && !fled) std::cout<<"You Win!\n";
        else std::cout<<"You Lose!\n";
    }

};

int main()
{
    Game game;
    game.CharacterCreation();
    game.Battle();
    return 0;
}

