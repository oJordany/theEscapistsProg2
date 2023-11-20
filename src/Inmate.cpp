#include <iostream>
using std::ostream;
using std::cout;

#include <iomanip>
#include "Inmate.h"

using std::setw;
using std::left;
using std::right;
using std::fixed;
using std::setprecision;

#define RESET   "\033[0m"
#define BLACK   "\033[30m"
#define RED     "\033[31m"      
#define GREEN   "\033[32m"      
#define YELLOW  "\033[33m"      
#define BLUE    "\033[34m"      
#define MAGENTA "\033[35m"      
#define CYAN    "\033[36m"      
#define WHITE   "\033[37m" 

int Inmate::nextId = 1;
map <int, string> Inmate::inmateMap;

Inmate::Inmate()
:name("Player"), health(100), energy(100), strength(40), speed(40), intelligence(40), money(0), currentLocation(""){
    Inmate::inmateMap[nextId++] = name;
}

Inmate::Inmate( string name,
                int health,
                int energy,
                int strength,
                int speed,
                int intelligence ,
                double money){
    setName(name);
    setHealth(health);
    setEnergy(energy);
    setStrength(strength);
    setSpeed(speed);
    setIntelligence(intelligence);
    setMoney(money);
    currentLocation = "";
    Inmate::inmateMap[nextId++] = this->name;
}

Inmate::Inmate( const Inmate& other )
:MAXSIZENAME(10){
    this->name = other.name;
    this->health = other.health;
    this->energy = other.energy;
    this->strength = other.strength;
    this->speed = other.speed;
    this->intelligence = other.intelligence;
    this->money = other.money;
    Inmate::inmateMap[nextId++] = this->name;
    this->currentLocation = other.currentLocation;
}

void Inmate::showPercentageBar(int percentage) const{
    cout << "|";
    const int barWidth = 30;
    int barFill = (percentage * barWidth) / 100;
    for (int i = 0; i < barWidth; ++i) {
        if (i < barFill){
            if (percentage >= 0 && percentage <= 40)
                cout << RED << "■" << RESET;
            else if (percentage > 40 && percentage <= 80)
                cout << YELLOW << "■" << RESET;
            else
                cout << GREEN << "■" << RESET;

        }else
            cout << " ";
    }
    cout << "| " << right << setw(3) << percentage << "%\n";
}

void Inmate::repeatCharacter(string character, int amount) const{
    for (int i = 0; i < amount; i++){
        cout << character;
    }
}

string Inmate::getName() const{
    return this->name;
}

int Inmate::getHealth() const{
    return this->health;
}

int Inmate::getEnergy() const{
    return this->energy;
}

int Inmate::getStrength() const{
    return this->strength;
}

int Inmate::getSpeed() const{
    return this->speed;
}

int Inmate::getIntelligence() const{
    return this->intelligence;
}

double Inmate::getMoney() const{
    return this->money;
}

void Inmate::setName(string name){
    if (name.length() > MAXSIZENAME){
        this->name = name.substr(0, MAXSIZENAME);
        return;
    }
    if (name != "") {
        this->name = name;
        return;
    }
    this->name = "Player";
}

void Inmate::setHealth(int health){
    if (health >= 0 && health <= 100){
        this->health = health;
        return;
    }else if (health > 100){
        this->health = 100;
        return;
    }

    this->health = 0;
}

void Inmate::setEnergy(int energy){
    if (energy >= 0 && energy <= 100){
        this->energy = energy;
        return;
    }else if (energy > 100){
        this->energy = 100;
        return;
    }

    this->energy = 0;
}

void Inmate::setStrength(int strength){
    if (strength >= 0 && strength <= 100){
        this->strength = strength;
        return;
    }else if (strength > 100){
        this->strength = 100;
        return;
    }

    this->strength = 0;
}

void Inmate::setSpeed(int speed){
    if (speed >= 0 && speed <= 100){
        this->speed = speed;
        return;
    } else if (speed > 100){
        this->speed = 100;
        return;
    }

    this->speed = 0;
}

void Inmate::setIntelligence(int intelligence){
    if (intelligence >= 0 && intelligence <= 100){
        this->intelligence = intelligence;
        return;
    } else if (intelligence > 100){
        this->intelligence = 100;
        return;
    }

    this->intelligence = 0;
}

void Inmate::setMoney(double money){
    if (money >= 0){
        this->money = money;
    }
}

