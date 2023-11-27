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
    private:
        const static int MAXNUMREQUESTS = 11;
        const static Request REQUESTS[MAXNUMREQUESTS];
        const double REWARDVALUE = 5.0;
        Request request;
};


#endif // BOTINMATE_H