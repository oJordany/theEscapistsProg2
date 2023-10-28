#include <iostream>
using std::cout;
using std::cin;

#include "Inmate.h"
#include "JobBoard.h"
#include "Time.h"
#include "Prison.h"

int main(){
    int option = -1;
    // CRIANDO PONTEIRO E FAZENDO ELE APONTAR PARA UMA PRISÃO
    Prison *prisonPtr = new Prison;
    // CRIANDO 10 PRISIONEIROS E CADASTRANDO ELES NA PRISÃO 
    Inmate Kev("Kev");
    Inmate Kelauce("KELAUCE");
    Inmate Clive("CLIVE");

    Task teste[4] = {
        {"teste1", "teste1...", &Kev},
        {"teste2", "teste2...", &Kelauce},
        {"teste3", "teste3...", &Clive},
        {"teste4", "teste4...", 0},
    };
    JobBoard jb(teste, 4);
    jb.unassignTask(1);
    jb.displayTasks();
    jb.assignTaskTo(Kelauce);
    jb.displayTasks();

    Task teste2[2] = {
        {"teste1", "teste1...", &Kev},
        {"teste2", "teste2...", &Kelauce},
    };
    JobBoard jb2(teste2, 2);

    jb2.displayTasks();

    cout << jb;

    jb2 = jb;
    
    jb2.displayTasks();

    cout << "jb2 == jb : " << (jb2 == jb) << "\n"; 
    cout << "jb2 != jb : " << (jb2 != jb) << "\n"; 
    cout << "!jb2 : " << !jb2 << "\n";
    cout << "Apos zerar o jb2: \n";
    jb2.setTasksSize(0);
    cout << "jb2 == jb : " << (jb2 == jb) << "\n"; 
    cout << "jb2 != jb : " << (jb2 != jb) << "\n"; 
    cout << "!jb2 :" << !jb2 << "\n";

    cout << jb2;
    jb2.displayTasks();
    // prisonPtr->registerInmateInPrison(NICK);
    // const Inmate CAMEO("CAMEO");
    // prisonPtr->registerInmateInPrison(CAMEO);
    // const Inmate JACKALL("JACKALL");
    // prisonPtr->registerInmateInPrison(JACKALL);
    // const Inmate ARNIE("ARNIE");
    // prisonPtr->registerInmateInPrison(ARNIE);
    // const Inmate KRIMEWAVE("KRIMEWAVE");
    // prisonPtr->registerInmateInPrison(KRIMEWAVE);
    // const Inmate DOGEKIT("DOGEKIT");
    // prisonPtr->registerInmateInPrison(DOGEKIT);

    // JobBoard()

    // // REGISTRANDO CADA ROTINA NA ROTINA DIÁRIA DA PRISÃO
    // prisonPtr->registerDailyPrisonRoutine({ 8, 0, 9, 0, "Breakfast" });
    // prisonPtr->registerDailyPrisonRoutine({ 9, 0, 10, 0, "Free Period" });
    // prisonPtr->registerDailyPrisonRoutine({ 10, 0, 11, 0, "Work Period" });
    // prisonPtr->registerDailyPrisonRoutine({ 11, 0, 12, 0, "Exercise Period" });
    // prisonPtr->registerDailyPrisonRoutine({ 12, 0, 13, 0, "Lunch" }); // ROTINA INSERIDA NA ORDEM ERRADA
    // prisonPtr->registerDailyPrisonRoutine({ 13, 0, 14, 0, "Job Period" });
    // prisonPtr->registerDailyPrisonRoutine({ 14, 0, 16, 0, "Free Period" });
    // prisonPtr->registerDailyPrisonRoutine({ 16, 0, 17, 0, "Evening Meal" });
    // prisonPtr->registerDailyPrisonRoutine({ 17, 0, 18, 0, "Shower Block" });
    // prisonPtr->registerDailyPrisonRoutine({ 18, 0, 19, 0, "Free Period" });
    // prisonPtr->registerDailyPrisonRoutine({ 19, 0, 20, 0, "Evening Roll Call" });
    // prisonPtr->registerDailyPrisonRoutine({ 20, 0, 21, 0, "Evening Free Period" });
    // prisonPtr->registerDailyPrisonRoutine({ 21, 0, 22, 0, "Bedtime" });
    // prisonPtr->registerDailyPrisonRoutine({ 22, 0, 24, 0, "Lights Out" });

    prisonPtr->setLevel(3);

    // cout << "DADOS DA NOVA PRISÃO\n";
    // prisonPtr->displayDailyRoutine();
    // prisonPtr->displayAllRegisteredInmates();
    // prisonPtr->displayAllPrisonLocations();

    // // DELETANDO O PONTEIRO prisonPtr QUE ESTAVA APONTANDO PARA A PRISÃO
    // delete prisonPtr;
    // prisonPtr = 0;

    // // INSTANCIANDO A PRISÃO CENTER PERKS
    // Prison centerPerks(0);

    // // CRIANDO OUTRO OBJETO E ALOCANDO O ENDEREÇO NO PONTEIRO
    // prisonPtr = new Prison(centerPerks);

    // // CADASTRANDO OS 10 PRISIONEIROS NA NOVA PRISÃO
    // prisonPtr->registerInmateInPrison(KEV);
    // prisonPtr->registerInmateInPrison(KELAUCE);
    // prisonPtr->registerInmateInPrison(CLIVE);
    // prisonPtr->registerInmateInPrison(BURNSIDE);
    // prisonPtr->registerInmateInPrison(NICK);
    // prisonPtr->registerInmateInPrison(CAMEO);
    // prisonPtr->registerInmateInPrison(JACKALL);
    // prisonPtr->registerInmateInPrison(ARNIE);
    // prisonPtr->registerInmateInPrison(KRIMEWAVE);
    // prisonPtr->registerInmateInPrison(DOGEKIT);

    // // CADASTRANDO OS LOCAIS DA PRISÃO
    // prisonPtr->registerLocationInPrison("Dining Room");
    // prisonPtr->registerLocationInPrison("Gymnasium");
    // prisonPtr->registerLocationInPrison("Exercise Room");
    // prisonPtr->registerLocationInPrison("Cleaning Room");
    // prisonPtr->registerLocationInPrison("Laundry");
    // prisonPtr->registerLocationInPrison("Security Room");
    // prisonPtr->registerLocationInPrison("Deposit");
    // prisonPtr->registerLocationInPrison("Isolation");
    // prisonPtr->registerLocationInPrison("Kitchen");
    // prisonPtr->registerLocationInPrison("Meeting room");
    // prisonPtr->registerLocationInPrison("Watch-tower");
    // prisonPtr->registerLocationInPrison("Pantry");

    // // REGISTRANDO CADA ROTINA NA ROTINA DIÁRIA DA PRISÃO
    // // *O método registerDailyPrisonRoutine() já ordena as rotinas por horário automaticamente*
    // prisonPtr->registerDailyPrisonRoutine({5, 0, 5, 59, "Wake Up Call, Roll Call"});
    // prisonPtr->registerDailyPrisonRoutine({6, 0, 6, 59, "Breakfast Time"});
    // prisonPtr->registerDailyPrisonRoutine({9, 0, 9, 59, "Exercise Time"});
    // prisonPtr->registerDailyPrisonRoutine({10, 0, 11, 59, "Free Time"});
    // prisonPtr->registerDailyPrisonRoutine({7, 0, 8, 59, "Job Time"}); // ROTINA INSERIDA NA ORDEM ERRADA
    // prisonPtr->registerDailyPrisonRoutine({12, 0, 12, 59, "Lunch Time"});
    // prisonPtr->registerDailyPrisonRoutine({13, 0, 13, 59, "Roll Call"});
    // prisonPtr->registerDailyPrisonRoutine({14, 0, 15, 59, "Job Time"});
    // prisonPtr->registerDailyPrisonRoutine({16, 0, 16, 59, "Shower Time"});
    // prisonPtr->registerDailyPrisonRoutine({17, 0, 17, 59, "Dinner Time"});
    // prisonPtr->registerDailyPrisonRoutine({18, 0, 18, 59, "Free Time"});

    // cout << "\n\n";

    // // ADICIONANDO MAIS ESPAÇO NA ROTINA DIÁRIA USANDO O SET
    // prisonPtr->setDailyRoutineSize(12);
    // // ADICIONANDO MAIS ESPAÇO NOS PRISIONEIROS REGISTRADOS USANDO O SET
    // prisonPtr->setRegisteredInmatesSize(14);
    // // ADICIONANDO MAIS ESPAÇO NAS LOCALIZAÇÕES USANDO O SET
    // prisonPtr->setLocationsSize(27);

    // // CRIANDO UM ARRAY DE ROTINAS PARA USAR COMO PARAMETRO DO MÉTODO startTime(Routine, int) DA CLASSE Time
    // int size = prisonPtr->getNextEntrieInDailyRoutine();
    // Routine dailyRoutineCenterPerks[size];
    // for (int i=0; i < size; i++){
    //     dailyRoutineCenterPerks[i] = prisonPtr->getDailyRoutineAtIndex(i);
    // }


    // // INICIANDO O JOGO ...
    // Time::startTime(dailyRoutineCenterPerks, size);

    // // instanciando objeto time_1. 
    // // *Esse objeto é um arquivo criado que fica sendo atualizado constantemente*";
    // Time time_1;
    // while(option != 0){
    //     cout << "Simulando a execução do programa...\n";
    //     cout << "Escolha uma opção: \n";
    //     cout << "[0] - Sair do jogo\n";
    //     cout << "[1] - Exibir rotina diária da prisão\n";
    //     cout << "[2] - Exibir nome dos prisioneiros da prisão\n";
    //     cout << "[3] - Exibir todos os locais da prisão\n";
    //     cout << "Opção: ";
    //     cin >> option;
    //     switch (option)
    //     {
    //     case 0:
    //         cout << "Saindo do jogo...\n";
    //         break;
    //     case 1:
    //         // EXIBINDO A ROTINA DIÁRIA COMPLETA DA PRISÃO
    //         prisonPtr->displayDailyRoutine();
    //         break;

    //     case 2:
    //         // EXIBINDO O NOME DE TODOS OS PRISIONEIROS CADASTRADOS NA PRISÃO
    //         prisonPtr->displayAllRegisteredInmates();
    //         break;

    //     case 3:
    //         // EXIBINDO TODOS OS LOCAIS DA PRISÃO
    //         prisonPtr->displayAllPrisonLocations();
    //         break;

    //     default:
    //         cout << "Insira uma opção válida!\n";
    //         break;
    //     }
    // }
    // // usando método static void endTime() para finalizar o tempo do jogo e remover os arquivos de tempo
    // Time::endTime();
    // // DELETANDO O PONTEIRO prisonPtr QUE ESTAVA APONTANDO PARA UMA CÓPIA DE centerPerks
    // delete prisonPtr;
}