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
    json storage;

    storage["centerPerks"];

    storage["centerPerks"]["level"] = 2;

    // storage["centerPerks"] = NULL;
    cout << storage.items();
    for (auto s : storage.items()){
        cout << s.value()["level"];
    }

    // std::cout << storage.dump() << std::endl;

    return 0;
}