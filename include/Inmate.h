#ifndef INMATE_H
#define INMATE_H
#include <string>

using std::string;

class Inmate
{
public:
    Inmate();
    Inmate( string, 
            int = 100, 
            int = 100, 
            int = 40, 
            int = 40, 
            int = 40, 
            double = 0.0);
    Inmate(const Inmate &); 
    ~Inmate();

    string getName() const;
    int getHealth() const;
    int getEnergy() const;
    int getStrength() const;
    int getSpeed() const;
    int getIntelligence() const;
    double getMoney() const;

    void setName(string);
    void setHealth(int);
    void setEnergy(int);
    void setStrength(int);
    void setSpeed(int);
    void setIntelligence(int);
    void setMoney(double);

    void viewProfile() const;
    void readBook(int = 1);

private:
    string name;
    int health; 
    int energy;
    int strength;
    int speed;
    int intelligence;
    double money;
    void showPercentageBar(int) const;
    void repeatCharacter(string, int) const;
    const int MAXSIZENAME = 10;
};

#endif