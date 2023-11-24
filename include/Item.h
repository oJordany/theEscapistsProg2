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
        Item(string, const Inmate&, string="");
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
        inline void setCurrentLocation(string location){currentLocation = location;};
        inline string getItemName() const {return itemName;};
        inline string getCurrentLocation() const {return currentLocation;};
    private:
        string itemName;
        string ownerName;
        string currentLocation;
        const static int MAXNUMITEMTYPES = 24;
        const static string ITEMTYPESPTR[MAXNUMITEMTYPES];
        string drawItem() const;
        void setItemName(string);
        string strip(const string&) const;
        string toLowerCase(string) const;
};

#endif //ITEM_H