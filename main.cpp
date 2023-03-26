#include <iostream>

class Enemy;

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
    Game(const Game& other):p(other.p), e(other.e){}
    ~Game(){}
    Game& operator=(const Game& other)
    {
        p=other.p;
        e=other.e;
        return *this;
    }
    friend std::ostream& operator <<(std::ostream& out, const Game& game)
    {
        out<<game.p;
        out<<game.e;
        return out;
    }
    void CharacterCreation()
    {
        std::cout<<"Welcome, Adventurer. Please enter your name.\n";
        std::cin>>p;
        std::cout<<"This is your profile:\n";
        std::cout<<p;
    }
    void Battle()
    {
        std::cout<<"This is your opponent:\n";
        std::cout<<e<<"\n";
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
        while(p.isAlive() && e.isAlive())
        {
            while(true)
            {
                std::cout<<"Please choose an action:\n";
                std::cout<<"1.Attack\n";
                std::cout<<"2.Check Current Stats\n";
                std::cout<<"3.Flee\n";
                std::cin>>op;
                switch(op)
                {
                    case 1:
                        p.NormalAttack(e);
                        break;
                    case 2:
                        std::cout<<*this;
                        break;
                    case 3:
                        fled=true;
                        break;
                    default:
                        std::cout<<"Invalid Input\n";
                        break;
                }
                if(op==1 || op==3) break;
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
    Game game2;
    game.CharacterCreation();
    std::cout<<"\n--------------------\n!!Game suspended. Copy constructor, = operator and << operator showcase for game class:\n";
    game2=game;
    std::cout<<game2;
    Game game3(game);
    std::cout<<game3;
    std::cout<<"Showcase over!!\n--------------------\n\n";
    game.Battle();
    return 0;
}

