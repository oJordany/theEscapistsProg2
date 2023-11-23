#include <iostream>
using std::cout;

#include <fstream>
using std::fstream;
using std::ifstream;
using std::ofstream;

#include <stdexcept>

#include <cstdlib>
using std::system;


int main() {
    // Nome do arquivo que você deseja imprimir
    std::string nomeArquivo = "Shovel.txt";

    // Cria um objeto ifstream para ler o arquivo
    std::ifstream arquivo(nomeArquivo);

    // Verifica se o arquivo foi aberto corretamente
    if (!arquivo.is_open()) {
        std::cerr << "Não foi possível abrir o arquivo: " << nomeArquivo << std::endl;
        return 1; // Retorna um código de erro
    }

    // Lê e imprime o conteúdo do arquivo linha por linha
    std::string linha;
    while (std::getline(arquivo, linha)) {
        std::cout << linha << std::endl;
    }

    // Fecha o arquivo
    arquivo.close();

    return 0;
}