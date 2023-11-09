#include <iostream>
#include <typeinfo>

#include <fstream>
using std::fstream;
using std::ifstream;
using std::ofstream;

#include "json.hpp"
using json = nlohmann::json;

using std::cout;
using namespace nlohmann::literals;

int main() {
    std::fstream arquivo("nome_do_arquivo.txt", std::ios::in | std::ios::out);

    if (arquivo.is_open()) {
        std::cout << "Arquivo aberto com sucesso!" << std::endl;
        // Agora você pode ler e escrever no arquivo usando o objeto 'arquivo'
    } else {
        std::cout << "Erro ao abrir o arquivo." << std::endl;
        arquivo << "Primeira entrada\n";
    }

    return 0;
}