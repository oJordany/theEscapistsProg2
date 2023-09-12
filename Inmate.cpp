#include <iostream>
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

Inmate::Inmate()
:name("Player"), health(100), energy(100), strength(40), speed(40), intelligence(40), money(0){

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
    this->money = money < 0 ? this->money : money;
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
    this->name = name;
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

void Inmate::setMoney(int money){
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

Inmate::~Inmate(){
    //...
}