#include <iostream>
using std::cout;
using std::cin;

#include <cstdlib>
using std::system;

#include "Inmate.h"
#include "JobBoard.h"
#include "Time.h"
#include "Prison.h"
#include "Data.h"
#include "util.h"

#include <map>
using std::map;

#include <fstream>
using std::remove;

#include <vector>
using std::vector;

#include <nlohmann/json.hpp>
using json = nlohmann::json;

int main(){
    int returnSystem;
    int option = -1;
    int option2 = -1;
    int option3 = -1;
    bool hasCheckpoint = false;
    Prison *prison;
    // map<string, string> tasksInfos;
    // string inmateNames[10] = {"KEV", "KELAUCE", "CLIVE", "CARL", "CAMEO", "JACKALL", "ARNIE", "KRIMEWAVE", "DOGEKIT", "PHIL"};
    // string prisonLocations[12] = {"Dining Room", "Gymnasium", "Exercise Room", 
    //                             "Cleaning Room", "Laundry", "Security Room", 
    //                             "Deposit", "Isolation", "Kitchen", "Meeting room",
    //                             "Watch-tower", "Pantry"};
    // // ALOCANDO 10 PRISIONEIROS E COLOCANDO ELES NO VETOR DE PONTEIROS 
    // vector<Inmate *> inmates;
    // for (int i=0; i<10; i++){
    //     inmates.push_back(new Inmate(inmateNames[i]));
    //     Inmate::viewAllInmates(); // método que usa o stl Map para printar as informacoes ID e INMATE NAME
    //     cout << "\n\n";
    // }

    // // CARREGANDO O ARQUIVO DE CONFIGURAÇÕES CONTENDO AS INFORMACOES DAS TASKS
    // loadConfig(tasksInfos, "../utils/configs.txt");
    // Task tasks[tasksInfos.size()];
    // int i = 0;
    // for (auto pair : tasksInfos){
    //     tasks[i].taskName = pair.first;
    //     tasks[i].taskDetails = pair.second;
    //     tasks[i].inmate = 0;
    //     i++;
    // }
    // // CRIANDO JOBBOARD
    // JobBoard jobBoard(tasks, tasksInfos.size());
    // JobBoard jobBoardSF(jobBoard); // Usando o construtor de copia
    // cout << "jobBoardSF == jobBoard --> " << (jobBoardSF == jobBoard) << "\n";

    // // CRIANDO DUAS PRISOES COM O MESMO JOBBOARD
    // Prison stalagFlucht("stalag flucht", jobBoardSF);
    // Prison centerPerks("center perks", 0, jobBoard, Data(31, 12, 2023));

    // // REGISTRANDO CADA ROTINA NA ROTINA DIÁRIA DA PRISÃO
    // // *O método registerDailyPrisonRoutine() já ordena as rotinas por horário automaticamente*
    // // center perks: 
    // centerPerks.registerDailyPrisonRoutine({5, 0, 5, 59, "Wake Up Call, Roll Call"});
    // centerPerks.registerDailyPrisonRoutine({6, 0, 6, 59, "Breakfast Time"});
    // centerPerks.registerDailyPrisonRoutine({9, 0, 9, 59, "Exercise Time"});
    // centerPerks.registerDailyPrisonRoutine({10, 0, 11, 59, "Free Time"});
    // centerPerks.registerDailyPrisonRoutine({7, 0, 8, 59, "Job Time"}); // ROTINA INSERIDA NA ORDEM ERRADA
    // centerPerks.registerDailyPrisonRoutine({12, 0, 12, 59, "Lunch Time"});
    // centerPerks.registerDailyPrisonRoutine({13, 0, 13, 59, "Roll Call"});
    // centerPerks.registerDailyPrisonRoutine({14, 0, 15, 59, "Job Time"});
    // centerPerks.registerDailyPrisonRoutine({16, 0, 16, 59, "Shower Time"});
    // centerPerks.registerDailyPrisonRoutine({17, 0, 17, 59, "Dinner Time"});
    // centerPerks.registerDailyPrisonRoutine({18, 0, 18, 59, "Free Time"});
    // // stalag flucht
    // stalagFlucht.registerDailyPrisonRoutine({5, 0, 5, 59, "Wake Up Call, Roll Call"});
    // stalagFlucht.registerDailyPrisonRoutine({6, 0, 6, 59, "Breakfast Time"});
    // stalagFlucht.registerDailyPrisonRoutine({9, 0, 9, 59, "Exercise Time"});
    // stalagFlucht.registerDailyPrisonRoutine({10, 0, 11, 59, "Free Time"});
    // stalagFlucht.registerDailyPrisonRoutine({7, 0, 8, 59, "Job Time"}); // ROTINA INSERIDA NA ORDEM ERRADA
    // stalagFlucht.registerDailyPrisonRoutine({12, 0, 12, 59, "Lunch Time"});
    // stalagFlucht.registerDailyPrisonRoutine({13, 0, 13, 59, "Roll Call"});
    // stalagFlucht.registerDailyPrisonRoutine({14, 0, 15, 59, "Job Time"});
    // stalagFlucht.registerDailyPrisonRoutine({16, 0, 16, 59, "Shower Time"});
    // stalagFlucht.registerDailyPrisonRoutine({17, 0, 17, 59, "Dinner Time"});
    // stalagFlucht.registerDailyPrisonRoutine({18, 0, 18, 59, "Free Time"});

    // // CADASTRANDO OS 10 PRISIONEIROS NAS PRISÕES
    // for (auto inmate : inmates){
    //     stalagFlucht.registerInmateInPrison(*inmate);
    //     centerPerks.registerInmateInPrison(*inmate);
    // }

    // // CADASTRANDO OS LOCAIS NA PRISÕES
    // for (auto location : prisonLocations){
    //     stalagFlucht.registerLocationInPrison(location);
    //     centerPerks.registerLocationInPrison(location);
    // }
    // Time time_1;
    // cout << "!time_1 -->"<< !time_1 << "\n"; 
    // cout << centerPerks;
    // cout << stalagFlucht;
    // cout << "centerPerks == stalagFlucht --> ";
    // cout << (centerPerks == stalagFlucht) << "\n";
    // cout << "centerPerks != stalagFlucht --> ";
    // cout << (centerPerks != stalagFlucht) << "\n";
    // cout << "!inmates[0] --> ";
    // cout << !inmates[0] << "\n";

    /********************************************* MENU DE SELEÇÃO DA PRISÃO ****************************************/
    while(option != 0){
        option2 = -1;
        json savedPrisons = loadSaves("saves.json");            // Objeto JSON com as prisões salvas
        cout << "Simulando a execução do programa...\n";        // Animação de entrada
        showFigure("prisonsFigure.txt");                        // Imagem das prisões
        cout << "\nEscolha uma prisão [0 para sair do jogo]: ";


        cin >> option;                                          // Seleção da prisão
        switch (option)
        {
            case 0:                                             // Sai do jogo
                cout << "Saindo do jogo...\n";
                break;


            /******************************************** CENTER PERKS ********************************************/   
            case 1:                                             
                option2 = -1;
                returnSystem = system("clear");

                if (savedPrisons.dump() != "null"){                         // Varifica se existem prisões salvas
                    hasCheckpoint = false;
                    for (auto savedPrison : savedPrisons.items( )){         // Verifica se Center Perks tem checkpoint
                        if (savedPrison.key() == "centerPerks"){
                            showFigure("newGameAndContinueFigure.txt");     // Printa botões de Novo Jogo e Continuar
                            hasCheckpoint = true;
                            break;
                        }
                    }
                    if (hasCheckpoint) {    
                        /***************** MENU DE SELEÇÃO NOVO JOGO/CONTINUAR (CENTER PERKS) ********************/
                        while(option2 != 0){
                            cout << "\nEscolha uma opção [0 para voltar]: ";
                            cin >> option2;                                 // Seleção: Novo jogo Ou Continuar ou Sair
                            switch (option2)
                            {
                                case 0:                                     // Sai do menu de Center Perks
                                    if (prison != 0){
                                        delete prison;                      // Libera o ponteiro das prisões
                                        prison = 0;                         
                                    }
                                    break;

                                case 1:                                     // Inicia um novo jogo em Center Perks
                                    cout << "Iniciando novo jogo...\n";
                                    option3 = -1;                           // Seleção das opções de ação na prisão
                                    createInfos(1);                         // Cria uma prisão inicial (no arquivo saves.json)
                                    {
                                        /* abre o arquivo saves.json e cria centerPerks a partir dele */
                                        ifstream inputFile("saves.json");   
                                        
                                        if (!inputFile.is_open()) {
                                            cerr << "Erro ao abrir aquivo para leitura!" << '\n';
                                        }else{
                                            inputFile >> savedPrisons;
                                            prison = new Prison(savedPrisons["centerPerks"]);
                                            int startHour = prison->getDailyRoutineAtIndex(0).startHour;
                                            int startMinute = prison->getDailyRoutineAtIndex(0).startMinute;
                                            prison->startPrisonTime(Data(31, 12, 2023), startHour, startMinute);

                                            /**************** MENU DE SELEÇÃO DAS AÇÕES EM CENTER PERKS ***************/
                                            while(option3 != 0){
                                                cout << "\nEscolha uma opção [0 para voltar]: ";
                                                cin >> option3;
                                                switch (option3)
                                                {   
                                                    case 0:
                                                        if (prison != 0){
                                                            delete prison;
                                                            prison = 0;
                                                        };
                                                        option2 = 0;
                                                        break;
                                                    case 1:
                                                        cout << "Testando";
                                                        break;
                                                    default:
                                                        cout << "Insira uma opção válida!\n";
                                                        break;
                                                }
                                            }
                                        }
                                    }
                                    break;
                                case 2:                                         // Continua o jogo a partir do que tava salvo
                                    option3 = -1;
                                    cout << "Continuando jogo...\n";
                                    prison = new Prison(savedPrisons["centerPerks"]);
                                    prison->startPrisonTime(Data(savedPrisons["centerPerks"]["prisonTimePtr"]["startDate"]["dia"],
                                                                savedPrisons["centerPerks"]["prisonTimePtr"]["startDate"]["mes"],
                                                                savedPrisons["centerPerks"]["prisonTimePtr"]["startDate"]["ano"]),
                                                            savedPrisons["centerPerks"]["prisonTimePtr"]["startHour"],
                                                            savedPrisons["centerPerks"]["prisonTimePtr"]["startMinute"],
                                                            savedPrisons["centerPerks"]["prisonTimePtr"]["dayCounter"],
                                                            savedPrisons["centerPerks"]["prisonTimePtr"]["currentDay"]);

                                    /**************** MENU DE SELEÇÃO DAS AÇÕES EM CENTER PERKS ***************/
                                    while(option3 != 0){
                                        returnSystem = system("clear");
                                        cout << "\nEscolha uma opção [0 para voltar]: ";
                                        cin >> option3;                             // Seleção das opções de ação na prisão
                                        switch (option3)
                                        {   
                                            case 0:                                 
                                                if (prison != 0){
                                                    delete prison;
                                                    prison = 0;
                                                };
                                                option2 = 0;
                                                break;
                                            case 1:
                                                cout << "Testando";
                                                break;
                                            default:
                                                cout << "Insira uma opção válida!\n";
                                                break;
                                        }
                                    }                                                    
                                    break;
                                default:
                                    break;
                            }
                        }
                    }
                }
                /***************************** CASO NÃO TENHA CHECKPOINT PARA CENTER PERKS *******************************/
                cout << "não há jogo salvo\n";
                /********************** MENU DE SELEÇÃO NOVO JOGO/CONTINUAR (CENTER PERKS) *******************************/
                while(option2 != 0){
                    showFigure("newGameFigure.txt");                                // Printa botão New game
                    cout << "\nEscolha uma opção [0 para voltar]: ";
                    cin >> option2;                                                 // Seleção: Novo jogo ou sair
                    switch (option2)
                    {
                    case 0:
                        break;
                    case 1:
                        option3 = -1;
                        createInfos(1);                                   // Cria uma prisão inicial (no arquivo saves.json)
                        {
                            /* abre o arquivo saves.json pra leitura e cria centerPerks a partir dele */
                            ifstream inputFile("saves.json");
                            
                            if (!inputFile.is_open()) {
                                cerr << "Erro ao abrir aquivo para leitura!" << '\n';
                            }else{
                                inputFile >> savedPrisons;
                                prison = new Prison(savedPrisons["centerPerks"]);
                                int startHour = prison->getDailyRoutineAtIndex(0).startHour;
                                int startMinute = prison->getDailyRoutineAtIndex(0).startMinute;
                                prison->startPrisonTime(Data(31, 12, 2023), startHour, startMinute);
                                while(option3 != 0){
                                    returnSystem = system("clear");
                                    cout << "\nEscolha uma opção [0 para voltar]: ";
                                    cin >> option3;
                                    switch (option3)
                                    {   
                                        case 0:
                                            if (prison != 0){
                                                delete prison;
                                                prison = 0;
                                            };
                                            option2 = 0;
                                            break;
                                        case 1:
                                            cout << "Testando";
                                            break;
                                        default:
                                            cout << "Insira uma opção válida!\n";
                                            break;
                                    }
                                }
                            }
                        }
                        break;
                    default:
                        cout << "Insira uma opção válida!\n";
                        break;
                    }
                }
                break;


            /*************************************** JUNGLE COMPOUND ****************************************/                 
            case 2:
                option2 = -1;
                returnSystem = system("clear");
                if (savedPrisons.dump() != "null"){                              // Verifica se existem prisões salvas     
                    hasCheckpoint = false;
                    for (auto savedPrison : savedPrisons.items()){               // Verifica se Jungle Compound tem checkpoint
                        if (savedPrison.key() == "jungleCompound"){
                            showFigure("newGameAndContinueFigure.txt");          // Printa botões de Novo Jogo e Continuar
                            hasCheckpoint = true;
                            break;
                        }
                    }
                    if (hasCheckpoint) {    
                    /***************** MENU DE SELEÇÃO NOVO JOGO/CONTINUAR (JUNGLE COMPOUND) ********************/
                        while(option2 != 0){
                            cout << "\nEscolha uma opção [0 para voltar]: ";
                            cin >> option2;                                 // Seleção: Novo jogo ou Continuar ou Sair
                            switch (option2)    
                            {
                                case 0:                                         // Sai do menu de Jungle Compound
                                    if (prison != 0){
                                        delete prison;                          // Libera o ponteiro das prisões
                                        prison = 0; 
                                        break;
                                    }else{
                                        break;
                                    }
                                case 1:                                       // Inicia um novo jogo em Jungle Compound
                                    cout << "Iniciando novo jogo...\n";
                                    option3 = -1;                             // Seleção das opções de ação na prisão
                                    createInfos(2);                           // Cria uma prisão inicial (no arquivo saves.json)
                                    {
                                        /* abre o arquivo saves.json e cria jungleCompound a partir dele */
                                        ifstream inputFile("saves.json");
                                        
                                        if (!inputFile.is_open()) {
                                            cerr << "Erro ao abrir aquivo para leitura!" << '\n';
                                        }else{
                                            inputFile >> savedPrisons;
                                            prison = new Prison(savedPrisons["jungleCompound"]);
                                            int startHour = prison->getDailyRoutineAtIndex(0).startHour;
                                            int startMinute = prison->getDailyRoutineAtIndex(0).startMinute;
                                            prison->startPrisonTime(Data(31, 12, 2023), startHour, startMinute);
                                            /**************** MENU DE SELEÇÃO DAS AÇÕES EM JUNGLE COMPOUND ***************/
                                            while(option3 != 0){
                                                cout << "\nEscolha uma opção [0 para voltar]: ";
                                                cin >> option3;
                                                switch (option3)
                                                {   
                                                    case 0:
                                                        if (prison != 0){
                                                            delete prison;
                                                            prison = 0;
                                                        };
                                                        option2 = 0;
                                                        break;
                                                    case 1:
                                                        cout << "Testando";
                                                        break;
                                                    default:
                                                        cout << "Insira uma opção válida!\n";
                                                        break;
                                                }
                                            }
                                        }
                                    }
                                    break;
                                case 2:                                         // Continua o jogo a partir do que tava salvo
                                    option3 = -1;
                                    cout << "Continuando jogo...\n";
                                    prison = new Prison(savedPrisons["jungleCompound"]);
                                    prison->startPrisonTime(Data(savedPrisons["jungleCompound"]["prisonTimePtr"]["startDate"]["dia"],
                                                                savedPrisons["jungleCompound"]["prisonTimePtr"]["startDate"]["mes"],
                                                                savedPrisons["jungleCompound"]["prisonTimePtr"]["startDate"]["ano"]),
                                                            savedPrisons["jungleCompound"]["prisonTimePtr"]["startHour"],
                                                            savedPrisons["jungleCompound"]["prisonTimePtr"]["startMinute"],
                                                            savedPrisons["jungleCompound"]["prisonTimePtr"]["dayCounter"],
                                                            savedPrisons["jungleCompound"]["prisonTimePtr"]["currentDay"]);
                                    /**************** MENU DE SELEÇÃO DAS AÇÕES EM JUNGLE COMPOUND ***************/
                                    while(option3 != 0){
                                        returnSystem = system("clear");
                                        
                                        cout << "\nEscolha uma opção [0 para voltar]: ";
                                        cin >> option3;                               // Seleção das opções de ação na prisão
                                        switch (option3)
                                        {   
                                            case 0:
                                                if (prison != 0){
                                                    delete prison;
                                                    prison = 0;
                                                };
                                                option2 = 0;
                                                break;
                                            case 1:
                                                cout << "Testando";
                                                break;
                                            default:
                                                cout << "Insira uma opção válida!\n";
                                                break;
                                        }
                                    }                                                    
                                    break;
                                default:
                                    break;
                            }
                        }
                    }
                }
                /***************************** CASO NÃO TENHA CHECKPOINT PARA JUNGLE COMPOUND *******************************/
                cout << "não há jogo salvo\n";
                /********************** MENU DE SELEÇÃO NOVO JOGO/CONTINUAR (JUNGLE COMPOUND) *******************************/
                while(option2 != 0){
                    showFigure("newGameFigure.txt");                                        // Printa botão New game
                    cout << "\nEscolha uma opção [0 para voltar]: ";                        
                    cin >> option2;                                                         // Seleção: Novo jogo ou sair
                    switch (option2)
                    {
                    case 0:
                        break;
                    case 1:
                        option3 = -1;
                        createInfos(2);                                    // Cria uma prisão inicial (no arquivo saves.json)
                        {
                            // abre o arquivo saves.json pra leitura e cria jungleCompound a partir dele
                            ifstream inputFile("saves.json");
                            
                            if (!inputFile.is_open()) {
                                cerr << "Erro ao abrir aquivo para leitura!" << '\n';
                            }else{
                                inputFile >> savedPrisons;
                                prison = new Prison(savedPrisons["jungleCompound"]);
                                int startHour = prison->getDailyRoutineAtIndex(0).startHour;
                                int startMinute = prison->getDailyRoutineAtIndex(0).startMinute;
                                prison->startPrisonTime(Data(31, 12, 2023), startHour, startMinute);
                                while(option3 != 0){
                                    returnSystem = system("clear");
                                    cout << "\nEscolha uma opção [0 para voltar]: ";
                                    cin >> option3;
                                    switch (option3)
                                    {   
                                        case 0:
                                            if (prison != 0){
                                                delete prison;
                                                prison = 0;
                                            };
                                            option2 = 0;
                                            break;
                                        case 1:
                                            cout << "Testando";
                                            break;
                                        default:
                                            cout << "Insira uma opção válida!\n";
                                            break;
                                    }
                                }
                            }
                        }
                        break;
                    default:
                        cout << "Insira uma opção válida!\n";
                        break;
                    }
                }

                break;

            case 3:
                option2 = -1;
                returnSystem = system("clear");
                if (savedPrisons.dump() != "null"){                              // Verifica se existem prisões salvas     
                    hasCheckpoint = false;
                    for (auto savedPrison : savedPrisons.items()){               // Verifica se JUNGLE COMPOUND tem checkpoint
                        if (savedPrison.key() == "hmpIrongate"){
                            showFigure("newGameAndContinueFigure.txt");          // Printa botões de Novo Jogo e Continuar
                            hasCheckpoint = true;
                            break;
                        }
                    }
                    if (hasCheckpoint) {    
                    /***************** MENU DE SELEÇÃO NOVO JOGO/CONTINUAR (JUNGLE COMPOUND) ********************/
                        while(option2 != 0){
                            cout << "\nEscolha uma opção [0 para voltar]: ";
                            cin >> option2;                                 // Seleção: Novo jogo ou Continuar ou Sair
                            switch (option2)    
                            {
                                case 0:                                         // Sai do menu de JUNGLE COMPOUND
                                    if (prison != 0){
                                        delete prison;                          // Libera o ponteiro das prisões
                                        prison = 0; 
                                        break;
                                    }else{
                                        break;
                                    }
                                case 1:                                       // Inicia um novo jogo em JUNGLE COMPOUND
                                    cout << "Iniciando novo jogo...\n";
                                    option3 = -1;                             // Seleção das opções de ação na prisão
                                    createInfos(3);                           // Cria uma prisão inicial (no arquivo saves.json)
                                    {
                                        /* abre o arquivo saves.json e cria JUNGLE COMPOUND a partir dele */
                                        ifstream inputFile("saves.json");
                                        
                                        if (!inputFile.is_open()) {
                                            cerr << "Erro ao abrir aquivo para leitura!" << '\n';
                                        }else{
                                            inputFile >> savedPrisons;
                                            prison = new Prison(savedPrisons["hmpIrongate"]);
                                            int startHour = prison->getDailyRoutineAtIndex(0).startHour;
                                            int startMinute = prison->getDailyRoutineAtIndex(0).startMinute;
                                            prison->startPrisonTime(Data(31, 12, 2023), startHour, startMinute);
                                            /**************** MENU DE SELEÇÃO DAS AÇÕES EM JUNGLE COMPOUND ***************/
                                            while(option3 != 0){
                                                cout << "\nEscolha uma opção [0 para voltar]: ";
                                                cin >> option3;
                                                switch (option3)
                                                {   
                                                    case 0:
                                                        if (prison != 0){
                                                            delete prison;
                                                            prison = 0;
                                                        };
                                                        option2 = 0;
                                                        break;
                                                    case 1:
                                                        cout << "Testando";
                                                        break;
                                                    default:
                                                        cout << "Insira uma opção válida!\n";
                                                        break;
                                                }
                                            }
                                        }
                                    }
                                    break;
                                case 2:                                         // Continua o jogo a partir do que tava salvo
                                    option3 = -1;
                                    cout << "Continuando jogo...\n";
                                    prison = new Prison(savedPrisons["hmpIrongate"]);
                                    prison->startPrisonTime(Data(savedPrisons["hmpIrongate"]["prisonTimePtr"]["startDate"]["dia"],
                                                                savedPrisons["hmpIrongate"]["prisonTimePtr"]["startDate"]["mes"],
                                                                savedPrisons["hmpIrongate"]["prisonTimePtr"]["startDate"]["ano"]),
                                                            savedPrisons["hmpIrongate"]["prisonTimePtr"]["startHour"],
                                                            savedPrisons["hmpIrongate"]["prisonTimePtr"]["startMinute"],
                                                            savedPrisons["hmpIrongate"]["prisonTimePtr"]["dayCounter"],
                                                            savedPrisons["hmpIrongate"]["prisonTimePtr"]["currentDay"]);
                                    /**************** MENU DE SELEÇÃO DAS AÇÕES EM CENTER PERKS ***************/
                                    while(option3 != 0){
                                        returnSystem = system("clear");
                                        
                                        cout << "\nEscolha uma opção [0 para voltar]: ";
                                        cin >> option3;                               // Seleção das opções de ação na prisão
                                        switch (option3)
                                        {   
                                            case 0:
                                                if (prison != 0){
                                                    delete prison;
                                                    prison = 0;
                                                };
                                                option2 = 0;
                                                break;
                                            case 1:
                                                cout << "Testando";
                                                break;
                                            default:
                                                cout << "Insira uma opção válida!\n";
                                                break;
                                        }
                                    }                                                    
                                    break;
                                default:
                                    break;
                            }
                        }
                    }
                }
                /***************************** CASO NÃO TENHA CHECKPOINT PARA JUNGLE COMPOUND *******************************/
                cout << "não há jogo salvo\n";
                /********************** MENU DE SELEÇÃO NOVO JOGO/CONTINUAR (JUNGLE COMPOUND) *******************************/
                while(option2 != 0){
                    showFigure("newGameFigure.txt");                                        // Printa botão New game
                    cout << "\nEscolha uma opção [0 para voltar]: ";                        
                    cin >> option2;                                                         // Seleção: Novo jogo ou sair
                    switch (option2)
                    {
                    case 0:
                        break;
                    case 1:
                        option3 = -1;
                        createInfos(3);                                    // Cria uma prisão inicial (no arquivo saves.json)
                        {
                            // abre o arquivo saves.json pra leitura e cria hmpIrongate a partir dele
                            ifstream inputFile("saves.json");
                            
                            if (!inputFile.is_open()) {
                                cerr << "Erro ao abrir aquivo para leitura!" << '\n';
                            }else{
                                inputFile >> savedPrisons;
                                prison = new Prison(savedPrisons["hmpIrongate"]);
                                int startHour = prison->getDailyRoutineAtIndex(0).startHour;
                                int startMinute = prison->getDailyRoutineAtIndex(0).startMinute;
                                prison->startPrisonTime(Data(31, 12, 2023), startHour, startMinute);
                                while(option3 != 0){
                                    returnSystem = system("clear");
                                    cout << "\nEscolha uma opção [0 para voltar]: ";
                                    cin >> option3;
                                    switch (option3)
                                    {   
                                        case 0:
                                            if (prison != 0){
                                                delete prison;
                                                prison = 0;
                                            };
                                            option2 = 0;
                                            break;
                                        case 1:
                                            cout << "Testando";
                                            break;
                                        default:
                                            cout << "Insira uma opção válida!\n";
                                            break;
                                    }
                                }
                            }
                        }
                        break;
                    default:
                        cout << "Insira uma opção válida!\n";
                        break;
                    }
                }

                break;

            default:
                cout << "Insira uma opção válida!\n";
                break;
        }
    }

    // while(option != 0){
    //     cout << "Simulando a execução do programa...\n";
    //     cout << "Escolha uma opção: \n";
    //     cout << "[0] - Sair do jogo\n";
    //     cout << "[1] - Exibir rotina diária da prisão\n";
    //     cout << "[2] - Exibir nome dos prisioneiros da prisão\n";
    //     cout << "[3] - Exibir todos os locais da prisão\n";
    //     cout << "[4] - Exibir quadro de tarefas da prisão\n";
    //     cout << "[5] - Exibir detalhes de uma tarefa\n";
    //     cout << "[6] - Iniciar tempo de center perks\n";
    //     cout << "[7] - Atribuir tarefas aos prisioneiros\n";
    //     cout << "[8] - Passar tempo\n";
    //     cout << "[9] - Salvar progresso\n";
    //     cout << "[10] - Continuar de onde parou\n";
    //     cout << "Opção: ";
    //     cin >> option;
    //     switch (option)
    //     {
    //     case 0:
    //         cout << "Saindo do jogo...\n";
    //         break;
    //     case 1:
    //         // EXIBINDO A ROTINA DIÁRIA COMPLETA DA PRISÃO
    //         prisons[0]->displayDailyRoutine();
    //         break;

    //     case 2:
    //         // EXIBINDO O NOME DE TODOS OS PRISIONEIROS CADASTRADOS NA PRISÃO
    //         prisons[0]->displayAllRegisteredInmates();
    //         break;

    //     case 3:
    //         // EXIBINDO TODOS OS LOCAIS DA PRISÃO
    //         prisons[0]->displayAllPrisonLocations();
    //         break;

    //     case 4:
    //         // EXIBINDO O QUADRO DE TAREFAS DA PRISÃO
    //         prisons[0]->displayPrisonJobBoard();
    //         break;

    //     case 5:
    //         // EXIBINDO DETALHES DE UMA TAREFA PELO ÍNDICE
    //         int taskOption;
    //         cout << "Insira o índice da tarefa: ";
    //         cin >> taskOption;
    //         prisons[0]->viewPrisonTaskDetails(taskOption);
    //         break;

    //     case 6:
    //         prisons[0]->startPrisonTime(Data(savedPrisonsValues[0]["prisonTimePtr"]["startDate"]["dia"],
    //                                         savedPrisonsValues[0]["prisonTimePtr"]["startDate"]["mes"],
    //                                         savedPrisonsValues[0]["prisonTimePtr"]["startDate"]["ano"]),
    //                                     savedPrisonsValues[0]["prisonTimePtr"]["startHour"],
    //                                     savedPrisonsValues[0]["prisonTimePtr"]["startMinute"],
    //                                     savedPrisonsValues[0]["prisonTimePtr"]["dayCounter"],
    //                                     savedPrisonsValues[0]["prisonTimePtr"]["currentDay"]);
    //         break;

    //     case 7:
    //         prisons[0]->assignTasksToInmates();
    //         break;

    //     case 8:
    //         int hour;
    //         int minute;
    //         cout << "Hora: ";
    //         cin >> hour;
    //         cout << "Minuto: ";
    //         cin >> minute;
    //         Time::skipTime(hour, minute);
    //         break;

    //     case 9:
    //         saveConfigs(prisons[0]->toJson("centerPerks"));
    //         break;

    //     case 10:
    //         loadSaves("saves.json");

    //     default:
    //         cout << "Insira uma opção válida!\n";
    //         break;
    //     }
    // }
}