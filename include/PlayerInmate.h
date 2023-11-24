#ifndef PLAYERINMATE_H
#define PLAYERINMATE_H

#include "Inmate.h"

#include <string>
using std::string

#include <iostream>
using std::ostream;
using std::out;

#include "Item.h"
#include "BotInmate.h"

class PlayerInmate: public Inmate
{
    friend ostream &operator<<(ostream &, const PlayerInmate &);
    public:
        PlayerInmate();
        PlayerInmate(string, 
                    int = 100, 
                    int = 100, 
                    int = 40, 
                    int = 40, 
                    int = 40, 
                    double = 0.0);
        PlayerInmate(const PlayerInmate&);
        ~PlayerInmate();
        const PlayerInmate & operator=(const PlayerInmate &);
        bool operator==(const PlayerInmate &) const;
        bool operator!=(const PlayerInmate &) const;
        bool operator!() const;
        void refreshStoredItemsLocations();
        void refreshStoredItemsLocations();
        void addItem(const Item&);
        const Item& dropItem(int);
        void showInventory();
        const Item& giveItemTo(const BotInmate&);
        void 
        void showAcceptedRequests() const;
    private:
        int totalItems;
        Item outfit;
        const static MAXNUMITEMS = 6;
        Item storedItems[MAXNUMITEMS];
        vector <*BotInmate> acceptedRequests;
}

#endif //PLAYERINMATE_H