#include <iostream>
using std::cout;

#include <fstream>
using std::fstream;
using std::ifstream;
using std::ofstream;

#include <string>
using std::string;

#include <stdexcept>

#include <cstdlib>
using std::system;

#include <iomanip>
using std::setfill;
using std::setw;
using std::left;
using std::right;

#include <map>
using std::map;

#include <cstdlib>
using std::srand;
using std::rand;

#include <ctime>
using std::time;

#include <regex>
using std::regex;
using std::regex_constants::icase;
using std::regex_search;


// #include "../include/Item.h"

void showFigure(string figureName){
    ifstream inputFile("utils/Items/"+figureName);
    int counter = 0;
    int startInfo;
    if (inputFile.is_open()){
        string line;
        while (getline(inputFile, line))
            counter++;
        
        inputFile.close();
    }else{
        cout << "Erro ao abrir o arquivo para leitura!\n";
    }
    startInfo = (counter / 2) - 1;
    counter = 0;
    inputFile.open("utils/Items/"+figureName);
    if (inputFile.is_open()){
        string line;
        while (getline(inputFile, line)){
            // cout << line << "\n";
            if (counter == 0){

            }
            if (counter == startInfo)
                cout << line << "   ℹ️ | Name: " << "\n";
            else if(counter == startInfo+1)
                cout << line << "   ℹ️ | Owner Name: " << "\n";
            else if(counter == startInfo+2)
                cout << line << "   ℹ️ | Current Location: " << "\n";
            else
                cout << line << "\n";
            counter++;
        }
        inputFile.close();
    }else{
        cout << "Erro ao abrir o arquivo para leitura!\n";
    }
}

#include <iostream>

class MyClass {
public:
    int value;

    MyClass(int v) : value(v) {}
    inline int getValue() const{return value;} ;
    // Outros membros e métodos...
};

#include <iostream>

int main() {
    try {
        // Código que pode lançar uma exceção
        throw std::runtime_error("Exceção ocorreu!");

        // Este código não será executado se uma exceção for lançada
        std::cout << "Este código não será executado." << std::endl;
    } catch (const std::exception& e) {
        // Lidar com a exceção
        std::cerr << "Erro: " << e.what() << std::endl;
    }

    // O programa continua a partir daqui após o bloco try-catch
    std::cout << "O programa continua após o bloco try-catch." << std::endl;

    return 0;
}