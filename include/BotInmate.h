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
        const BotInmate & operator=(const BotInmate &);
        bool operator==(const BotInmate &) const;
        bool operator!=(const BotInmate &) const;
        bool operator!() const;
        void showRequest() const;
        bool completeRequest(Item);
    private:
        const static int MAXNUMREQUESTS = ;
        static Request requests[];
        const double REWARDVALUE = 5.0;
        Request request;
        Request drawRequest() const;
};


#endif // BOTINMATE_H