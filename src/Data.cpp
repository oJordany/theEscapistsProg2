/* 
 * File:   Data.cpp
 * Author: Cssj
 * 
 * Created on 9 de Junho de 2012, 14:47
 */

#include "Data.h"

#include <iostream>
using std::cout;

#include <iomanip>
using std::setw;
using std::setfill;
using std::right;

Data::Data(int d, int m, int a) 
{
    if ( m > 0 && m <= 12 ) // validate the month
        mes = m;
    
    if ( a < 0 )
        ano = 1900;
    else
        ano = a;
   
    dia = VerificaDia(d);

}

Data::Data(const Data &outraData){
    dia = outraData.dia;
    mes = outraData.mes;
    ano = outraData.ano;
}

void Data::print() const
{
   cout << dia << '/' << mes << '/' << ano;
   
}

int Data::VerificaDia(int diaTeste) const
{
    static const int diasPorMes[ 13 ] = 
       { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    
    if ( diaTeste > 0 && diaTeste <= diasPorMes[ mes ] )
        return diaTeste;
    
    if ( mes == 2 && diaTeste == 29 && ( ano % 400 == 0 ||
            ( ano % 4 == 0 && ano % 100 != 0 ) ) )
        return diaTeste;
    
    // cout << "Dia invalido (" << diaTeste << ") configurado para 1.\n";
    return 1; 

    
}

// Added by Luiz Jordany (https://github.com/oJordany)
void Data::incrementaData(){
    dia = VerificaDia(dia+1);
    if (dia != 1)
        return;

    int novoMes = mes + 1;
    if (novoMes > 0 && novoMes <= 12){
        mes = novoMes;
        return;
    }

    mes = 1;
    ano++;

}

ostream &operator<<(ostream &out, const Data &data){
    out << setfill('0') << setw(2) << right << data.dia << "/";
    out << setfill('0') << setw(2) << right << data.mes << "/";
    out << setfill(' ') << data.ano;

    return out;
}

bool Data::operator==(const Data &data) const{
    if (data.dia != this->dia)
        return false;
    if (data.mes != this->mes)
        return false;
    if (data.ano != this->ano)
        return false;
    return true;
}

bool Data::operator!=(const Data &data) const{
    return !(*this == data);
}

Data::~Data(){
    //...
}