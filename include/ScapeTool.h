#ifndef SCAPETOOL_H
#define SCAPETOOL_H

#include "Item.h"
#include "Inmate.h"

class ScapeTool : public Item {
    friend ostream &operator<<(ostream &, const ScapeTool &)
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
    int getDurability() const;
    void viewScapeToolInfos() const;

private:
    int durability;
    const static int MAX_DURABILITY = 100;
};

#endif // SCAPETOOL_H
