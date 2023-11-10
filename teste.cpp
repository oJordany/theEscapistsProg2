#include <iostream>
#include <typeinfo>

#include <fstream>
using std::fstream;
using std::ifstream;
using std::ofstream;

#include "json.hpp"
using json = nlohmann::json;

#include "includes/Prison.h"

using std::cout;
using namespace nlohmann::literals;

int main() {
    Prison *prison;

    prison = new Prison();

    return 0;
}