#include <iostream>
using std::cout;
using std::cin;

#include "Inmate.h"
#include "JobBoard.h"
#include "Time.h"
#include "Prison.h"
#include "Data.h"
#include "util.h"

#include <map>
using std::map;

#include <vector>
using std::vector;

int main(){
    int option = -1;
    map<string, string> tasksInfos;
    string inmateNames[10] = {"KEV", "KELAUCE", "CLIVE", "CARL", "CAMEO", "JACKALL", "ARNIE", "KRIMEWAVE", "DOGEKIT", "PHIL"};
    string prisonLocations[12] = {"Dining Room", "Gymnasium", "Exercise Room", 
                                "Cleaning Room", "Laundry", "Security Room", 
                                "Deposit", "Isolation", "Kitchen", "Meeting room",
                                "Watch-tower", "Pantry"};
    // ALOCANDO 10 PRISIONEIROS E COLOCANDO ELES NO VETOR DE PONTEIROS 
    vector<Inmate *> inmates;
    for (int i=0; i<10; i++){
        inmates.push_back(new Inmate(inmateNames[i]));
    }

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
    // CRIANDO UM JOBBOARD
    JobBoard jobBoard(tasks, tasksInfos.size());

    // CRIANDO DUAS PRISOES COM O MESMO JOBBOARD
    Prison centerPerks("center perks", 0, jobBoard, Data(31, 12, 2023));
    Prison stalagFlucht("stalag flucht", jobBoard);

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
    // stalag flucht
    stalagFlucht.registerDailyPrisonRoutine({5, 0, 5, 59, "Wake Up Call, Roll Call"});
    stalagFlucht.registerDailyPrisonRoutine({6, 0, 6, 59, "Breakfast Time"});
    stalagFlucht.registerDailyPrisonRoutine({9, 0, 9, 59, "Exercise Time"});
    stalagFlucht.registerDailyPrisonRoutine({10, 0, 11, 59, "Free Time"});
    stalagFlucht.registerDailyPrisonRoutine({7, 0, 8, 59, "Job Time"}); // ROTINA INSERIDA NA ORDEM ERRADA
    stalagFlucht.registerDailyPrisonRoutine({12, 0, 12, 59, "Lunch Time"});
    stalagFlucht.registerDailyPrisonRoutine({13, 0, 13, 59, "Roll Call"});
    stalagFlucht.registerDailyPrisonRoutine({14, 0, 15, 59, "Job Time"});
    stalagFlucht.registerDailyPrisonRoutine({16, 0, 16, 59, "Shower Time"});
    stalagFlucht.registerDailyPrisonRoutine({17, 0, 17, 59, "Dinner Time"});
    stalagFlucht.registerDailyPrisonRoutine({18, 0, 18, 59, "Free Time"});

    // CADASTRANDO OS 10 PRISIONEIROS NAS PRISÕES
    for (auto inmate : inmates){
        stalagFlucht.registerInmateInPrison(*inmate);
        centerPerks.registerInmateInPrison(*inmate);
    }

    // CADASTRANDO OS LOCAIS NA PRISÕES
    for (auto location : prisonLocations){
        stalagFlucht.registerLocationInPrison(location);
        centerPerks.registerLocationInPrison(location);
    }

    cout << centerPerks;
    cout << stalagFlucht;

    while(option != 0){
        cout << "Simulando a execução do programa...\n";
        cout << "Escolha uma opção: \n";
        cout << "[0] - Sair do jogo\n";
        cout << "[1] - Exibir rotina diária da prisão\n";
        cout << "[2] - Exibir nome dos prisioneiros da prisão\n";
        cout << "[3] - Exibir todos os locais da prisão\n";
        cout << "[4] - Exibir quadro de tarefas da prisão\n";
        cout << "[5] - Exibir detalhes de uma tarefa\n";
        cout << "[6] - Iniciar tempo de center perks\n";
        cout << "[7] - Iniciar tempo de stalag flucht\n";
        cout << "[8] - Atribuir tarefas aos prisioneiros\n";
        cout << "[9] - Passar tempo\n";
        cout << "Opção: ";
        cin >> option;
        switch (option)
        {
        case 0:
            cout << "Saindo do jogo...\n";
            break;
        case 1:
            // EXIBINDO A ROTINA DIÁRIA COMPLETA DA PRISÃO
            centerPerks.displayDailyRoutine();
            break;

        case 2:
            // EXIBINDO O NOME DE TODOS OS PRISIONEIROS CADASTRADOS NA PRISÃO
            centerPerks.displayAllRegisteredInmates();
            break;

        case 3:
            // EXIBINDO TODOS OS LOCAIS DA PRISÃO
            centerPerks.displayAllPrisonLocations();
            break;

        case 4:
            // EXIBINDO O QUADRO DE TAREFAS DA PRISÃO
            centerPerks.displayPrisonJobBoard();
            break;

        case 5:
            // EXIBINDO DETALHES DE UMA TAREFA PELO ÍNDICE
            int taskOption;
            cout << "Insira o índice da tarefa: ";
            cin >> taskOption;
            centerPerks.viewPrisonTaskDetails(taskOption);
            break;

        case 6:
            centerPerks.startPrisonTime();
            break;

        case 7:
            stalagFlucht.startPrisonTime();
            break;

        case 8:
            centerPerks.assignTasksToInmates();
            break;

        case 9:
            int hour;
            int minute;
            cout << "Hora: ";
            cin >> hour;
            cout << "Minuto: ";
            cin >> minute;
            Time::skipTime(hour, minute);
            break;

        default:
            cout << "Insira uma opção válida!\n";
            break;
        }
    }

    for (int i=0; i < inmates.size(); i++){
        delete inmates[i];
    }
}