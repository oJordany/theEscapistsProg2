#include <iostream>
using std::cout;
using std::ostream;
using std::flush;

#include <thread>
using std::this_thread::sleep_for;

#include <chrono>
using std::chrono::milliseconds;

#include <string>
using std::string;

#include <iomanip>
using std::setfill;
using std::setw;

#include <regex>
using std::regex;
using std::regex_constants::icase;
using std::regex_search;

#include <iomanip>
using std::setfill;
using std::setw;
using std::left;
using std::right;

#include <stdexcept>
using std::out_of_range;

#include "PlayerInmate.h"
#include "Inmate.h"
#include "BotInmate.h"
#include "Item.h"

PlayerInmate::PlayerInmate()
:Inmate(), outfit(Item("inmate outfit", Inmate())){
    //...
}

PlayerInmate::PlayerInmate( string name,
                            int health,
                            int energy,
                            int strength,
                            int speed,
                            int intelligence,
                            double money
                            ):  Inmate(name, health, energy, strength, speed, intelligence, money), 
                                outfit(Item("inmate outfit", Inmate(name, health, strength, speed, intelligence, money))){
    //...
}

PlayerInmate::PlayerInmate(const PlayerInmate &other)
:Inmate(static_cast<Inmate>(other)), outfit(Item(other.outfit)){
    for (auto storedItem : other.storedItems){
        this->storedItems.push_back(new Item(*storedItem));
    }
    for (auto acceptedRequest : other.acceptedRequests){
        this->acceptedRequests.push_back(new BotInmate(*acceptedRequest));
    }
}

void PlayerInmate::refreshStoredItemsLocations(){
    for (auto storedItem: storedItems){
        storedItem->setCurrentLocation(this->getCurrentLocation());
    }
}

void PlayerInmate::refreshOutfitLocation(){
    outfit.setCurrentLocation(this->getCurrentLocation());
}

void PlayerInmate::addItem(const Item &item){
    if (storedItems.size() < MAXNUMITEMS){
        storedItems.push_back(new Item(item));
        cout << "\033[32m" << item.getItemName() << " foi pego e adicionado ao inventário!\033[m\n";
    }else{ 
        cout << "🚫 \033[31m\x1b[1;4mWarning! Inventory Full!\x1b[0m\033[m 🚫" << "\n";
        cout << "Please make space before adding more items. 🧳🔒\n";
    }
}

void PlayerInmate::sleep(){
    string room = this->getName() + "'s room";
    regex pattern("Lights out", icase); // 'icase' torna a correspondência sem diferenciação de maiúsculas e minúsculas
    if (this->getCurrentLocation() == room && regex_search(Time::getCurrentRoutineName(), pattern)){
        // Roda a animação dormindo
        int durationInSeconds = 10;
        
        for (int i = 0; i < durationInSeconds; ++i) {
            if (i % 2 == 0) {
                std::cout << "⋆⭒˚｡⋆⋆⭒˚｡⋆⋆⭒˚｡⋆⋆⭒˚｡⋆⋆⭒˚｡⋆⋆⭒˚｡⋆⋆⭒˚｡⋆⋆⭒˚｡⋆  💤🛌  ⋆⭒˚｡⋆⋆⭒˚｡⋆⋆⭒˚｡⋆⋆⭒˚｡⋆⋆⭒˚｡⋆⋆⭒˚｡⋆⋆⭒˚｡⋆⋆⭒˚｡⋆" << flush;
            } else {
                std::cout << "⋆⭒˚｡⋆⋆⭒˚｡⋆⋆⭒˚｡⋆⋆⭒˚｡⋆⋆⭒˚｡⋆⋆⭒˚｡⋆⋆⭒˚｡⋆⋆⭒˚｡⋆    🛌  ⋆⭒˚｡⋆⋆⭒˚｡⋆⋆⭒˚｡⋆⋆⭒˚｡⋆⋆⭒˚｡⋆⋆⭒˚｡⋆⋆⭒˚｡⋆⋆⭒˚｡⋆" << flush;
            }

            sleep_for(milliseconds(1000));
            cout << '\r';  // Retorna para o início da linha
        }
        setEnergy(100);
        Time::skipTime(Time::getRoutineStartHour(1), Time::getRoutineStartMinute(1));
        return;
    }
    cout << "Oops! 😮 You can't sleep yet. It's not bedtime! 🌙⏰\n";
}

void PlayerInmate::acceptRequest(const BotInmate &botInmate){
    if (botInmate.getCurrentLocation() == this->getCurrentLocation())
        acceptedRequests.push_back(new BotInmate(botInmate));
    else    
        cout << "🚫 \033[31m\x1b[1;4mInmate not found!\033[m\x1b[0m 🚫\n";
}

