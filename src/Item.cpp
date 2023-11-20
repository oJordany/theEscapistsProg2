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

Item::Item(){
    itemName = drawItem();
    durability = 5;
    currentLocation = "";
}

Item::Item(string itemName, string durability)

string Item::drawItem() const{
    srand(time(0));

    int randomIndex = rand() % MAXNUMITEMTYPES;

    return ITEMTYPESPTR[randomIndex];
}