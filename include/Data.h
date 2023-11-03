/* 
 * File:   Data.h
 * Author: Cssj
 *
 * Created on 9 de Junho de 2012, 14:47
 */

#ifndef DATA_H
#define	DATA_H

#include <iostream>
using std::ostream;

class Data 
{
    // Added by Luiz Jordany (https://github.com/oJordany)
    friend ostream &operator<<(ostream &, const Data &);

public:
    
    Data( int = 1, int = 1, int = 1900 );
    // Added by Luiz Jordany (https://github.com/oJordany)
    Data(const Data &);
    // Added by Luiz Jordany (https://github.com/oJordany)
    ~Data();
    bool operator==(const Data &data) const;
    bool operator!=(const Data &data) const;
    
    void print() const;
    
    void incrementaData();
    inline int getDia() const {return dia;} 
    inline int getMes() const {return mes;} 
    inline int getAno() const {return ano;} 
    
private:
    
    int mes;
    int dia;
    int ano;
    
    int VerificaDia( int ) const;

    // Added by Luiz Jordany (https://github.com/oJordany)
};

#endif	/* DATA_H */

