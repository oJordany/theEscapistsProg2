/* 
 * File:   Data.h
 * Author: Cssj
 *
 * Created on 9 de Junho de 2012, 14:47
 */

#ifndef DATA_H
#define	DATA_H

class Data 
{
public:
    
    Data( int = 1, int = 1, int = 1900 );
    
    void print() const;
    
private:
    
    int mes;
    int dia;
    int ano;
    
    int VerificaDia( int ) const;


};

#endif	/* DATA_H */

