/*Criar três hierarquia, sendo duas de três níveis, como explicado em sala e 
no Classroom. Fazer a sobrecarga para cada classe dos operadores =, ==, ≠, ! e << 
(friend). Usar sempre que possível o static_cast para reaproveitamento de código. 
Para cada classe do seu projeto criar pelo menos três constructores, 
sendo um o constructor de cópia. É necessário ter a funcionalidade: 1. 
leitura de arquivos para configuração das suas classes e variáveis de status, 2. 
processamento das variáveis de status e 3. salvamento dessas variáveis. 
Sem o diagrama UML, a saída do programa e o vídeo, o trabalho não será avaliado.*/


//// Geral - parte para revisão
    //Diagrama UML    
    //Organização do código 

//// O .h das classes bases

     ////Classe base 1  (Inmate)
        #ifndef INMATE_H
        #define INMATE_H

        #include <string>
        using std::string;

        #include <iostream>
        using std::cout;
        using std::ostream;

        #include <map>
        using std::map;

        #include <nlohmann/json.hpp>
        using json = nlohmann::json;

        class Inmate
        {
            friend ostream &operator<<(ostream &, const Inmate &);

        public:
            Inmate();
            Inmate( string, 
                    int = 100, 
                    int = 100, 
                    int = 40, 
                    int = 40, 
                    int = 40, 
                    double = 0.0);
            Inmate(const Inmate &); 
            ~Inmate();
            const Inmate & operator=(const Inmate &);   // operador de atribuição
            bool operator==(const Inmate &) const;      // operador de igualdade
            bool operator!=(const Inmate &) const;      // operador de diferença
            bool operator!() const;                     // operador de negação

            json toJson() const;
            string getName() const;
            int getHealth() const;
            int getEnergy() const;
            int getStrength() const;
            int getSpeed() const;
            int getIntelligence() const;
            double getMoney() const;
            inline string getCurrentLocation() const {return currentLocation;};
            inline bool isNull() const { return this == nullptr; }
            inline void moveTo(string newLocation) { currentLocation = newLocation;};

            void setName(string);
            void setHealth(int);
            void setEnergy(int);
            void setStrength(int);
            void setSpeed(int);
            void setIntelligence(int);
            void setMoney(double);
            static string getInmateNameByID(int);
            static void viewAllInmates();

            void viewProfile() const;
            void readBook(int = 1);
            void bathe(int=5);
            void workOut(int=1);

        private:
            string name;
            int health; 
            int energy;
            int strength;
            int speed;
            int intelligence;
            double money;
            string currentLocation;
            void showPercentageBar(int) const;
            void repeatCharacter(string, int) const;
            const int MAXSIZENAME = 10;
            static map<int, string> inmateMap;
            static int nextId;
        };

        #endif

     ////Classe base 2 (Item)
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

        #include <nlohmann/json.hpp>
        using json = nlohmann::json;

        class Item{
            friend ostream &operator<<(ostream &, const Item &);
            public:
                Item();
                Item(string, string="", string="");
                Item(string, const Inmate&, string="");
                Item(const Item&);
                ~Item();
                json toJson() const;
                const Item & operator=(const Item &);
                bool operator==(const Item &) const;
                bool operator!=(const Item &) const;
                bool operator!() const;
                void catchItem(const Inmate&);
                void giveTo(const Inmate&);
                void drop(string);
                void viewInfos() const;
                inline void setOwnerName(string name){this->ownerName = name;};
                inline void setCurrentLocation(string location){currentLocation = location;};
                inline string getItemName() const {return itemName;};
                inline string getCurrentLocation() const {return currentLocation;};

            private:
                string itemName;
                string ownerName;
                string currentLocation;
                const static int MAXNUMITEMTYPES = 24;
                const static string ITEMTYPES[MAXNUMITEMTYPES];
                string drawItem() const;
                void setItemName(string);
                string strip(const string&) const;
                string toLowerCase(string) const;
        };

        #endif //ITEM_H

     ////Classe base 3
        // Falta fazer ...

//// O .h da hierarquia 1

     ////Classe 1   (BotInmate)
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

     ////Classe 2 (PlayerInmate)
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
                void viewPlayerInmateProfile() const;
                Item giveItemTo(int, const BotInmate&); // Toda vez que for dar um item, verificar se ele mata uma request
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

     ///E assim por diante

//// O .h da hierarquia 2

     ////Classe 1
     // Falta fazer ...

     ////Classe 2
     // Falta fazer ...

     ///E assim por diante

