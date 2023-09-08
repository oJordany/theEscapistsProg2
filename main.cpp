#include <iostream>
using std::cout;

#include "Inmate.h"
#include "Inmate.cpp"

int main(){
    Inmate Prisoner01("Kev");

    Prisoner01.viewProfile();
    cout << "\n";
    Prisoner01.setEnergy(15);
    Prisoner01.readBook(30);
    Prisoner01.viewProfile();
    cout << "getName(): "<< Prisoner01.getName() << "\n";
    cout << "getHealth(): " << Prisoner01.getHealth() << "\n";
    cout << "getEnergy(): "<< Prisoner01.getEnergy() << "\n";
    cout << "getStrength(): "<< Prisoner01.getStrength() << "\n";
    cout << "getSpeed(): "<< Prisoner01.getSpeed() << "\n";
    cout << "getIntelligence(): "<< Prisoner01.getIntelligence() << "\n";
    cout << "getMoney(): "<< Prisoner01.getMoney() << "\n";
}