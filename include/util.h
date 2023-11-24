#include <iostream>
using std::cerr;
using std::cin;
using std::cout;

#include <iomanip> 
using std::setw;

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

#include <chrono>
using std::chrono::milliseconds;

#include <thread>
using std::this_thread::sleep_for;

#include <cctype>
using std::tolower;

#include "Data.h"
#include "Inmate.h"
#include "BotInmate.h"
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

string toLowerCase(string str){
    for (auto &character : str) character = tolower(character);
    return str;
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
        cerr << "Erro ao abrir aquivo para leitura! Tentando criá-lo ..." << '\n';
        // abre o arquivo para escrita
        ofstream outputFile(nameFile);
        if (!outputFile.is_open()) {
            cerr << "Erro ao abrir aquivo para escrita!" << '\n';
            return false; 
        }

        outputFile << datas.dump(4);

        outputFile.close();
        return true; 
    }

    json storage;

    inputFile >> storage;

    for (auto data : datas.items()){
        storage[data.key()] = data.value();
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

void showTypeWritterAnimation(string figureName){
    ifstream inputFile("../utils/"+figureName);

    if (inputFile.is_open()){
        string line;
        while (getline(inputFile, line)){
            for (int i=0; line[i] != '\0'; i++){
                cout << line[i];
                sleep_for(milliseconds(1));
                cout.flush();
            }
            cout << " \n";
        }
        inputFile.close();
    }else{
        cout << "Erro ao abrir o arquivo para leitura!\n";
    }
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
    // const int LOCATIONSNUMBER = 13;
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
    cout << "\t‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\n";
    cout << "\t\033[30mINMATE NAME:\033[m ";
    cin >> inmateName;
    if (prisonID == 1){
      map<string, string> tasksInfos;
      string inmateNames[INMATESNUMBER] = {inmateName, "KEV", 
                                "KELAUCE", "CARL", 
                                "CAMEO", "JACKALL", 
                                "ARNIE", "KRIMEWAVE", 
                                "DOGEKIT", "PHIL"};
      map <string, bool> prisonLocations = {{"Dining Room", 1}, {"Gymnasium", 1}, {"Exercise Room", 1}, 
                                            {"Cleaning Room", 1}, {"Laundry", 1}, {"Security Room", 0}, 
                                            {"Deposit", 1}, {"Isolation", 0}, {"Kitchen", 1}, 
                                            {"Meeting Room", 1}, {"Watch-tower", 0}, {"Pantry", 1}, {"Library", 1},
                                            {"Shower Room", 1}};

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
      centerPerks.registerDailyPrisonRoutine({0, 0, 4, 59, "Lights Out"});
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
      centerPerks.registerDailyPrisonRoutine({19, 0, 23, 59, "Lights Out"});

      centerPerks.registerRoutineToLocation("Wake Up Call, Roll Call", "Meeting Room");
      centerPerks.registerRoutineToLocation("Breakfast Time", "Dining Room");
      centerPerks.registerRoutineToLocation("Exercise Time", "Exercise Room");
      centerPerks.registerRoutineToLocation("Free Time", "");
      centerPerks.registerRoutineToLocation("Job Time", "");
      centerPerks.registerRoutineToLocation("Lunch Time", "Dining Room");
      centerPerks.registerRoutineToLocation("Roll Call", "Meeting Room");
      centerPerks.registerRoutineToLocation("Shower Time", "Shower Room");
      centerPerks.registerRoutineToLocation("Dinner Time", "Dining Room");
      centerPerks.registerRoutineToLocation("Lights Out", "");

      // CADASTRANDO OS 10 PRISIONEIROS NAS PRISÕES
      for (int i=0; i < INMATESNUMBER; i++){
          centerPerks.registerInmateInPrison(Inmate(inmateNames[i]));
      }

      // CADASTRANDO OS 10 PRISIONEIROS BOT NAS PRISÕES
      for (int i=1; i < INMATESNUMBER; i++){
          centerPerks.registerBotInmateInPrison(BotInmate(inmateNames[i]));
      }

      // CADASTRANDO OS LOCAIS NA PRISÕES
      for (auto location : prisonLocations){
          centerPerks.registerLocationInPrison(location.first, location.second);
      }

      int startHour = centerPerks.getDailyRoutineAtIndex(0).startHour;
      int startMinute = centerPerks.getDailyRoutineAtIndex(0).startMinute;
      centerPerks.startPrisonTime(Data(31, 12, 2023), startHour, startMinute);
      json centerPerksJson = centerPerks.toJson("centerPerks");
      saveConfigs(centerPerksJson);
    }else if (prisonID == 2){
      map<string, string> tasksInfos;
      string inmateNames[INMATESNUMBER] = {inmateName, "KEV", 
                                "KELAUCE", "CARL", 
                                "CAMEO", "JACKALL", 
                                "ARNIE", "KRIMEWAVE", 
                                "DOGEKIT", "PHIL"};
      map <string, bool> prisonLocations = {
                                    {"Forest Clearing", 1}, {"Wilderness Training Ground", 1}, {"Outdoor Fitness Area", 1}, 
                                    {"Rustic Workshop", 1}, {"Riverbank Laundry", 1}, {"Jungle Surveillance Center", 0}, 
                                    {"Storage Hut", 1}, {"Deep Forest Solitude", 0}, {"Canopy Kitchen", 1}, 
                                    {"Treetop Gathering Hall", 1}, {"Canopy Observation Tower", 0}, {"Jungle Supplies Depot", 1},
                                    {"Canopy Library", 1}, {"Riverbank Bathhouse", 1}
                                    };

      // CARREGANDO O ARQUIVO DE CONFIGURAÇÕES CONTENDO AS INFORMACOES DAS TASKS
      loadConfig(tasksInfos, "../utils/configs2.txt");
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

      Prison jungleCompound("Jungle Compound", 0, jobBoard, Data(31, 12, 2023));

      // REGISTRANDO CADA ROTINA NA ROTINA DIÁRIA DA PRISÃO
      // *O método registerDailyPrisonRoutine() já ordena as rotinas por horário automaticamente*
      // center perks: 
      jungleCompound.registerDailyPrisonRoutine({8, 0, 8, 59, "Morning Roll Call"});
      jungleCompound.registerDailyPrisonRoutine({9, 0, 9, 59, "Breakfast"});
      jungleCompound.registerDailyPrisonRoutine({10, 0, 12, 59, "Work Period"});
      jungleCompound.registerDailyPrisonRoutine({13, 0, 13, 59, "Mid-day Roll Call"});
      jungleCompound.registerDailyPrisonRoutine({14, 0, 15, 59, "Free Period"});
      jungleCompound.registerDailyPrisonRoutine({16, 0, 16, 59, "Dinner"});
      jungleCompound.registerDailyPrisonRoutine({17, 0, 17, 59, "Exercise Period"});
      jungleCompound.registerDailyPrisonRoutine({18, 0, 18, 59, "Shower"});
      jungleCompound.registerDailyPrisonRoutine({19, 0, 21, 59, "Free Period"});
      jungleCompound.registerDailyPrisonRoutine({22, 0, 22, 59, "Evening Roll Call"});
      jungleCompound.registerDailyPrisonRoutine({23, 0, 7, 59, "Lights Out"});

      jungleCompound.registerRoutineToLocation("Morning Roll Call", "Treetop Gathering Hall");
      jungleCompound.registerRoutineToLocation("Breakfast", "Forest Clearing");
      jungleCompound.registerRoutineToLocation("Work Period", "");
      jungleCompound.registerRoutineToLocation("Mid-day Roll Call", "Treetop Gathering Hall");
      jungleCompound.registerRoutineToLocation("Free Period", "");
      jungleCompound.registerRoutineToLocation("Dinner", "Forest Clearing");
      jungleCompound.registerRoutineToLocation("Exercise Period", "Outdoor Fitness Area");
      jungleCompound.registerRoutineToLocation("Shower", "Riverbank Bathhouse");
      jungleCompound.registerRoutineToLocation("Evening Roll Call", "Treetop Gathering Hall");
      jungleCompound.registerRoutineToLocation("Lights Out", "");

      // CADASTRANDO OS 10 PRISIONEIROS NAS PRISÕES
      for (int i=0; i < INMATESNUMBER; i++){
          jungleCompound.registerInmateInPrison(Inmate(inmateNames[i]));
      }

      // CADASTRANDO OS LOCAIS NA PRISÕES
      for (auto location : prisonLocations){
          jungleCompound.registerLocationInPrison(location.first, location.second);
      }
      int startHour = jungleCompound.getDailyRoutineAtIndex(0).startHour;
      int startMinute = jungleCompound.getDailyRoutineAtIndex(0).startMinute;
      jungleCompound.startPrisonTime(Data(31, 12, 2023), startHour, startMinute);
      json jungleCompoundJson = jungleCompound.toJson("jungleCompound");
      saveConfigs(jungleCompoundJson);
    }else if(prisonID == 3){
        map<string, string> tasksInfos;
        string inmateNames[INMATESNUMBER] = {inmateName, "KEV", 
                                    "KELAUCE", "CARL", 
                                    "CAMEO", "JACKALL", 
                                    "ARNIE", "KRIMEWAVE", 
                                    "DOGEKIT", "PHIL"};
        map <string, bool> prisonLocations = {
                                        {"Maximum Security Chow Hall", 1}, {"Ironclad Exercise Yard", 1}, {"Secure Metalshop", 1}, 
                                        {"Sanitation Chamber", 1}, {"Prison Laundry Complex", 1}, {"Surveillance Hub", 0}, 
                                        {"Contraband Vault", 1}, {"Iron Isolation Unit", 0}, {"Fortified Galley", 1}, 
                                        {"Warden's Briefing Chamber", 1}, {"Iron Watchtower", 0}, {"Ration Storage", 1},  
                                        {"Ironbound Library", 1}, {"Maximum Security Bathhouse", 1}
                                        };

        // CARREGANDO O ARQUIVO DE CONFIGURAÇÕES CONTENDO AS INFORMACOES DAS TASKS
        loadConfig(tasksInfos, "../utils/configs3.txt");
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

        Prison hmpIrongate("HMP Irongate", 0, jobBoard, Data(31, 12, 2023));

        // REGISTRANDO CADA ROTINA NA ROTINA DIÁRIA DA PRISÃO
        // *O método registerDailyPrisonRoutine() já ordena as rotinas por horário automaticamente*
        // center perks: 
        hmpIrongate.registerDailyPrisonRoutine({9, 0, 9, 59, "Morning Roll Call"});
        hmpIrongate.registerDailyPrisonRoutine({10, 0, 10, 59, "Breakfast"});
        hmpIrongate.registerDailyPrisonRoutine({11, 0, 13, 59, "Work Period"});
        hmpIrongate.registerDailyPrisonRoutine({14, 0, 14, 59, "Afternoon Roll Call"});
        hmpIrongate.registerDailyPrisonRoutine({15, 0, 15, 59, "Free Period"});
        hmpIrongate.registerDailyPrisonRoutine({16, 0, 16, 59, "Exercise Period"});
        hmpIrongate.registerDailyPrisonRoutine({17, 0, 17, 59, "Evening Meal"});
        hmpIrongate.registerDailyPrisonRoutine({18, 0, 18, 59, "Shower Block"});
        hmpIrongate.registerDailyPrisonRoutine({19, 0, 19, 59, "Evening Roll Call"});
        hmpIrongate.registerDailyPrisonRoutine({20, 0, 8, 59, "Lights Out"});

        hmpIrongate.registerRoutineToLocation("Morning Roll Call", "Warden's Briefing Chamber");
        hmpIrongate.registerRoutineToLocation("Breakfast", "Maximum Security Chow Hall");
        hmpIrongate.registerRoutineToLocation("Work Period", "");
        hmpIrongate.registerRoutineToLocation("Afternoon Roll Call", "Warden's Briefing Chamber");
        hmpIrongate.registerRoutineToLocation("Free Period", "");
        hmpIrongate.registerRoutineToLocation("Exercise Period", "Ironclad Exercise Yard");
        hmpIrongate.registerRoutineToLocation("Evening Meal", "Maximum Security Chow Hall");
        hmpIrongate.registerRoutineToLocation("Shower Block", "Maximum Security Bathhouse");
        hmpIrongate.registerRoutineToLocation("Evening Roll Call", "Warden's Briefing Chamber");
        hmpIrongate.registerRoutineToLocation("Lights Out", "");

        // CADASTRANDO OS 10 PRISIONEIROS NAS PRISÕES
        for (int i=0; i < INMATESNUMBER; i++){
            hmpIrongate.registerInmateInPrison(Inmate(inmateNames[i]));
        }

        // CADASTRANDO OS LOCAIS NA PRISÕES
        for (auto location : prisonLocations){
            hmpIrongate.registerLocationInPrison(location.first, location.second);
        }
        int startHour = hmpIrongate.getDailyRoutineAtIndex(0).startHour;
        int startMinute = hmpIrongate.getDailyRoutineAtIndex(0).startMinute;
        hmpIrongate.startPrisonTime(Data(31, 12, 2023), startHour, startMinute);
        json hmpIrongateJson = hmpIrongate.toJson("hmpIrongate");
        saveConfigs(hmpIrongateJson);
    }else{
        cout << "error creating information for prison\n";
    }
}