//// O .h da hierarquia 3

     ////Classe 1
     // Falta fazer ...

     ////Classe 2
     // Falta fazer ...

     ///E assim por diante


//// Mostrar implementação de método que especializa a derivada
 /// Mostrar reaproveitamente de código da base

    //// Hierarquia 1

         ////Classe 1 (BotInmate)
            // toFullJson()
                json BotInmate::toFullJson() const{
                    json botInmateJson = this->toJson();
                    json requestJson;
                    requestJson["description"] = request.description;
                    requestJson["itemName"] = request.itemName;
                    requestJson["status"] = request.status;
                    botInmateJson["request"] = requestJson;
                    return botInmateJson;
                }

            // showRequest()
                void BotInmate::showRequest() const{
                    cout << "\033[34mRequest Description:\033[m " << this->request.description << "\n"; 
                    cout << "\033[34mRequest Status:\033[m " << ((this->request.status) ? "\033[32m☑\033[m Completed" : "☐ Pending") << "\n"; 
                }

            // drawRequest()
            Request BotInmate::drawRequest() const{
                int randomIndex = rand() % MAXNUMREQUESTS;
                return REQUESTS[randomIndex];
            }

            // completeRequest()
            double BotInmate::completeRequest(const Item &item){
                if (item.getItemName() == request.itemName){
                    request.status = 1;
                    return REWARDVALUE;
                }
                return 0.0;
            }

         ////Classe 2 (PlayerInmate)
            // toFullJson()
            json BotInmate::toFullJson() const{
                json botInmateJson = this->toJson();
                json requestJson;
                requestJson["description"] = request.description;
                requestJson["itemName"] = request.itemName;
                requestJson["status"] = request.status;
                botInmateJson["request"] = requestJson;
                return botInmateJson;
            }

            // refreshStoredItemsLocations()
            void PlayerInmate::refreshStoredItemsLocations(){
                for (auto storedItem: storedItems){
                    storedItem->setCurrentLocation(this->getCurrentLocation());
                }
            }

            // refreshOutfitLocations()
            void PlayerInmate::refreshOutfitLocation(){
                outfit.setCurrentLocation(this->getCurrentLocation());
            }

            // addItem()
            void PlayerInmate::addItem(const Item &item){
                if (storedItems.size() < MAXNUMITEMS){
                    storedItems.push_back(new Item(item));
                    cout << "\033[32m" << item.getItemName() << " foi pego e adicionado ao inventário!\033[m\n";
                }else{ 
                    cout << "🚫 \033[31m\x1b[1;4mWarning! Inventory Full!\x1b[0m\033[m 🚫" << "\n";
                    cout << "Please make space before adding more items. 🧳🔒\n";
                }
            }

            // sleep()
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

            // acceptRequest()
            void PlayerInmate::acceptRequest(const BotInmate &botInmate){
                if (botInmate.getCurrentLocation() == this->getCurrentLocation())
                    acceptedRequests.push_back(new BotInmate(botInmate));
                else    
                    cout << "🚫 \033[31m\x1b[1;4mInmate not found!\033[m\x1b[0m 🚫\n";
            }

            // dropItem()
            Item PlayerInmate::dropItem(int itemID){
                if (!storedItems.empty() && itemID >= 0 && itemID <= storedItems.size() && itemID < MAXNUMITEMS){
                    Item releasedItem(storedItems[itemID]->getItemName(), "", this->getCurrentLocation());
                    delete storedItems[itemID];
                    storedItems.erase(storedItems.begin() + itemID);
                    return releasedItem;
                }

                throw std::out_of_range("🚫 \033[31m\x1b[1;4mInvalid Item ID!\033[m\x1b[0m 🚫 Item not found with ID: " + std::to_string(itemID));
            }

            // showInventory()
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
            }

            // viewInmateProfile()
            void PlayerInmate::viewPlayerInmateProfile() const{
                this->viewProfile();
                cout << setfill('-') << setw(57) << "\n" << setfill(' ');
                outfit.viewInfos();
                cout << setfill('-') << setw(57) << "\n" << setfill(' ');
            }

            // giveItemTo()
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

            // showAcceptedRequests()
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


         ///E assim por diante

    //// Hierarquia 2

         ////Classe 1
         // Falta fazer ...

         ////Classe 2
         // Falta fazer ...

         ///E assim por diante


    //// Hierarquia 3

         ////Classe 1

         ////Classe 2

         ///E assim por diante



