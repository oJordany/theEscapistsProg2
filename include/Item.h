#ifndef ITEM_H
#define ITEM_H

#include <string>
using std::string;

#include <iostream>
using std::ostream;

#include <vector>
using std::vector;

#include "Inmate.h"

#include <climits>  // para usar INT_MAX

class Item{
    friend ostream &operator<<(ostream &, const Item &);
    public:
        Item();
        Item(string, const Inmate&, string="",  int=5);
        Item(const Item&);
        ~Item();
        const Item & operator=(const Item &);
        bool operator==(const Item &) const;
        bool operator!=(const Item &) const;
        bool operator!() const;
        void catchItem(const Inmate&);
        void giveTo(const Inmate&);
        void drop(string);
        void viewInfos() const;
        void setItemName(string);
        void setDurability(int=INT_MAX);
        inline void setCurrentLocation(string location){currentLocation = location;};
        inline string getItemName() const {return itemName;};
        inline int getDurability() const {return durability;};
        inline string currentLocation() const {return currentLocation;};
    private:
        string itemName;
        int durability;
        string ownerName;
        string currentLocation;
        const static int MAXNUMITEMTYPES = 18;
        const static *ITEMTYPESPTR[MAXNUMITEMTYPES];
        string drawItem() const;
}

#endif //ITEM_H