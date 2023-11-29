#ifndef BOTINMATE_H
#define BOTINMATE_H

#include <string>
using std::string;

#include <iostream>
using std::cout;
using std::ostream;

#include <map>
using std::map;

#include <vector>
using std::vector;

#include "Inmate.h"
#include "Item.h"

#include <cstdlib>
using std::rand;

#include <nlohmann/json.hpp>
using json = nlohmann::json;

struct Request {
    string description;
    string itemName;
    bool status;
};

class BotInmate: public Inmate
{
    friend ostream &operator<<(ostream &, const BotInmate &);
    public:
        BotInmate();
        BotInmate(  string, 
                    int = 100, 
                    int = 100, 
                    int = 40, 
                    int = 40, 
                    int = 40, 
                    double = 0.0);
        BotInmate(const BotInmate &); 
        ~BotInmate();
        json toFullJson() const;
        const BotInmate & operator=(const BotInmate &);
        bool operator==(const BotInmate &) const;
        bool operator!=(const BotInmate &) const;
        bool operator!() const;
        void showRequest() const;
        inline Request getRequest() const {return request;}
        double completeRequest(const Item&);
        void setRequest(Request);
        Request drawRequest() const;
        Item sellItemTo(const Inmate&);
        inline void setItemForSale(string itemName){itemForSalePtr = new Item(itemName, this->getName(), this->getCurrentLocation());}
        inline void setItemPrice(double price){itemPrice = price;}
        inline void setRewardValue(double reward){rewardValue = reward;}
        inline void drawItemForSale(){itemForSalePtr = new Item("", this->getName(), this->getCurrentLocation());}
        inline void drawItemPrice(){itemPrice = rand() % 16 + 5;}
        inline void drawRewardValue(){rewardValue = rand() % 6 + 5;}
        inline double getItemPrice() const {return itemPrice;}
        void showItemForSale() const;
        void refreshItemForSaleLocation(){itemForSalePtr->setCurrentLocation(this->getCurrentLocation());}
    private:
        const static int MAXNUMREQUESTS = 11;
        const static Request REQUESTS[MAXNUMREQUESTS];
        double rewardValue;
        double itemPrice;
        Request request;
        Item *itemForSalePtr;
};


#endif // BOTINMATE_H