void Inmate::viewProfile() const{
    repeatCharacter("-", 57);
    cout << "\n";
    cout << "    ⢀⡀      |\n";
    cout << BLACK << " ⣠⣶⣿⣿⣿⣿⣷⣄⠀  " << RESET << "| " << CYAN << left << setw(11) << "👤 | NAME: " << RESET << right << setw(32) << this->name << "\n";
    cout << "⢰⣿⣿⣿⣿⣿⣿⣿⣿⣆  |\n";
    cout << BLACK << "⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿  " << RESET << "|";
    repeatCharacter("-", 44);
    cout << "\n";
    cout << "⣠⣴⣶⣦⣤⣤⣴⣶⣦⣄  |\n"; 
    cout << "⢿⣧⣤⣼⣿⣿⣧⣤⣼⡿  | " GREEN << left << setw(11) << "💲 | MONEY: " << RESET << right << setw(31) << fixed << setprecision(2) << this->money << "\n";
    cout << "⠀⠀⠉⠁⠀⠀⠈⠉    |\n";
    repeatCharacter("-", 57);
    cout << "\n";
    cout << RED << left << setw(22) << "💓 | Health: " << RESET;
    showPercentageBar(this->health);
    cout << GREEN << left << setw(22) << "🔋 | Energy: " << RESET;
    showPercentageBar(this->energy);
    cout << YELLOW << left << setw(22) << "💪 | Strength: " << RESET;
    showPercentageBar(this->strength);
    cout << BLACK << left << setw(22) << "💨 | Speed: " << RESET;
    showPercentageBar(this->speed);
    cout << MAGENTA << left << setw(22) << "🧠 | Intelligence: " << RESET;
    showPercentageBar(this->intelligence);
    cout << "\n";
}

void Inmate::readBook(int additionalIntelligence){
    if (this->energy >= 5){
        int newIntelligence = this->intelligence + additionalIntelligence;
        int newEnergy = this->energy - 5;
        setEnergy(newEnergy);
        setIntelligence(newIntelligence);
    }
}

json Inmate::toJson() const{
    json inmateJson;

    inmateJson["name"] = name;
    inmateJson["health"] = health;
    inmateJson["energy"] = energy;
    inmateJson["strength"] = strength;
    inmateJson["speed"] = speed;
    inmateJson["intelligence"] = intelligence;
    inmateJson["money"] = money;

    return inmateJson;
}

ostream &operator<<(ostream &out, const Inmate &inmate){
    out << "Name: " << inmate.getName() << "\n";
    out << "Health: " << inmate.getHealth() << "\n";
    out << "Energy: " << inmate.getEnergy() << "\n";
    out << "Strength: " << inmate.getStrength() << "\n";
    out << "Speed: " << inmate.getSpeed() << "\n";
    out << "Intelligence: " << inmate.getIntelligence() << "\n";
    out << "Money: " << inmate.getIntelligence() << "\n";
    out << "Current Location: " << inmate.currentLocation << "\n";

    return out;
}

const Inmate & Inmate::operator=(const Inmate &inmateOnTheRight){
    if (this != &inmateOnTheRight){
        this->name = inmateOnTheRight.name;
        this->health = inmateOnTheRight.health;
        this->energy = inmateOnTheRight.energy;
        this->strength = inmateOnTheRight.strength;
        this->speed = inmateOnTheRight.speed;
        this->intelligence = inmateOnTheRight.intelligence;
        this->money = inmateOnTheRight.money;
        this->currentLocation = inmateOnTheRight.currentLocation;
    }

    return *this;
}

bool Inmate::operator==(const Inmate &inmateOnTheRight) const{
    if (this->MAXSIZENAME != inmateOnTheRight.MAXSIZENAME){
        return false;
    }
    if (this->name != inmateOnTheRight.name){
        return false;
    }
    if (this->health != inmateOnTheRight.health){
        return false;
    }
    if (this->energy != inmateOnTheRight.energy){
        return false;
    }
    if (this->strength != inmateOnTheRight.strength){
        return false;
    }
    if (this->speed != inmateOnTheRight.speed){
        return false;
    }
    if (this->intelligence != inmateOnTheRight.intelligence){
        return false;
    }
    if (this->money != inmateOnTheRight.money){
        return false;
    }

    return true; 
}

bool Inmate::operator!=(const Inmate &inmateOnTheRight) const{
    return ! (*this == inmateOnTheRight);
}

bool Inmate::operator!() const{
    return this->energy < 5;
}

string Inmate::getInmateNameByID(int id){
    if (id > 0 && id <= Inmate::nextId)
        return Inmate::inmateMap[id];
    return "";
}

void Inmate::viewAllInmates(){
    cout << "ID" << "\t" << "INMATE NAME" << "\n";
    for (auto pair : Inmate::inmateMap){
        cout << pair.first << "\t" << pair.second << "\n";
    }
    cout << "\n";
}

Inmate::~Inmate(){
    //..
}