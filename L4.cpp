#include <bits/stdc++.h>
using namespace std;
#define nl "\n"
class QNS
{
    private:
        int powerLevel;
        int durability;
        int energyStorage;
        int heatLevel;
    
    public:
        QNS() : powerLevel(1000), durability(500), energyStorage(300), heatLevel(0) {} // Constructor with default parameters.
        QNS(const int& pow, const int& dur, const int &nrg, const int &heat) : powerLevel(min(pow, 5000)), durability(dur), energyStorage(nrg), heatLevel(heat) {} // Default Constructor.
        QNS(const QNS& suit1) : powerLevel(suit1.powerLevel), durability(suit1.durability), energyStorage(suit1.energyStorage), heatLevel(suit1.heatLevel) {} // Copy Constructor.
        void operator+(const QNS& suit1);
        void operator-(const int& x);
        void operator*(const int& x);
        void operator/(const int& x);
        friend istream& operator>>(istream& stream, QNS& suit);
        friend ostream& operator<<(ostream& stream, QNS& suit);
        void boostPower(const int& factor);
        void boostPower(const QNS& suit1);
        bool operator==(const QNS& suit1);
        bool operator<(const QNS& suit1);
        int getPowerLevel(void); // Getters.
        int getDurability(void); // Getters.
        int getEnergyStorage(void); // Getters.
        int getHeatLevel(void); // Getters.
        void setPowerLevel(const int &pow); // Setters.
        void setDurability(const int &dur); // Setters.
        void setEnergyStorage(const int &nrg); // Setters.
        void setHeatLevel(const int &heat); // Setters.
};

queue<QNS> suits; // Maintaining queue to satisfy FCFS criteria.

class Avenger
{
    private:
        string name;
        QNS suit;
        int attackStrength;

    public:
        Avenger() {}
        Avenger(const string& avName, const QNS& avSuit, const int& strength) : name(avName), suit(avSuit), attackStrength(strength) {}
        friend istream& operator>>(istream& stream, Avenger& hero);
        friend ostream& operator<<(ostream& stream, Avenger& hero);
        void Attack(Avenger& enemy);
        void upgradeSuit(void);
        void repair(const int& x); // Reduces heatLevel and increases durability.
        void printStatus(void);
        QNS& getSuit(void); // Returns reference of the suit of Avenger.
        string getName(void);
        int getAttackStrength(void);
};

class Battle
{
    private:
        vector<Avenger> heroes;
        vector<Avenger> enemies;
        vector<string> battleLog;

    public:
        Battle() {}
        void startBattle(void); // Starts the battle and takes commands of which are to be done in the battle.
        void printBattleLog(void);
        int Result(void);
        void addHero(const Avenger& hero); // Adds the passed hero into the heroes vector.
        void addEnemy(const Avenger& enemy); // Adds the passed enemy into the enemies vector.
        Avenger& getAvenger(const string& name);
};

void QNS::operator+(const QNS& suit1)
{
    powerLevel += suit1.energyStorage;
    durability += suit1.durability;
    energyStorage += suit1.powerLevel;
    powerLevel = min(powerLevel, 5000);
}

void QNS::operator-(const int& x)
{
    durability -= x;
    energyStorage += x;
    heatLevel += x;
}

void QNS::operator*(const int& x)
{
    energyStorage += (5 * x);
    heatLevel += x;
    powerLevel = powerLevel + (powerLevel * x / 100);
    powerLevel = min(powerLevel, 5000);
}

void QNS::operator/(const int& x)
{
    durability += x;
    heatLevel -= x;
    heatLevel = max(heatLevel, 0);
}

istream &operator>>(istream &stream, QNS &suit)
{
    int P, D, E, H;
    stream >> P >> D >> E >> H;
    suit = QNS(P, D, E, H);
    return stream;
}

ostream &operator<<(ostream &stream, QNS &suit)
{
    stream << suit.getPowerLevel() << " " << suit.getDurability() << " " << suit.getEnergyStorage() << " " << suit.getHeatLevel();
    return stream;
}

void QNS::boostPower(const int& factor)
{
    (*this)*factor;
}

void QNS::boostPower(const QNS& suit1)
{
    (*this) + suit1;
}

bool QNS::operator==(const QNS& suit1)
{
    return ((powerLevel == suit1.powerLevel) and (durability == suit1.durability)) ;
}

bool QNS::operator<(const QNS& suit1)
{
    return (powerLevel + durability < suit1.powerLevel + suit1.durability);
}

int QNS::getPowerLevel(void)
{
    return powerLevel;
}

int QNS::getDurability(void)
{
    return durability;
}

int QNS::getEnergyStorage(void)
{
    return energyStorage;
}

int QNS::getHeatLevel(void)
{
    return heatLevel;
}

void QNS::setPowerLevel(const int& pow)
{
    powerLevel = pow;
}

void QNS::setDurability(const int& dur)
{
    durability = dur;
}

void QNS::setEnergyStorage(const int& nrg)
{
    energyStorage = nrg;
}

void QNS::setHeatLevel(const int& heat)
{
    heatLevel = heat;
}

istream& operator>>(istream& stream, Avenger& hero)
{
    string name;
    int strength;
    stream >> name >> strength;
    QNS dummy;
    hero = Avenger(name, dummy, strength);
    return stream;
}

ostream& operator<<(ostream& stream, Avenger& hero)
{
    stream << hero.getName() << " " << hero.getSuit();
    return stream;
}

