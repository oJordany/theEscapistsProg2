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

#include "../include/Item.h"

int main() {
    Item teste = Item;

    teste.viewInfos();
    return 0;
}