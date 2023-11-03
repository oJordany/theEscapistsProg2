#include <iostream>
using std::cerr;
using std::cin;
using std::cout;

#include <string>
using std::string;
using std::getline;

#include <fstream>
using std::fstream;
using std::ifstream;
using std::ofstream;

#include <sstream>
using std::istringstream;

#include <iomanip>
using std::ws;

#include <map>
using std::map;

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "Data.h"
#include "Inmate.h"
#include "JobBoard.h"
#include "Prison.h"
#include "Time.h"

string strip(const string& str) {
    size_t first = str.find_first_not_of(" \t\n\r\f\v");
    size_t last = str.find_last_not_of(" \t\n\r\f\v");

    if (first == string::npos) // Se a string está vazia ou contém apenas espaços em branco
        return "";

    return str.substr(first, (last - first + 1));
}

json loadSaves( string nameFile )
{

    ifstream inputFile(nameFile);

    json storage;
    
    if ( !inputFile.is_open() ) 
    {
        cerr << "Error opening file." << '\n';
        return storage; // Exit with an error code
    }

    inputFile >> storage;

    inputFile.close();

    return storage;

}

bool loadConfig( map<string, string>& variables, string nameFile )
{

    ifstream inputFile(nameFile);

    if ( !inputFile.is_open() ) 
    {
        cerr << "Error opening file." << '\n';
        return false; // Exit with an error code
    }

    string line;    
    string variableName;
    char equalsSign;
    string value;
    while (getline(inputFile, line)) 
    {
        istringstream iss(line);
        if (getline(iss >> ws, variableName, '=') && getline(iss >> ws, value)){
            variableName = strip(variableName);
            value = strip(value);
            variables[variableName] = value;
        }else
            cerr << "Error parsing line: " << line << '\n';
    }

    if( variables.size( ) == 0 )
    {   
        cerr << "No variables found.\n";
        return false;
    }

    inputFile.close();

    return true;

}

bool saveConfigs( const json& datas, string nameFile="saves.json" )
{
    // abre o arquivo pra escrita 
    ofstream outputFile(nameFile, std::ios::out);
    if (!outputFile.is_open()) {
        cerr << "Erro ao abrir aquivo para escrita!" << '\n';
        return false; //
    }

    outputFile << datas.dump(4);
    outputFile.close();
    cout << "Dados salvos com sucesso!" << '\n';
    return true;
}


void createInfos( string nameFile, int id = 0 )
{
    int dia;
    int mes;
    int ano;

    cout << "Para jogar, insira sua data de nascimento (dia mês ano): ";
    if (!(cin >> dia >> mes >> ano)) {
        cerr << "entrada inválida!" << '\n';
        return; // Exit with an error code
    }

    // abre o arquivo pra escrita 
    ofstream outputFile(nameFile, std::ios::out | std::ios::trunc);
    if (!outputFile.is_open()) {
        cerr << "Erro ao abrir aquivo para escrita!" << '\n';
        return; //
    }
		// escreve no arquivo 
    outputFile << "id = " << id << '\n';
    outputFile << "dia = " << dia << '\n';
    outputFile << "mes = " << mes << '\n';
    outputFile << "ano = " << ano << '\n';

    outputFile.close();
    cout << "Dados salvos com sucesso!" << '\n';
    return;
}