Item PlayerInmate::dropItem(int itemID){
    if (!storedItems.empty() && itemID >= 0 && itemID <= storedItems.size() && itemID < MAXNUMITEMS){
        Item releasedItem(storedItems[itemID]->getItemName(), "", this->getCurrentLocation());
        delete storedItems[itemID];
        storedItems.erase(storedItems.begin() + itemID);
        return releasedItem;
    }

    throw std::out_of_range("🚫 \033[31m\x1b[1;4mInvalid Item ID!\033[m\x1b[0m 🚫 Item not found with ID: " + std::to_string(itemID));
}

void PlayerInmate::showInventory() const{
    int itemID = 0;
    bool isEmpty = true;
    for (auto storedItem : storedItems){
        isEmpty = false;
        cout << setfill('-') << setw(40) << "Item ID: " << itemID << setfill('-') << setw(40) << "\n" << setfill(' ');
        storedItem->viewInfos();
        itemID++;
    }
    if (!isEmpty)
        cout << setfill('-') << setw(81) << "\n" << setfill(' ');
    else    
        cout << "\033[31m\x1b[1;4mInventory Empty!\033[m\x1b[0m 🎒🔍\n";
    // for (auto storedWeapon : storedWeapons){
    //     cout << setfill('-') << setw(20) << "Item ID: " << itemID << setfill('-') << setw(11) << "\n";
    //     storedWeapon->showInfos();
    //     itemID++;
    // }
    // cout << setfill('-') << setw(41) << "\n";
    // for (auto storedShovel : storedShovels){
    //     cout << setfill('-') << setw(20) << "Item ID: " << itemID << setfill('-') << setw(11) << "\n";
    //     storedShovel->showInfos();
    //     itemID++;
    // }
    // cout << setfill('-') << setw(41) << "\n";
    // for (auto storedKey : storedKeys){
    //     cout << setfill('-') << setw(20) << "Item ID: " << itemID << setfill('-') << setw(11) << "\n";
    //     storedKey->showInfos();
    //     itemID++;
    // }
    // cout << setfill('-') << setw(41) << "\n";
}

void PlayerInmate::viewPlayerInmateProfile() const{
    this->viewProfile();
    cout << setfill('-') << setw(57) << "\n" << setfill(' ');
    outfit.viewInfos();
    cout << setfill('-') << setw(57) << "\n" << setfill(' ');
}

Item PlayerInmate::giveItemTo(int itemID, const BotInmate &botInmate){
    if (itemID >= 0 && itemID <= storedItems.size()){
            Item releasedItem(storedItems[itemID]->getItemName(), botInmate, botInmate.getCurrentLocation());
            delete storedItems[itemID];
            storedItems.erase(storedItems.begin() + itemID);
            for (int i = 0; i < acceptedRequests.size(); i++){
                if (acceptedRequests[i]->getName() == botInmate.getName() && 
                    storedItems[itemID]->getItemName() == botInmate.getRequest().itemName){
                    delete acceptedRequests[i];
                    acceptedRequests.erase(acceptedRequests.begin() + i);
                    break;
                }
            }
            return releasedItem;
        }

    throw std::out_of_range("🚫 \033[31m\x1b[1;4mInvalid Item ID!\033[m\x1b[0m 🚫 Item not found with ID: " + std::to_string(itemID));
}

void PlayerInmate::showAcceptedRequests() const{
    bool isEmpty = true;
    for (auto acceptedRequest : acceptedRequests){
        isEmpty = false;
        cout << setfill('-') << setw(40) << "\x1b[1;4m" << acceptedRequest->getName() << "'s Request\x1b[0m" << setfill('-') << setw(15) << "\n" << setfill(' ');
        acceptedRequest->showRequest();
    }
    if (isEmpty)
        cout << "🙅 \x1b[1;4mOops! No requests were accepted.\x1b[0m 🙅\n";
}

json PlayerInmate::toFullJson() const{
    json playerInmateJson = this->toJson();
    playerInmateJson["outfit"] = outfit.toJson();
    playerInmateJson["currentLocation"] = this->getCurrentLocation();

    if (storedItems.empty()){
        playerInmateJson["storedItems"] = json::array();
    }else{
        for (auto storedItem : storedItems)
            playerInmateJson["storedItems"].push_back(storedItem->toJson());
    }

    if (acceptedRequests.empty()){
        playerInmateJson["acceptedRequests"] = json::array();
    }else{
        for (auto acceptedRequest : acceptedRequests)
            playerInmateJson["acceptedRequests"].push_back(acceptedRequest->toFullJson());
    }

    return playerInmateJson;
}

PlayerInmate::~PlayerInmate(){
    for (int i=0; i < storedItems.size(); i++){
        delete storedItems[i];
        storedItems.erase(storedItems.begin() + i);
    }
    for (int i=0; i < acceptedRequests.size(); i++){
        delete acceptedRequests[i];
        acceptedRequests.erase(acceptedRequests.begin() + i);
    }
}