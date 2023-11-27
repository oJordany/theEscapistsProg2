#include "ScapeTool.h"

ScapeTool::ScapeTool() : Item(), durability(100) {}

ScapeTool::ScapeTool(string itemName, string ownerName, string currentLocation, int durability)
    : Item(itemName, ownerName, currentLocation), durability(durability) {
    setDurability(durability);
}

ScapeTool::ScapeTool(string itemName, const Inmate& ownerName, string currentLocation, int durability)
    : Item(itemName, ownerName, currentLocation), durability(durability) {
    setDurability(durability);
}

ScapeTool::ScapeTool(string itemName, string ownerName, string currentLocation, int durability)
    : Item(itemName, ownerName, currentLocation), durability(durability) {
    setDurability(durability);
}

ScapeTool::ScapeTool(const ScapeTool& other) : Item(other), durability(other.durability) {}


void ScapeTool::setDurability(int newDurability) {
    if (newDurability >= 0 && newDurability <= MAX_DURABILITY) {
        durability = newDurability;
    } else {
        // Tratar valores inválidos, como definir para 0 se for negativo ou 100 se for maior que 100
        durability = (newDurability < 0) ? 0 : MAX_DURABILITY;
    }
}

int ScapeTool::getDurability() const {
    return durability;
}

void Item::viewScapeToolInfos() const{
    ifstream inputFile("../utils/Items/"+itemName+".txt");
    int counter = 0;
    int startInfo;
    int widthItemImg = 30;
    if (inputFile.is_open()){
        string line;
        while (getline(inputFile, line))
            counter++;
        
        inputFile.close();
    }else{
        cout << "Erro ao abrir o arquivo para leitura!\n";
    }
    startInfo = (counter / 2) - 2;
    counter = 0;
    inputFile.open("../utils/Items/"+itemName+".txt");
    if (inputFile.is_open()){
        string line;
        while (getline(inputFile, line)){
            if (counter == startInfo)
                cout << line << "    🏷️  | Name: " << itemName << "\n";
            else if(counter == startInfo+1)
                cout << line << "    👤 | Owner Name: " << ((ownerName == "") ? "null" : ownerName) << "\n";
            else if(counter == startInfo+2)
                cout << line << "    📍 | Current Location: " << ((currentLocation == "") ? "null" : currentLocation) << "\n";
            else if(counter == startInfo+3)
                cout << line << "    🔋 | Durability: " << durability << "\n";
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

    return out;
}

const ScapeTool& ScapeTool::operator=(const ScapeTool &scapeToolOnTheRight) {
    static_cast<Item>(*this) = static_cast<Item>(scapeToolOnTheRight);

    this->durability = scapeToolOnTheRight.durability;

    return *this;
}

bool ScapeTool::operator==(const ScapeTool &scapeToolOnTheRight) const {
    if (!(static_cast<Item>(*this) == static_cast<Item>(scapeToolOnTheRight)))
        return false;

    return this->durability == scapeToolOnTheRight.durability;
}

bool ScapeTool::operator!=(const ScapeTool &scapeToolOnTheRight) const {
    return !(*this == scapeToolOnTheRight);
}

bool ScapeTool::operator!() const {
    return !static_cast<Item>(*this);
}

ScapeTool::~ScapeTool() {}