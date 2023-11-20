#ifndef ITEM_H
#define ITEM_H

#include <string>
using std::string;

#include <iostream>
using std::ostream;

#include <vector>
using std::vector;

#include 

class Item{
    friend ostream &operator<<(ostream &, const Item &);
    public:
        Item();
        Item(string, string, int);
        Item(const Item&);
        ~Item();
        const Item & operator=(const Item &);
        bool operator==(const Item &) const;
        bool operator!=(const Item &) const;
        bool operator!() const;
        void catchItem(string currentLocation);
        void dropItem(string nameItem, string currentLocation);
    private:
        string itemName;
        int durability;
        string currentLocation;
        const static int MAXNUMITEMS = 20;
        const static int MAXNUMITEMTYPES = 18;
        const static *ITEMTYPESPTR[MAXNUMITEMTYPES] = {"Shovel", "Brass Knuckles", "Key",
                                                    "Correspondence Letter", "Fabric", "Sheet Metal",
                                                    "Book", "Guard Clothing", "Prisoner Clothes", "Hoe",
                                                    "Mop", "Knife", "Master Key", 
                                                    "Pliers", "Tool Handle"};
        static int itemsNumber;
        string drawItem() const;
}

#endif //ITEM_H