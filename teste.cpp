#include <iostream>
using std::cout;
using std::flush;

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

#include <thread>
using std::this_thread::sleep_for;

#include <chrono>
using std::chrono::milliseconds;

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

#include <thread>
#include <chrono>

void runAnimation(string destination, string origin) {
    const int totalFrames = 5;

    for (int frame = 0; frame < totalFrames; ++frame) {
        cout << destination;

        for (int i = 0; i < totalFrames - frame - 1; ++i) {
            cout << ' ';
        }

        cout << "🏃";

        for (int i = 0; i < frame; ++i) {
            cout << '-';
        }

        cout << origin << flush;
        sleep_for(milliseconds(500));
        cout << '\r';  // Retorna para o início da linha
    }
    cout << "\n";  // Adiciona uma quebra de linha no final
}



#include <iostream>
#include <cmath>

class MyClass {
public:
    int getItemAtIndex(int index) {
        if (index < 0 || index >= items.size()) {
            throw std::out_of_range("Index out of range");
        }
        return items[index];
    }

private:
    std::vector<int> items = {1, 2, 3, 4, 5};
};

#include <cstdlib>
using std::system;



int main() {
    int status;
    status = system("bash teste.bash");
    while (status != 0) {
        status = system("bash teste.bash");
    }
    system("clear");
    cout << "Apos\n";
    return 0;
}