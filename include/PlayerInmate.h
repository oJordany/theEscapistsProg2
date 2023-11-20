#ifndef PLAYERINMATE_H
#define PLAYERINMATE_H

#include "Inmate.h"

#include <string>
using std::string

#include <iostream>
using std::ostream;
using std::out;

class PlayerInmate{
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
    private:
        const static MAXNUMITEMS = 6;
        // Item *itemStorage[MAXNUMITEMS];
        vector <*BotInmate> requestsAccepted;
}

#endif //PLAYERINMATE_H