//// Fazer a sobrecarga para todas as classes dos operadores =, ==, ≠ e << (friend)

     //// Operator=
         //// Base 1 (Inmate)
                const Inmate & Inmate::operator=(const Inmate &inmateOnTheRight){
                    if (this != &inmateOnTheRight){
                        this->name = inmateOnTheRight.name;
                        this->health = inmateOnTheRight.health;
                        this->energy = inmateOnTheRight.energy;
                        this->strength = inmateOnTheRight.strength;
                        this->speed = inmateOnTheRight.speed;
                        this->intelligence = inmateOnTheRight.intelligence;
                        this->money = inmateOnTheRight.money;
                        this->currentLocation = inmateOnTheRight.currentLocation;
                    }

                    return *this;
                }
             ////Derivadas da Base 1 - mostrar uso static_cast
                //// Classe 1 (BotInmate)
                const BotInmate & BotInmate::operator=(const BotInmate &botInmateOnTheRight){
                    *static_cast<Inmate*>(this) = static_cast<Inmate>(botInmateOnTheRight); // -> USO DO static_cast
                    this->request.description = botInmateOnTheRight.request.description;
                    this->request.itemName = botInmateOnTheRight.request.itemName;
                    this->request.status = botInmateOnTheRight.request.status;
                    return *this;
                }

                //// Classe 2 (PlayerInmate)
                const PlayerInmate & PlayerInmate::operator=(const PlayerInmate &playerInmateOnTheRight){
                    *static_cast<Inmate*>(this) = static_cast<Inmate>(playerInmateOnTheRight);  // USO DO static_cast
                    this->outfit = playerInmateOnTheRight.outfit;
                    for (int i=0; i < this->storedItems.size(); i++){
                        delete this->storedItems[i];
                    }
                    this->storedItems.resize(0);
                    for (auto storedItem : playerInmateOnTheRight.storedItems){
                        this->storedItems.push_back(new Item(*storedItem));
                    }
                    for (int i=0; i < this->acceptedRequests.size(); i++){
                        delete this->acceptedRequests[i];
                    }
                    this->acceptedRequests.resize(0);
                    for (auto acceptedRequest : playerInmateOnTheRight.acceptedRequests){
                        this->acceptedRequests.push_back(new BotInmate(*acceptedRequest));
                    }
                    return *this;
                }


         //// Base 2 (Item)
                const Item& Item::operator=(const Item &itemOnTheRight){
                    this->itemName = itemOnTheRight.itemName;
                    this->currentLocation = itemOnTheRight.currentLocation;
                    this->ownerName = itemOnTheRight.ownerName;

                    return *this;
                }
             ////Derivadas da Base 2 - mostrar uso static_cast
                // Falta fazer ...

        //// Base 3
            // Falta fazer ...
            ////Derivadas da Base 3 - mostrar uso static_cast


     //// Operators== e !=
         //// Base 1 (Inmate)
            bool Inmate::operator==(const Inmate &inmateOnTheRight) const{
                if (this->MAXSIZENAME != inmateOnTheRight.MAXSIZENAME){
                    return false;
                }
                if (this->name != inmateOnTheRight.name){
                    return false;
                }
                if (this->health != inmateOnTheRight.health){
                    return false;
                }
                if (this->energy != inmateOnTheRight.energy){
                    return false;
                }
                if (this->strength != inmateOnTheRight.strength){
                    return false;
                }
                if (this->speed != inmateOnTheRight.speed){
                    return false;
                }
                if (this->intelligence != inmateOnTheRight.intelligence){
                    return false;
                }
                if (this->money != inmateOnTheRight.money){
                    return false;
                }

                return true; 
            }

            bool Inmate::operator!=(const Inmate &inmateOnTheRight) const{
                return ! (*this == inmateOnTheRight);
            }

             ////Derivadas da Base 1 - mostrar uso static_cast
                //// Classe 1 (BotInmate)
                bool BotInmate::operator==(const BotInmate &botInmateOnTheRight) const{
                    if (static_cast<Inmate>(*this) != static_cast<Inmate>(botInmateOnTheRight)) // USO DO static_cast
                        return false;
                    if (this->request.description != botInmateOnTheRight.request.description)
                        return false;
                    if (this->request.itemName != botInmateOnTheRight.request.itemName)
                        return false;
                    if (this->request.status != botInmateOnTheRight.request.status)
                        return false;
                    return true;
                }

                bool BotInmate::operator!=(const BotInmate &botInmateOnTheRight) const{
                    return !(*this == botInmateOnTheRight);
                }
                //// Classe 2 (PlayerInmate)
                bool PlayerInmate::operator==(const PlayerInmate &playerInmateOnTheRight) const{
                    if (static_cast<Inmate>(*this) != static_cast<Inmate>(playerInmateOnTheRight))  // USO DO static_cast
                        return false;
                    if (this->outfit != playerInmateOnTheRight.outfit)
                        return false;
                    if (this->storedItems.size() != playerInmateOnTheRight.storedItems.size())
                        return false;
                    if (this->acceptedRequests.size() != playerInmateOnTheRight.acceptedRequests.size())
                        return false;
                    for (int i=0; i < this->storedItems.size(); i++){
                        if (this->storedItems[i] != playerInmateOnTheRight.storedItems[i])
                            return false;
                    }
                    for (int i=0; i < this->acceptedRequests.size(); i++){
                        if (this->acceptedRequests[i] != playerInmateOnTheRight.acceptedRequests[i])
                            return false;
                    }
                    return true;
                }

                bool PlayerInmate::operator!=(const PlayerInmate &playerInmateOnTheRight) const{
                    return (*this == playerInmateOnTheRight);
                }

         //// Base 2
                bool Item::operator==(const Item &itemOnTheRight) const{
                    if (this->itemName != itemOnTheRight.itemName)
                        return false;
                    if (this->currentLocation != itemOnTheRight.currentLocation)
                        return false;
                    if (this->ownerName != itemOnTheRight.ownerName)
                        return false;
                    
                    return true;
                }

                bool Item::operator!=(const Item &itemOnTheRight) const{
                    return !(*this == itemOnTheRight);
                }
             ////Derivadas da Base 2 - mostrar uso static_cast
                // Falta fazer ...
        //// Base 3
            // Falta fazer ...
            ////Derivadas da Base 3 - mostrar uso static_cast
                // Falta fazer ...

     //// Operator<<
        //// Base 1 (Inmate)

            ////Derivadas da Base 1 - mostrar uso static_cast 
                //// Classe 1 (BotInmate)
                    ostream &operator<<(ostream &out, const BotInmate &botInmate){
                    out << static_cast<Inmate>(botInmate);                                  // USO DO static_cast
                    out << "Request Description: " << botInmate.request.description << "\n"; 
                    out << "Requested Item Name: " << botInmate.request.itemName << "\n"; 
                    out << "Request Status: " << botInmate.request.status << "\n"; 

                    return out;
                }
                //// Classe 2 (PlayerInmate)
                    ostream &operator<<(ostream &out, const PlayerInmate &playerInmate){
                        out << static_cast<Inmate>(playerInmate);                           // USO DO static_cast
                        out << "outfit: " << playerInmate.outfit << "\n"; 
                        out << "\033[1mstored items: \033[0m\n"; 
                        for (auto storedItem : playerInmate.storedItems)
                            out << *storedItem << "\n";
                        out << "\n\033[1maccepted requests: \033[0m\n"; 
                        for (auto acceptedRequest : playerInmate.acceptedRequests){
                            cout << acceptedRequest->getName() << "'s request:\n";
                            acceptedRequest->showRequest();
                            cout << "\n";
                        }

                        return out;
                    }

        //// Base 2 (Item)
            ostream &operator<<(ostream &out, const Item &item){
                out << "itemName: " << item.itemName << "\n";
                out << "ownerName: " << ((item.ownerName == "") ? "null" : item.ownerName) << "\n";
                out << "currentLocation: " << ((item.currentLocation == "") ? "null" : item.currentLocation) << "\n";

                return out;
            }
            ////Derivadas da Base 2 - mostrar uso static_cast
            // Falta fazer ...

       //// Base 3
            // Falta fazer ...
            ////Derivadas da Base 3 - mostrar uso static_cast
                // Falta fazer ...


