#include <iostream>
using std::cout;

#include "Inmate.h"
// #include "Inmate.cpp"

int main(){

    cout << "Utilizando Inmate definindo seus atributos\n";
    Inmate Prisoner01("Kev", 100, 83, 71, 48, 26, 5.50);
    cout << "Utilizando viewProfile() para visualizar o perfil de Prisoner01:\n";
    Prisoner01.viewProfile();
    cout << "Utilizando setEnergy(15) para alterar a energia do prisioneiro\n";
    Prisoner01.setEnergy(15);
    cout << "Utilizando readBook(30) para aumentar +30 na inteligência\n";
    Prisoner01.readBook(30);
    cout << "Utilizando setMoney(30) para alterar a quantidade de dinheiro\n";
    Prisoner01.setMoney(30);
    cout << "Utilizando viewProfile() para visualizar as alterações nos atributos\n";
    Prisoner01.viewProfile();
    cout << "Utilizando os métodos get para confirmar as alterações nos atributos ↓↓↓\n";
    cout << "getName(): "<< Prisoner01.getName() << "\n";
    cout << "getHealth(): " << Prisoner01.getHealth() << "\n";
    cout << "getEnergy(): "<< Prisoner01.getEnergy() << "\n";
    cout << "getStrength(): "<< Prisoner01.getStrength() << "\n";
    cout << "getSpeed(): "<< Prisoner01.getSpeed() << "\n";
    cout << "getIntelligence(): "<< Prisoner01.getIntelligence() << "\n";
    cout << "getMoney(): "<< Prisoner01.getMoney() << "\n";
    cout << "\n\n";
    cout << "Utilizando Inmate sem definir seus atributos\n";
    Inmate Prisoner02;
    cout << "Utilizando viewProfile() para visualizar o perfil de Prisoner02:\n";
    Prisoner02.viewProfile();
    cout << "Utilizando setEnergy(-7) para alterar a energia do prisioneiro\n";
    Prisoner02.setEnergy(-7);
    cout << "Utilizando readBook(100) para aumentar +100 na inteligência\n";
    Prisoner02.readBook(100);
    cout << "Utilizando setMoney(30) para alterar a quantidade de dinheiro\n";
    Prisoner02.setMoney(30);
    cout << "Utilizando setMoney(-30) para alterar a quantidade de dinheiro\n";
    Prisoner02.setMoney(-30);
    cout << "Utilizando viewProfile() para visualizar as alterações nos atributos\n";
    Prisoner02.viewProfile();
    cout << "Utilizando os métodos get para confirmar as alterações nos atributos ↓↓↓\n";
    cout << "getName(): "<< Prisoner02.getName() << "\n";
    cout << "getHealth(): " << Prisoner02.getHealth() << "\n";
    cout << "getEnergy(): "<< Prisoner02.getEnergy() << "\n";
    cout << "getStrength(): "<< Prisoner02.getStrength() << "\n";
    cout << "getSpeed(): "<< Prisoner02.getSpeed() << "\n";
    cout << "getIntelligence(): "<< Prisoner02.getIntelligence() << "\n";
    cout << "getMoney(): "<< Prisoner02.getMoney() << "\n";
}