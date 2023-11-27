#include <iostream>
using std::cout;
using std::ostream;

#include "BotInmate.h"

#include <string>
using std::string;

#include <cmath>
using std::ceil;

#include <vector>
using std::vector;

#include <cstdlib>
using std::srand;
using std::rand;

#include <ctime>
using std::time;

const Request BotInmate::REQUESTS[MAXNUMREQUESTS] = {
                                    {"I need a \033[31mshovel\033[m to dig my way out. Can you find one for me?", "shovel", 0},
                                    {"In a tight spot without protection. Bring me \033[31mbrass knuckles\033[m, quick!", "brass knuckles", 0},
                                    {"Trying to fix something. Bring me a \033[31msheet metal\033[m, please.", "sheet metal", 0},
                                    {"Bored out of my mind. Lend me a \033[31mbook\033[m, would you?", "book", 0},
                                    {"Caught the eye of a guard. Need some camouflage - \033[31mguard clothing\033[m -, anyone?", "guard clothing", 0},
                                    {"Got a bit of gardening to do. Pass me a \033[31mhoe\033[m, will you?", "hoe", 0},
                                    {"Need to scrub down this mess. A \033[31mmop\033[m would be a lifesaver!", "mop", 0},
                                    {"Hungry as ever. How about some \033[31mfood\033[m to keep me going?", "food", 0},
                                    {"Feeling a bit under the weather. Could use a boost - an \033[31menergetic\033[m drink, perhaps?", "energetic", 0},
                                    {"Accidents happen. A \033[31mFirst Aid Kit\033[m could save the day. Can you find one?", "first aid kit", 0},
                                    {"Trying to fix this contraption. I need \033[31mpliers\033[m, and I need them fast!", "pliers", 0}
                                    };

BotInmate::BotInmate()
:Inmate(){
    request = drawRequest();
}

BotInmate::BotInmate(string name,
                    int health,
                    int energy,
                    int strength,
                    int speed,
                    int intelligence ,
                    double money)
:Inmate(name, health, energy, strength, speed, intelligence, money){
    request = drawRequest();
}

BotInmate::BotInmate(const BotInmate &other)
:Inmate(static_cast<Inmate>(other)){
    this->request = other.request;
}

double BotInmate::completeRequest(const Item &item){
    if (item.getItemName() == request.itemName){
        request.status = 1;
        return REWARDVALUE;
    }
    return 0.0;
}

void BotInmate::showRequest() const{
    cout << "\033[34mRequest Description:\033[m " << this->request.description << "\n"; 
    cout << "\033[34mRequest Status:\033[m " << ((this->request.status) ? "\033[32m☑\033[m Completed" : "☐ Pending") << "\n"; 
}

Request BotInmate::drawRequest() const{
    int randomIndex = rand() % MAXNUMREQUESTS;
    return REQUESTS[randomIndex];
}

void BotInmate::setRequest(Request newRequest){
    request.itemName = newRequest.itemName;
    request.description = newRequest.description;
    request.status = newRequest.status;
}

ostream &operator<<(ostream &out, const BotInmate &botInmate){
    out << static_cast<Inmate>(botInmate);
    out << "Request Description: " << botInmate.request.description << "\n"; 
    out << "Requested Item Name: " << botInmate.request.itemName << "\n"; 
    out << "Request Status: " << botInmate.request.status << "\n"; 

    return out;
}

const BotInmate & BotInmate::operator=(const BotInmate &botInmateOnTheRight){
    static_cast<Inmate>(*this) = static_cast<Inmate>(botInmateOnTheRight);
    this->request.description == botInmateOnTheRight.request.description;
    this->request.itemName == botInmateOnTheRight.request.itemName;
    this->request.status == botInmateOnTheRight.request.status;
    return *this;
}

bool BotInmate::operator==(const BotInmate &botInmateOnTheRight) const{
    if (static_cast<Inmate>(*this) != static_cast<Inmate>(botInmateOnTheRight))
        return false;
    if (this->request.description != botInmateOnTheRight.request.description)
        return false;
    if (this->request.itemName != botInmateOnTheRight.request.itemName)
        return false;
    if (this->request.status == botInmateOnTheRight.request.status)
        return false;
    return true;
}

bool BotInmate::operator!=(const BotInmate &botInmateOnTheRight) const{
    return !(*this == botInmateOnTheRight);
}

bool BotInmate::operator!() const{
    return (!static_cast<Inmate>(*this) &&
            !this->request.status);
}

json BotInmate::toFullJson() const{
    json botInmateJson = this->toJson();
    json requestJson;
    requestJson["description"] = request.description;
    requestJson["itemName"] = request.itemName;
    requestJson["status"] = request.status;
    botInmateJson["request"] = requestJson;
    return botInmateJson;
}

BotInmate::~BotInmate(){
    //...
}