//// Para cada classe do seu projeto criar pelo menos dois constructores, 
 //sendo um o constructor de cópia 
 ////Mostrar uso de reaproveitamento de código da base na derivada

    //// Base 1 (Inmate) - constructores
        ////Constructor 1
            Inmate::Inmate()
            :name("Player"), health(100), energy(100), strength(40), speed(40), intelligence(40), money(0), currentLocation(""){
                Inmate::inmateMap[nextId++] = name;
            }

        ////Constructor 2
            Inmate::Inmate( string name,
                            int health,
                            int energy,
                            int strength,
                            int speed,
                            int intelligence ,
                            double money){
                setName(name);
                setHealth(health);
                setEnergy(energy);
                setStrength(strength);
                setSpeed(speed);
                setIntelligence(intelligence);
                setMoney(money);
                currentLocation = "";
                Inmate::inmateMap[nextId++] = this->name;
            }
        ////Constructor de cópia
            Inmate::Inmate( const Inmate& other )
            :MAXSIZENAME(10){
                this->name = other.name;
                this->health = other.health;
                this->energy = other.energy;
                this->strength = other.strength;
                this->speed = other.speed;
                this->intelligence = other.intelligence;
                this->money = other.money;
                Inmate::inmateMap[nextId++] = this->name;
                this->currentLocation = other.currentLocation;
            }


    //// Base 2 (Item) - constructores
        ////Constructor 1
            Item::Item(){
                itemName = drawItem();
                currentLocation = "";
            }
        ////Constructor 2
            Item::Item(string item, string ownerName, string locationName)
            :currentLocation(locationName), ownerName(ownerName){
                setItemName(item);
            }
        ////Constructor 3
            Item::Item(string item, const Inmate &owner, string locationName)
            :currentLocation(locationName), ownerName(owner.getName()){
                setItemName(item);
            }
        ////Constructor de cópia
            Item::Item(const Item &other){
                this->itemName = other.itemName;
                this->ownerName = other.ownerName;
                this->currentLocation = other.currentLocation;
            }

    //// Base 3 - constructores
        ////Constructor 1
        // Falta fazer ...
        ////Constructor de cópia 
        // Falta fazer ...

    ////Derivadas - constructores

        //// Hierarquia 1

             ////Classe 1 (BotInmate)
                 ////Constructor 1
                    BotInmate::BotInmate()
                    :Inmate(){                          // uso de reaproveitamento de código da base na derivada
                        request = drawRequest();
                    }
                 ////Constructor 2
                    BotInmate::BotInmate(string name,
                                        int health,
                                        int energy,
                                        int strength,
                                        int speed,
                                        int intelligence ,
                                        double money)
                    :Inmate(name, health, energy, strength, speed, intelligence, money){    // uso de reaproveitamento de código da base na derivada
                        request = drawRequest();
                    }

                 ////Constructor de cópia
                    BotInmate::BotInmate(const BotInmate &other)    
                    :Inmate(static_cast<Inmate>(other)){                // uso de reaproveitamento de código da base na derivada
                        this->request = other.request;
                    }

             ////Classe 2 (PlayerInmate)
                 ////Constructor 1
                    PlayerInmate::PlayerInmate()
                    :Inmate(), outfit(Item("inmate outfit", Inmate())){     // uso de reaproveitamento de código da base na derivada
                        //...
                    }
                 ////Constructor 2
                    PlayerInmate::PlayerInmate( string name,
                                                int health,
                                                int energy,
                                                int strength,
                                                int speed,
                                                int intelligence,
                                                double money
                                                ):  Inmate(name, health, energy, strength, speed, intelligence, money), // uso de reaproveitamento de código da base na derivada
                                                    outfit(Item("inmate outfit", Inmate(name, health, strength, speed, intelligence, money))){
                        //...
                    }

                 ////Constructor de cópia
                    PlayerInmate::PlayerInmate(const PlayerInmate &other) 
                    :Inmate(static_cast<Inmate>(other)), outfit(Item(other.outfit)){            // uso de reaproveitamento de código da base na derivada
                        for (auto storedItem : other.storedItems){
                            this->storedItems.push_back(new Item(*storedItem));
                        }
                        for (auto acceptedRequest : other.acceptedRequests){
                            this->acceptedRequests.push_back(new BotInmate(*acceptedRequest));
                        }
                    }
             
             ///E assim por diante


        //// Hierarquia 2
            // Falta fazer ...
             ////Classe 1
                 ////Constructor 1

                 ////Constructor de cópia

             ////Classe 2
                 ////Constructor 1

                 ////Constructor de cópia

             ///E assim por diante


      //// Hierarquia 3
            // Falta fazer ...
             ////Classe 1
                 ////Constructor 1

                 ////Constructor de cópia

             ////Classe 2
                 ////Constructor 1

                 ////Constructor de cópia

             ///E assim por diante

//// Carregamento e salvamento de arquivos
    /*É necessário ter a funcionalidade: 1. 
      leitura de arquivos para configuração das suas classes e variáveis de status, 2. 
      processamento das variáveis de status e 3. salvamento dessas variáveis. 
      Sem o diagrama UML, a saída do programa e o vídeo, o trabalho não será avaliado.*/

    //Link arquivo de configuração no repositório
        // Meu arquivo util.h: https://github.com/oJordany/theEscapistsProg2/blob/main/include/util.h
        // Arquivo json pré pronto para iniciar o jogo a partir de um progresso já salvo: 
    //Link vídeo mostrando a execução do código usando o arquivo de configuração