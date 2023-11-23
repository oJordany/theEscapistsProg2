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

#include "util.h"

#include <climits>

#define RESET   "\033[0m"
#define BLACK   "\033[30m"
#define RED     "\033[31m"      
#define GREEN   "\033[32m"      
#define YELLOW  "\033[33m"      
#define BLUE    "\033[34m"      
#define MAGENTA "\033[35m"      
#define CYAN    "\033[36m"      
#define WHITE   "\033[37m" 

const string Item::ITEMTYPESPTR[MAXNUMITEMTYPES] = {"shovel", "brass knuckles", "key",
                                                    "correspondence letter", "fabric", "sheet metal",
                                                    "book", "guard outfit", "inmate outfit", "hoe",
                                                    "mop", "knife", "master key", 
                                                    "pliers", "tool handle", "soap", "molten plastic"};

Item::Item(){
    itemName = drawItem();
    durability = INT_MAX;
    currentLocation = "";
}

Item::Item(string item, const Inmate &owner, string locationName, int durability)
:currentLocation(locationName), ownerName(owner.getName()){
    setItemName(item);
    setDurability(durability);
}

Item::Item(const Item &other){
    this->itemName = other.itemName;
    this->durability = other.durability;
    this->ownerName = other.ownerName;
    this->currentLocation = other.currentLocation;
}

void Item::setDurability(int durability){
    if (durability > 0){
        this->durability = durability;
        return;    
    }
    this->durability = INT_MAX;
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
    showFigure("Items/"+itemName);
    cout << "ℹ️ | Name: " << itemName << "\n";
    cout << "ℹ️ | Durability: " << durability << "\n";
    cout << "ℹ️ | Owner Name: " << ownerName << "\n";
    cout << "ℹ️ | Current Location: " << currentLocation << "\n";
}

string Item::drawItem() const{
    srand(time(0));

    int randomIndex = rand() % MAXNUMITEMTYPES;

    while(ITEMTYPESPTR[randomIndex] == "Key")
        randomIndex = rand() % MAXNUMITEMTYPES;

    return ITEMTYPESPTR[randomIndex];
}