#ifndef PLAYERINMATE_H
#define PLAYERINMATE_H

#include "Inmate.h"

#include <string>
using std::string;

#include <iostream>
using std::ostream;
using std::cout;

#include <vector>
using std::vector;

#include "Inmate.h"
#include "Item.h"
#include "BotInmate.h"
#include "Time.h"

#include <nlohmann/json.hpp>
using json = nlohmann::json;

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
        json toFullJson() const;
        const PlayerInmate & operator=(const PlayerInmate &);
        bool operator==(const PlayerInmate &) const;
        bool operator!=(const PlayerInmate &) const;
        bool operator!() const;
        void refreshStoredItemsLocations();
        void refreshOutfitLocation();
        void addItem(const Item&);
        void sleep();
        void acceptRequest(const BotInmate&);
        inline void setOutfit(const Item &newOutfit){outfit = newOutfit;};
        Item dropItem(int);
        // const Weapon& dropWeapon(int);
        // const Shovel& dropShovel(int);
        // const Key& dropKey(int);
        void showInventory() const;
        Item giveItemTo(int itemID, const BotInmate&); // Toda vez que for dar um item, verificar se ele mata uma request
        void showAcceptedRequests() const;
        inline int getStoredItemsSize() const {return storedItems.size();};
        inline int getMAXNUMITEMS() const {return MAXNUMITEMS;};
    private:
        Item outfit;
        const static int MAXNUMITEMS = 3;
        // const static int MAXNUMWEAPONS = 3;
        // const static int MAXNUMSHOVELS = 3;
        // const static int MAXNUMKEYS = 3;
        vector <Item*> storedItems;
        // vector <*Weapons> storedWeapons;
        // vector <*Shovel> storedShovels;
        // vector <*Key> storedKeys;
        vector <BotInmate*> acceptedRequests;
};

#endif //PLAYERINMATE_H