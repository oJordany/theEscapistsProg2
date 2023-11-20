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

itemsNumber = 0;
const string Item::ITEMTYPESPTR[MAXNUMITEMTYPES] = {"Shovel", "Brass Knuckles", "Key",
                                                    "Correspondence Letter", "Fabric", "Sheet Metal",
                                                    "Book", "Guard Clothing", "Prisoner Clothes", "Hoe",
                                                    "Mop", "Knife", "Master Key", 
                                                    "Pliers", "Tool Handle"};

Item::Item(){
    itemName = drawItem();
    durability = 5;
    currentLocation = "";
    itemsNumber++;
}

Item::Item(string item, const Inmate &owner, string locationName, int durability)
:currentLocation(locationName), ownerName(owner.getName()){
    setItemName(item);
    setDurability(durability);
    itemsNumber++
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

string Item::drawItem() const{
    srand(time(0));

    int randomIndex = rand() % MAXNUMITEMTYPES;

    return ITEMTYPESPTR[randomIndex];
}