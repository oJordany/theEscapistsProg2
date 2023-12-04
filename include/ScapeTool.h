#ifndef SCAPETOOL_H
#define SCAPETOOL_H

#include "Item.h"
#include "Inmate.h"

class ScapeTool : public Item {
    friend ostream &operator<<(ostream &, const ScapeTool &);
public:
    ScapeTool();
    ScapeTool(string, string="", string="", int=100);
    ScapeTool(string, const Inmate&, string="", int=100);
    ScapeTool(const ScapeTool&);
    ~ScapeTool();

    const ScapeTool& operator=(const ScapeTool &);
    bool operator==(const ScapeTool &) const;
    bool operator!=(const ScapeTool &) const;
    bool operator!() const;

    void setDurability(int);
    inline int getDurability() const {return durability;}
    void viewScapeToolInfos() const;
    inline string getScapeLocation() const{return scapeLocation;}
    inline void setScapeLocation(string location){scapeLocation = location;} 
    inline bool checkUsage(string currentLocation) const {return (currentLocation == scapeLocation) ? true : false;}


private:
    int durability;
    string scapeLocation;
    const static int MAX_DURABILITY = 100;
};

#endif // SCAPETOOL_H
