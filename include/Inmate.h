#ifndef INMATE_H
#define INMATE_H

#include <string>
using std::string;

#include <iostream>
using std::cout;
using std::ostream;

#include <map>
using std::map;

#include <nlohmann/json.hpp>
using json = nlohmann::json;

class Inmate
{
    friend ostream &operator<<(ostream &, const Inmate &);

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
    const Inmate & operator=(const Inmate &);   // operador de atribuição
    bool operator==(const Inmate &) const;      // operador de igualdade
    bool operator!=(const Inmate &) const;      // operador de diferença
    bool operator!() const;                     // operador de negação

    json toJson() const;
    string getName() const;
    int getHealth() const;
    int getEnergy() const;
    int getStrength() const;
    int getSpeed() const;
    int getIntelligence() const;
    double getMoney() const;
    inline bool isNull() const { return this == nullptr; }

    void setName(string);
    void setHealth(int);
    void setEnergy(int);
    void setStrength(int);
    void setSpeed(int);
    void setIntelligence(int);
    void setMoney(double);
    static string getInmateNameByID(int);
    static void viewAllInmates();

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
    static map<int, string> inmateMap;
    static int nextId;
};

#endif