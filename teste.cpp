#include <iostream>
using std::cout;

#include <fstream>
using std::fstream;
using std::ifstream;
using std::ofstream;

#include <stdexcept>

#include <cstdlib>
using std::system;

#include <map>
using std::map;

int main() {
     std::map<int, std::string> meuMapa;

    // Preencher o mapa com alguns valores de exemplo
    meuMapa[1] = "um";
    meuMapa[2] = "dois";
    meuMapa[3] = "três";
    meuMapa[4] = "quatro";

    cout << meuMapa.end()->first <<  "\n";

    return 0;
}