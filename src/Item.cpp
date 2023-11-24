#include "Item.h"

#include "Inmate.h"

#include <iostream>
using std::ostream;
using std::cout;

#include  <string>
using std::string;

#include <cstdlib>
using std::srand;
using std::rand;

#include <ctime>
using std::time;

#include "Inmate.h"

#include <fstream>
using std::ifstream;

#include <iomanip>
using std::setfill;
using std::setw;
using std::left;
using std::right;

#include <vector>
using std::vector;

#include <cstdlib>
using std::system;
// #include <climits>

#define RESET   "\033[0m"
#define BLACK   "\033[30m"
#define RED     "\033[31m"      
#define GREEN   "\033[32m"      
#define YELLOW  "\033[33m"      
#define BLUE    "\033[34m"      
#define MAGENTA "\033[35m"      
#define CYAN    "\033[36m"      
#define WHITE   "\033[37m" 

const string Item::ITEMTYPESPTR[MAXNUMITEMTYPES] = {"shovel", "brass knuckles", "key1", 
                                                    "key2", "key3", "key4", 
                                                    "key5", "plastic key1", "plastic key2",
                                                    "plastic key3", "plastic key4", "plastic key5", 
                                                    "correspondence letter", "fabric", "sheet metal",
                                                    "book", "guard outfit", "inmate outfit", 
                                                    "hoe", "mop", "knife", 
                                                    "soap", "molten plastic", "tool handle", 
                                                    };

Item::Item(){
    itemName = drawItem();
    currentLocation = "";
}

Item::Item(string item, const Inmate &owner, string locationName)
:currentLocation(locationName), ownerName(owner.getName()){
    setItemName(item);
}

Item::Item(const Item &other){
    this->itemName = other.itemName;
    this->ownerName = other.ownerName;
    this->currentLocation = other.currentLocation;
}

void Item::setItemName(string item){
    bool isValidItemType = false;
    for (auto itemType : ITEMTYPESPTR){
        if (toLowerCase(itemType) == toLowerCase(item)){
            isValidItemType = true;
            break;
        }
    }

    if (isValidItemType)
        this->itemName = item;
    else   
        this->itemName = drawItem();
}

string Item::strip(const string& str) const{
    size_t first = str.find_first_not_of(" \t\n\r\f\v");
    size_t last = str.find_last_not_of(" \t\n\r\f\v");

    if (first == string::npos) // Se a string está vazia ou contém apenas espaços em branco
        return "";

    return str.substr(first, (last - first + 1));
}

string Item::toLowerCase(string str) const{
    for (auto &character : str) character = tolower(character);
    return str;
}

void Item::catchItem(const Inmate &inmate){
    if (ownerName.empty()){
        ownerName = inmate.getName();
        currentLocation = inmate.getCurrentLocation();
    }else{
        cout << RED << "This item belongs to " << ownerName << RESET << "\n";
    }
}

void Item::giveTo(const Inmate &inmate){
    ownerName = inmate.getName();
    currentLocation = inmate.getCurrentLocation();
}

void Item::drop(string location){
    currentLocation = location;
    ownerName = "";
}

void Item::viewInfos() const{
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
    startInfo = (counter / 2) - 1;
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
            else
                cout << line << "\n";
            counter++;
        }
        inputFile.close();
    }else{
        cout << "Erro ao abrir o arquivo para leitura!\n";
    }
}

string Item::drawItem() const{
    srand(time(0));

    int randomIndex = rand() % MAXNUMITEMTYPES;

    vector <string> ruffleItems;

    for (int i = 0; i < MAXNUMITEMTYPES; i++){
        if (ITEMTYPESPTR[i] != "shovel" &&
            ITEMTYPESPTR[i] != "brass knuckles" &&
            ITEMTYPESPTR[i] != "key1" &&
            ITEMTYPESPTR[i] != "key2" &&
            ITEMTYPESPTR[i] != "key3" &&
            ITEMTYPESPTR[i] != "key4" &&
            ITEMTYPESPTR[i] != "key5" &&
            ITEMTYPESPTR[i] != "plastic key1" &&
            ITEMTYPESPTR[i] != "plastic key2" &&
            ITEMTYPESPTR[i] != "plastic key3" &&
            ITEMTYPESPTR[i] != "plastic key4" &&
            ITEMTYPESPTR[i] != "plastic key5" &&
            ITEMTYPESPTR[i] != "correspondence letter" &&
            ITEMTYPESPTR[i] != "knife"
            )
            ruffleItems.push_back(ITEMTYPESPTR[i]);
    }  

        randomIndex = rand() % ruffleItems.size();

    return ruffleItems[randomIndex];
}

ostream &operator<<(ostream &out, const Item &item){
    out << "itemName: " << itemName << "\n";
    out << "ownerName: " << ownerName << "\n";
    out << "currentLocation: " << currentLocation << "\n";

    return out;
}

const Item& Item::operator=(const Item &itemOnTheRight){
    this->itemName = itemOnTheRight.itemName;
    this->currentLocation = itemOnTheRight.currentLocation;
    this->ownerName = itemOnTheRight.ownerName;

    return *this;
}

bool Item::operator==(const Item &itemOnTheRight) const{
    if (this->itemName != itemOnTheRight.itemName)
        return false;
    if (this->currentLocation != itemOnTheRight.currentLocation)
        return false;
    if (this->ownerName != itemOnTheRight.ownerName)
        return false;
    
    return true;
}

bool Item::operator!=(const Item &itemOnTheRight) const{
    return !(*this == itemOnTheRight);
}

bool Item::operator!() const{
    return this->ownerName != "";
}

Item::~Item(){
    //...
}