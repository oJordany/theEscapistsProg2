#include "ScapeTool.h"

#include <iostream>
using std::cout;

#include <fstream>
using std::ifstream;
using std::ofstream;

ScapeTool::ScapeTool() : Item("shovel"), durability(100), scapeLocation("") {}

ScapeTool::ScapeTool(string itemName, string ownerName, string currentLocation, int durability)
    : Item(itemName, ownerName, currentLocation), scapeLocation(""){
    setDurability(durability);
}

ScapeTool::ScapeTool(string itemName, const Inmate& ownerName, string currentLocation, int durability)
    : Item(itemName, ownerName, currentLocation), scapeLocation(""){
    setDurability(durability);
}

ScapeTool::ScapeTool(const ScapeTool& other) 
    : Item(static_cast<Item>(other)), durability(other.durability), scapeLocation(other.scapeLocation){

}


void ScapeTool::setDurability(int newDurability) {
    if (newDurability >= 0 && newDurability <= MAX_DURABILITY) {
        durability = newDurability;
    } else {
        // Tratar valores inválidos, como definir para 0 se for negativo ou 100 se for maior que 100
        durability = (newDurability < 0) ? 0 : MAX_DURABILITY;
    }
}


void ScapeTool::viewScapeToolInfos() const{
    ifstream inputFile("../utils/Items/"+this->getItemName()+".txt");
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
    startInfo = (counter / 2) - 3;
    counter = 0;
    inputFile.open("../utils/Items/"+this->getItemName()+".txt");
    if (inputFile.is_open()){
        string line;
        while (getline(inputFile, line)){
            if (counter == startInfo)
                cout << line << "    🏷️  | Name: " << this->getItemName() << "\n";
            else if(counter == startInfo+1)
                cout << line << "    👤 | Owner Name: " << ((this->getOwnerName() == "") ? "null" : this->getOwnerName()) << "\n";
            else if(counter == startInfo+2)
                cout << line << "    📍 | Current Location: " << ((this->getCurrentLocation() == "") ? "null" : this->getCurrentLocation()) << "\n";
            else if(counter == startInfo+3)
                cout << line << "    🔋 | Durability: " << durability << "\n";
            else if(counter == startInfo+4)
                cout << line << "    📍 | Scape Location: " << scapeLocation << "\n";
            else
                cout << line << "\n";
            counter++;
        }
        inputFile.close();
    }else{
        cout << "Erro ao abrir o arquivo para leitura!\n";
    }
}

ostream &operator<<(ostream &out, const ScapeTool &scapeTool) {
    out << static_cast<const Item&>(scapeTool);

    out << "durability: " << scapeTool.getDurability() << "\n";
    out << "scapeLocation: " << ((scapeTool.getScapeLocation() == "") ? "null" : scapeTool.getScapeLocation()) << "\n";

    return out;
}

const ScapeTool& ScapeTool::operator=(const ScapeTool &scapeToolOnTheRight) {
    static_cast<Item>(*this) = static_cast<Item>(scapeToolOnTheRight);

    this->durability = scapeToolOnTheRight.durability;
    this->scapeLocation = scapeToolOnTheRight.scapeLocation;

    return *this;
}

bool ScapeTool::operator==(const ScapeTool &scapeToolOnTheRight) const {
    if (!(static_cast<Item>(*this) == static_cast<Item>(scapeToolOnTheRight)))
        return false;

    return (this->durability == scapeToolOnTheRight.durability && this->scapeLocation == scapeToolOnTheRight.scapeLocation);
}

bool ScapeTool::operator!=(const ScapeTool &scapeToolOnTheRight) const {
    return !(*this == scapeToolOnTheRight);
}

bool ScapeTool::operator!() const {
    return !static_cast<Item>(*this);
}

ScapeTool::~ScapeTool() {}