#include <iostream>

class Enemy;

class Player
{
    std::string Name;//Player Character's Name
    int HP, MaxHP, STR, DEF;//Player Character's Attributes
public:
    Player(const std::string _Name="", int _HP=100, int _MaxHP=100, int _STR=1, int _DEF=1):Name(_Name), HP(_HP), MaxHP(_MaxHP), STR(_STR), DEF(_DEF){}
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
        HP-=x;
    }
    bool isAlive()
    {
        return HP>0;
    }
    void NormalAttack(Enemy& e);
    int NormalAttackStrength()
    {
        return 25+25*STR/10;
    }
    int NormalAttackDefense()
    {
        return 25*DEF/10;
    }
};

class Enemy
{
    int HP, MaxHP, STR, DEF;//Enemy's basic attributes
public:
    Enemy(int _HP=0, int _MaxHP=0, int _STR=0, int _DEF=0):HP(_HP), MaxHP(_MaxHP), STR(_STR), DEF(_DEF){}
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
        HP-=x;
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

class Game
{
    Player p;
    Enemy e{100, 100, 1, 1};
public:
    Game()=default;
    void CharacterCreation()
    {
        std::cout<<"Welcome, Adventurer. Please enter your name.\n";
        std::cin>>p;
        std::cout<<"This is your profile:\n";
        std::cout<<p;
    }
    void Battle()
    {
        bool fled=false;
        while(p.isAlive() && e.isAlive())
        {
            while(true)
            {
                std::cout<<"Please choose an action:\n";
                std::cout<<"1.Attack\n";
                std::cout<<"2.Flee\n";
                int op;
                std::cin>>op;
                switch(op)
                {
                    case 1:
                        p.NormalAttack(e);
                        break;
                    case 2:
                        fled=true;
                        break;
                    default:
                        std::cout<<"Invalid Input\n";
                        break;
                }
                if(op==1 || op==2) break;
            }
            if(fled) break;
            if(!e.isAlive())
                break;
            e.NormalAttack(p);
        }
        if(fled) std::cout<<"You Fled The Battlefield.\n";
        if(p.isAlive() && !fled) std::cout<<"You Win!\n";
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