void Avenger::Attack(Avenger& enemy)
{
    enemy.getSuit() - attackStrength;
}

void Avenger::upgradeSuit(void)
{
    if(!suits.empty())
    {
        suit + suits.front();
        suits.pop();
    }
}

void Avenger::repair(const int& x)
{
    suit / x;
}

void Avenger::printStatus(void)
{
    cout << (*this) << nl;
}

QNS& Avenger::getSuit(void)
{
    QNS &dummy = suit;
    return dummy;
}

string Avenger::getName(void)
{
    return name;
}

int Avenger::getAttackStrength(void)
{
    return attackStrength;
}

void Battle::startBattle(void)
{
    string command;
    cin >> command;
    while(command != "End")
    {
        if(command == "Attack")
        {
            string avengerA, avengerB;
            cin >> avengerA >> avengerB;
            if(getAvenger(avengerA).getSuit().getDurability() > 0 and getAvenger(avengerA).getSuit().getHeatLevel() <= 500)
            {
                if(getAvenger(avengerB).getSuit().getDurability() > 0)
                {
                    battleLog.push_back(avengerA + " attacks " + avengerB);
                    getAvenger(avengerA).Attack(getAvenger(avengerB));
                }
                if(getAvenger(avengerB).getSuit().getDurability() <= 0)
                {
                    battleLog.push_back(avengerB + " suit destroyed");

                }
                else if(getAvenger(avengerB).getSuit().getHeatLevel() > 500)
                {
                    battleLog.push_back(avengerB + " suit overheated");
                }
            }
        }
        else if(command == "Repair")
        {
            string avenger;
            int x;
            cin >> avenger >> x;
            getAvenger(avenger).repair(x);
            battleLog.push_back(avenger + " repaired");
        }
        else if(command == "BoostPowerByFactor")
        {
            string avenger;
            int factor;
            cin >> avenger >> factor;
            getAvenger(avenger).getSuit().boostPower(factor);
            battleLog.push_back(avenger + " boosted");
            if(getAvenger(avenger).getSuit().getHeatLevel() > 500)
            {
                battleLog.push_back(avenger + " suit overheated");
            }
        }
        else if(command == "BoostPower")
        {
            string avenger;
            QNS suit;
            cin >> avenger >> suit;
            getAvenger(avenger).getSuit().boostPower(suit);
            battleLog.push_back(avenger + " boosted");
            if (getAvenger(avenger).getSuit().getHeatLevel() > 500)
            {
                battleLog.push_back(avenger + " suit overheated");
            }
        }
        else if(command == "AvengerStatus")
        {
            string avenger;
            cin >> avenger;
            getAvenger(avenger).printStatus();
        }
        else if(command == "Upgrade")
        {
            string avenger;
            cin >> avenger;
            if(!suits.empty())
            {
                battleLog.push_back(avenger + " upgraded");
            }
            else
            {
                battleLog.push_back(avenger + " upgrade Fail");
            }
            getAvenger(avenger).upgradeSuit();
        }
        else if(command == "PrintBattleLog")
        {
            printBattleLog();
        }
        else if(command == "BattleStatus")
        {
            cout << (Result() == 1 ? "heroes are winning" : (Result() == -1 ? "enemies are winning" : "tie")) << nl;
        }
        cin >> command;
    }
}

void Battle::printBattleLog(void)
{
    for(auto state : battleLog)
    {
        cout << state << nl;
    }
}

int Battle::Result(void)
{
    int heroSum = 0, enemySum = 0;
    for(auto hero : heroes)
    {
        if(hero.getSuit().getDurability() > 0)
            heroSum += hero.getSuit().getPowerLevel() + hero.getSuit().getDurability();
    }
    for(auto enemy : enemies)
    {
        if(enemy.getSuit().getDurability() > 0)
            enemySum += enemy.getSuit().getPowerLevel() + enemy.getSuit().getDurability();
    }
    if(heroSum > enemySum)
    {
        return 1;
    }
    if(heroSum < enemySum)
    {
        return -1;
    }
    return 0;
}

void Battle::addHero(const Avenger& hero)
{
    heroes.push_back(hero);
}

void Battle::addEnemy(const Avenger& enemy)
{
    enemies.push_back(enemy);
}

Avenger& Battle::getAvenger(const string& name)
{
    for(auto &hero : heroes)
    {
        if(hero.getName() == name)
        {
            return hero;
        }
    }
    for (auto &enemy : enemies)
    {
        if (enemy.getName() == name)
        {
            return enemy;
        }
    }
    static Avenger dummy;
    return dummy;
}


int main(void)
{
    int k, n, m;
    cin >> k >> n >> m;
    QNS tempSuit;
    while(k--)
    {
        cin >> tempSuit;
        suits.push(tempSuit);
    }
    Avenger hero;
    Battle fight;
    while(n--)
    {
        cin >> hero;
        if(!suits.empty())
        {
            hero.getSuit() = suits.front();
            suits.pop();
            fight.addHero(hero);
        }
        else
        {
            cout << hero.getName() << " is out of fight" << nl;
        }
    }
    Avenger enemy;
    while(m--)
    {
        cin >> enemy;
        if(!suits.empty())
        {
            enemy.getSuit() = suits.front();
            suits.pop();
            fight.addEnemy(enemy);
        }
        else
        {
            cout << enemy.getName() << " is out of fight" << nl;
        }
    }
    string command;
    cin >> command;
    if(command == "BattleBegin")
    {
        fight.startBattle();
    }
    return 0;
}