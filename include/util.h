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
    // abre o arquivo pra leitura
    ifstream inputFile(nameFile);
    if (!inputFile.is_open()) {
        cerr << "Erro ao abrir aquivo para leitura!" << '\n';
        return false; 
    }

    json storage;

    inputFile >> storage;

    for (auto data : datas.items()){
        cout << data.key() << "\n";
        storage["centerPerks"] = data.value();
    }
    inputFile.close();

    // abre o arquivo para escrita
    ofstream outputFile(nameFile);
    if (!outputFile.is_open()) {
        cerr << "Erro ao abrir aquivo para escrita!" << '\n';
        return false; 
    }

    outputFile << storage.dump(4);

    outputFile.close();
    cout << "Dados salvos com sucesso!" << '\n';
    return true;
}

void showFigure(string figureName){
    ifstream inputFile("../utils/"+figureName);

    if (inputFile.is_open()){
        string line;
        while (getline(inputFile, line)){
            cout << line << "\n";
        }
        inputFile.close();
    }else{
        cout << "Erro ao abrir o arquivo para leitura!\n";
    }
}

void createInfos( int prisonID = 1 )
{   
    const int INMATESNUMBER = 10;
    const int LOCATIONSNUMBER = 12;
    string inmateName;
    cout << "\t_________________________\n";
    cout << "\t   ||   ||     ||   ||   \n";
    cout << "\t   ||   ||, , ,||   ||   \n";
    cout << "\t   ||  (||/|/(\\||/  ||   \n";
    cout << "\t   ||  ||| _'_`|||  ||   \n";
    cout << "\t   ||   || o o ||   ||   \n";
    cout << "\t   ||  (||  - `||)  ||   \n";
    cout << "\t   ||   ||  =  ||   ||   \n";
    cout << "\t   ||   ||\\___/||   ||   \n";
    cout << "\t   ||\033[30m___\033[m||) , (||\033[30m___\033[m||   \n";
    cout << "\t  /||---||-\\_/-||---||\\  \n";
    cout << "\t / ||\033[30m--_\033[m||\033[30m_____\033[m||\033[30m_--\033[m|| \\ \n";
    cout << "\t(_(||)-| S123-45 |-(||)_)\n";
    cout << "\033[30mINMATE NAME:\033[m ";
    cin >> inmateName;
    if (prisonID == 1){
      map<string, string> tasksInfos;
      string inmateNames[INMATESNUMBER] = {inmateName, "KEV", 
                                "KELAUCE", "CARL", 
                                "CAMEO", "JACKALL", 
                                "ARNIE", "KRIMEWAVE", 
                                "DOGEKIT", "PHIL"};
      string prisonLocations[LOCATIONSNUMBER] = {"Dining Room", "Gymnasium", "Exercise Room", 
                                    "Cleaning Room", "Laundry", "Security Room", 
                                    "Deposit", "Isolation", "Kitchen", 
                                    "Meeting room", "Watch-tower", "Pantry"};

      // CARREGANDO O ARQUIVO DE CONFIGURAÇÕES CONTENDO AS INFORMACOES DAS TASKS
      loadConfig(tasksInfos, "../utils/configs.txt");
      Task tasks[tasksInfos.size()];
      int i = 0;
      for (auto pair : tasksInfos){
          tasks[i].taskName = pair.first;
          tasks[i].taskDetails = pair.second;
          tasks[i].inmate = 0;
          i++;
      }
      
      // // CRIANDO JOBBOARD
      JobBoard jobBoard(tasks, tasksInfos.size());

      Prison centerPerks("Center Perks", 0, jobBoard, Data(31, 12, 2023));

      // REGISTRANDO CADA ROTINA NA ROTINA DIÁRIA DA PRISÃO
      // *O método registerDailyPrisonRoutine() já ordena as rotinas por horário automaticamente*
      // center perks: 
      centerPerks.registerDailyPrisonRoutine({5, 0, 5, 59, "Wake Up Call, Roll Call"});
      centerPerks.registerDailyPrisonRoutine({6, 0, 6, 59, "Breakfast Time"});
      centerPerks.registerDailyPrisonRoutine({9, 0, 9, 59, "Exercise Time"});
      centerPerks.registerDailyPrisonRoutine({10, 0, 11, 59, "Free Time"});
      centerPerks.registerDailyPrisonRoutine({7, 0, 8, 59, "Job Time"}); // ROTINA INSERIDA NA ORDEM ERRADA
      centerPerks.registerDailyPrisonRoutine({12, 0, 12, 59, "Lunch Time"});
      centerPerks.registerDailyPrisonRoutine({13, 0, 13, 59, "Roll Call"});
      centerPerks.registerDailyPrisonRoutine({14, 0, 15, 59, "Job Time"});
      centerPerks.registerDailyPrisonRoutine({16, 0, 16, 59, "Shower Time"});
      centerPerks.registerDailyPrisonRoutine({17, 0, 17, 59, "Dinner Time"});
      centerPerks.registerDailyPrisonRoutine({18, 0, 18, 59, "Free Time"});

      // CADASTRANDO OS 10 PRISIONEIROS NAS PRISÕES
      for (int i=0; i < INMATESNUMBER; i++){
          centerPerks.registerInmateInPrison(Inmate(inmateNames[i]));
      }

      // CADASTRANDO OS LOCAIS NA PRISÕES
      for (auto location : prisonLocations){
          centerPerks.registerLocationInPrison(location);
      }
       
      cout << "startPrisonTime\n";
      centerPerks.startPrisonTime(Data(31, 12, 2023), 5, 0);
      json centerPerksJson = centerPerks.toJson("centerPerks")
      saveConfigs(centerPerks);
    }


}
