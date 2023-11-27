#ifndef SHOVEL_H
#define SHOVEL_H

#include "ScapeTools.h"

#include <iostream>
using std::ostream;

#include <map>
using std::map;
using std::advance;

#include <cstdlib> // Para usar a função rand()

class Shovel : public ScapeTools {
public:

    Shovel();
    Shovel(string, string="", string="", string="", int=100);
    Shovel(const Shovel&);
    ~Shovel();

    void viewShovelInfos() const;
    void dig();

private:
    string type;
    const static map<string, int> TYPES_MAP;
};

#endif // SHOVEL_H
