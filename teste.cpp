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

#include "CImg.h"

using namespace cimg_library;

int main() {
    // Carrega a imagem
    CImg<unsigned char> image("Cell_Key.jpg");

    // Redimensiona a imagem para um tamanho razoável
    image.resize(100, 100);

    // Converte a imagem para arte ASCII
    const char* ascii_characters = "@%#*+=-:. ";
    const int num_characters = strlen(ascii_characters);

    for (int y = 0; y < image.height(); ++y) {
        for (int x = 0; x < image.width(); ++x) {
            // Calcula o índice de luminosidade
            int index = static_cast<int>((image(x, y, 0) + image(x, y, 1) + image(x, y, 2)) / 3.0 / 256.0 * num_characters);

            // Exibe o caractere correspondente
            std::cout << ascii_characters[index];
        }
        std::cout << std::endl;
    }

    return 0;
}