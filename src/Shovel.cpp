#include "Shovel.h"

#include <iostream>
using std::cout;

const map<string, int> Shovel::TYPES_MAP = {
    {"Sturdy Shovel", 10},
    {"Lightweight Shovel", 20},
    {"Flimsy Shovel", 25}
};

Shovel::Shovel() : ScapeTool("Shovel", "", "", 100) {
    // Sorteia um tipo de pá aleatoriamente
    auto it = TYPES_MAP.begin();
    advance(it, rand() % TYPES_MAP.size());
    type = it->first;
}

Shovel::Shovel(string itemName, string ownerName, string currentLocation, string shovelType, int durability)
    : ScapeTool(itemName, ownerName, currentLocation, durability) {
        if (TYPES_MAP.find(shovelType) != TYPES_MAP.end()){
            this->type = shovelType;
        }else {
            // Sorteia um tipo de pá aleatoriamente
            auto it = TYPES_MAP.begin();
            advance(it, rand() % TYPES_MAP.size());
            type = it->first;
        }
}


Shovel::Shovel(const Shovel& other) : ScapeTool(static_cast<ScapeTool>(other)), type(other.type) {}


void Shovel::viewShovelInfos() const {
    std::cout << "Shovel Type: " << TYPES_MAP.at(TYPES_MAP.find(static_cast<int>(type)) << "\n";
    std::cout << "Durability: " << getDurability() << "\n";
}

void Shovel::dig() {
    // Reduz a durabilidade de acordo com o tipo de pá
    setDurability(getDurability() - TYPES_MAP.at(TYPES_MAP.find(type)->first));
}

Shovel::~Shovel() {}