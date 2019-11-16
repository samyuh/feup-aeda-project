#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <algorithm>

#include "Menus.h"
#include "Team.h"
#include "input_utils.h"

using namespace std;
extern Team *national_team;

//Players Menu

int menu_allPlayers() {
    string toSort;
    national_team->showPlayersTable();
    cout << "To sort write \"sort [ Name | Position | Value ]\" " << endl;
    cout << "Write something else to go back!" << endl;
    getline(cin, toSort);
    if(toSort == "sort Name" || toSort == "sort name"){
        national_team->sortPlayersName();
        return 0;
    }
    if(toSort == "sort Position" || toSort == "sort position"){
        national_team->sortPlayersPosition();
        return 0;
    }
    if(toSort == "sort Value" || toSort == "sort value") {
        national_team->sortPlayersValue();
        return 0;
    }
    return 1;
}

int menu_searchPlayers() {
    char menu;

    cout << "========================================= " << endl;
    cout << "           Search Player Menu             " << endl;
    cout << "========================================= \n" << endl;

    cout << "1. Search by Name " << endl;
    cout << "2. Search by Position " << endl;
    cout << "0. Return to Player Menu " << endl << endl;

    cin.clear();
    cin >> menu;
    cin.ignore(1000,'\n');

    switch(menu) {
        case '1':
            try {
                string name;
                vector<Player *> to_print = national_team->findPlayerName(name);

                cout << "Write the name of the player you wish to find: " << endl;
                getline(cin, name);
                if (name == "0") return 0;
                for (size_t i = 0; i < to_print.size(); i++) {
                    to_print[i]->info();

                    cout << endl << "Competitions Participated: " << endl;
                    vector<Competition *> v = national_team->getCompetition();
                    for (size_t j = 0; j < v.size(); j++)
                        cout << v[j]->getCompetitionName() << endl;
                    cout << endl << "-----------------------------------" << endl << endl;
                }
            }
            catch (PersonNotFound &er) {
                cout << "Player " << er.getName() << " not found" << endl;
            }
            waitInput();
            return 0;
        case '2':
            try {
                string position;
                vector<Player *> to_print = national_team->findPlayerPos(position);
                cout << "Write the position of the Player(s) you wish to find: " << endl;
                getline(cin, position);
                if (position == "0") return 0;
                cout << endl;
                for (size_t i = 0; i < to_print.size(); i++) {
                    to_print[i]->info();

                    cout << endl << "Competitions Participated: " << endl;
                    vector<Competition *> v = national_team->getCompetition();
                    for (size_t j = 0; j < v.size(); j++)
                        cout << v[j]->getCompetitionName() << endl;
                    cout << endl << "-----------------------------------" << endl;
                }
            }
            catch (PositionNotFound &er) {
                cout << "Players for position " << er.getPosition() << " not found" << endl;
            }
            waitInput();
            return 0;
        case '0':
            return 1;
        default:
            return 0;
    }
}

int menu_addPlayer(){
    string n, c, pos;
    int wei,hei,val,earn;
    Date d;
    string checker;

    cout << "Write the name of the Player you wish to add: " << endl;
    getline(cin,n);
    cout << "Write " << n << "'s birthday " << endl;
    cin >> d;
    cout << "Write " << n << "'s club " << endl;
    getline(cin,c);
    cout << "Write " << n << "'s position " << endl;
    cin >> pos; checkPosition(pos); cin.ignore(1000,'\n');
    cout << "Write " << n << "'s weight " << endl;
    cin >> wei; failInput(wei); cin.ignore(1000,'\n');
    cout << "Write " << n << "'s height " << endl;
    cin >> hei; failInput(hei); cin.ignore(1000,'\n');
    cout << "Write " << n << "'s value " << endl;
    cin >> val; failInput(val); cin.ignore(1000,'\n');
    cout << "Write " << n << "'s earnings " << endl;
    cin >> earn; failInput(earn);


    PlayerStatistics *stats_virtual;
    if (pos == "Goalkeeper") {

        GoalkeeperStatistics *s = new GoalkeeperStatistics();
        stats_virtual= s;
    }
    else if (pos == "Defender") {
        DefenderStatistics *s = new DefenderStatistics();
        stats_virtual = s;
    }
    else if (pos == "Midfielder") {
        MidfielderStatistics *s = new MidfielderStatistics();
        stats_virtual = s;
    }
    else if (pos == "Forward") {
        ForwardStatistics *s = new ForwardStatistics();
        stats_virtual = s;
    }

    Player *play = new Player(n,d,c,pos,wei,hei,val,earn, stats_virtual);

    cout << "Do you wish to add " << n << " as a Player?" << endl;
    cout << "1. Add Player " << endl;
    cout << "Any other key cancel adding player " << endl;
    cin.ignore(1000,'\n');
    getline(cin,checker);
    if (checker != "1") {
        cout << "Player was not added!" << endl;
    }
    else{
        national_team->addPlayer(play);
        cout << "Player successfully added!!" << endl;
    }
}

int menu_updatePlayers(){
    unsigned int index;
    vector<Player*> v_players;

    national_team->showPlayersTable();
    cout << "Write the index of the Player you wish to update." << endl;
    cout << "Press [a] or other letter to exit." << endl;

    while (cin >> index && !cin.eof()) {
        v_players = national_team->getPlayers();
        if (index >= v_players.size()) {
            cout << "Invalid index." << endl;
            continue;
        }
        else {
            Player * player = v_players[index];
            string name = player->getName();
            string new_name;
            string club, position;
            Date birthday;
            int weight, height, value;
            double earnings;
            PlayerStatistics *stats = player->getStatistics();
            char n;
            cout << "Which field you want to change in player " << name << endl;
            cout << "Select the correspondent index: " << endl;
            cout << "1. Change name" << endl;
            cout << "2. Change birthday" << endl;
            cout << "3. Change club" << endl;
            cout << "4. Change position" << endl;
            cout << "5. Change weight" << endl;
            cout << "6. Change height" << endl;
            cout << "7. Change value" << endl;
            cout << "8. Change earnings" << endl;
            cout << "9. Change statistics" << endl;

            cin >> n;

            switch(n){
                case '1':
                    cin.ignore(1000, '\n');
                    cout << name << "'s new Name: " << endl;
                    getline(cin, new_name);
                    for (size_t i = 0; i < v_players.size(); i++)
                        if (v_players[i]->getName() == new_name) throw PersonAlreadyExists(new_name);
                    player->setName(new_name);
                    break;
                case '2':
                    cout << name << "'s new birthday " << endl;
                    cin >> birthday;
                    player->setBirthday(birthday);
                    break;
                case '3':
                    cin.ignore(1000, '\n');
                    cout << name << "'s new club " << endl;
                    getline(cin, club);
                    player->setClub(club);
                    break;
                case '4':
                    cout << name << "'s new position " << endl;
                    cin >> position;
                    checkPosition(position);
                    player->setPosition(position);
                    break;
                case '5':
                    cout << name << "'s new weight " << endl;
                    cin >> weight;
                    failInput(weight);
                    player->setWeight(weight);
                    cin.clear();
                    cin.ignore(1000, '\n');
                    break;
                case '6':
                    cout << name << "'s new height " << endl;
                    cin >> height;
                    failInput(height);
                    player->setHeight(height);
                    cin.clear();
                    cin.ignore(1000, '\n');
                    break;
                case '7':
                    cout << name << "'s new value " << endl;
                    cin >> value;
                    failInput(value);
                    player->setValue(value);
                    cin.clear();
                    cin.ignore(1000, '\n');
                    break;
                case '8':
                    cout << name << "'s new earnings " << endl;
                    cin >> earnings;
                    failInput(earnings);
                    player->setEarnings(earnings);
                    cin.clear();
                    cin.ignore(1000, '\n');
                    break;
                case '9':
                    cin >> stats;
                    break;
                default:
                    cout << "Invalid index" << endl;
                    break;
            }
            cout << "Write the index of another player you wish to update." << endl;
            cout << "Press [a] or other letter to exit." << endl;
        }
    }
    cout << "Stopped updating Players!" << endl;
    cin.clear();
    cin.ignore(1000, '\n');
    return 1;
}


int menu_removePlayer() {
    unsigned int index;
    vector<Player*> v_players;
    national_team->showPlayersTable();
    cout << "Write the index of the Player you wish to remove " << endl;
    cout << "Press [a] or other letter to exit." << endl;

    while(cin >> index && !cin.eof()){
        v_players = national_team->getPlayers();
        if (index >= v_players.size()) {
            cout << "Index too high!!" << endl;
            continue;
        }
        else {
            string name = v_players[index]->getName();
            national_team->removePlayer(v_players[index]);
            national_team->showPlayersTable();
            cout << name << " was successfully removed!!" << endl;
            cout << "Press [a] or other letter to exit." << endl;
        }
    }
    cout << "Stopped removing Players!!" << endl;
    cin.clear();
    cin.ignore(1000,'\n');
    waitInput();
    return 1;
}

int menu_players()
{
    char menu;


    //cout << string(50, '\n');  //Clear Screen that works on linux(more portable)
    cout << "========================================= " << endl;
    cout << "               Player Menu                " << endl;
    cout << "========================================= \n" << endl;

    cout << "1. View all players" << endl;
    cout << "2. Search Players " << endl;
    cout << "3. Add Player " << endl;
    cout << "4. Update Player " << endl;
    cout << "5. Remove Player " << endl;
    cout << "0. Return to Main Menu " << endl << endl;

    cin.clear();
    cin >> menu;
    cin.ignore(1000,'\n');

    switch(menu)
    {
        case '1':
            while(!menu_allPlayers());
            return 0;
        case '2':
            while(!menu_searchPlayers());
            return 0;
        case '3':
            try {
                while(!menu_addPlayer());
            }
            catch(PersonAlreadyExists &er) {
                cout << "Player " << er.getName() << " already exists" << endl;
            }
            catch(CantUseThatName &er){
                cout << "Can't use " << er.getName() << " has a name" << endl;
            }
            waitInput();
            return 0;
        case '4':
            try {
                while(!menu_updatePlayers());
                }
            catch (PersonAlreadyExists &er) {
                cout << "Player named " << er.getName() << " already exists!" << endl;
                }
            waitInput();
            return 0;
        case '5':
            while(!menu_removePlayer());
            return 0;
        case '0':
            return 1;
        default:     //Invalid input
            return 0;
    }
}

// Staff

int menu_allStaff() {
    string toSort;
    national_team->showStaffTable();
    cout << "To sort write \"sort [ Name | Function ]\" " << endl;
    cout << "Write something else to go back!" << endl;
    getline(cin, toSort);
    if(toSort == "sort Name" || toSort == "sort name"){
        national_team->sortStaffName();
        return 0;
    }
    if(toSort == "sort Function" || toSort == "sort function") {
        national_team->sortStaffFunction();
        return 0;
    }
    return 1;
}

int menu_searchStaffMembers(){
    char menu;

    cout << "========================================= " << endl;
    cout << "           Search Staff Menu              " << endl;
    cout << "========================================= \n" << endl;

    cout << "1. Search by Name " << endl;
    cout << "2. Search by Staff Function " << endl;
    cout << "0. Return to Staff Menu " << endl << endl;

    cin.clear();
    cin >> menu;
    cin.ignore(1000,'\n');

    switch(menu){
        case '1':
            cout << "   Write the name of the Staff you want to search: " << endl;
            cout << "0. Return to Staff Menu" << endl << endl;

            try {
                string name;
                getline(cin, name);
                if(name == "0") return 0;

                vector<Staff *> to_print = national_team->findStaffName(name);
                for (size_t i = 0; i < to_print.size(); i++) {
                    to_print[i]->info();
                    cout << endl;
                }
            }
            catch(PersonNotFound & er) {
                cout << "Staff member " << er.getName() << " not found" << endl;
            }
            waitInput();
            return 0;
        case '2':
            cout << "Write the function of the Staff you want to search: " << endl;
            cout << "0. Return to Staff Menu" << endl;
            try {
                string function;
                getline(cin, function);
                if(function == "0") return 0;

                vector<Staff *> to_print = national_team->findStaffFunction(function);
                for (size_t i = 0; i < to_print.size(); i++) {
                    to_print[i]->info();
                    cout << endl;
                }
            }
            catch(FunctionNotFound & er) {
                cout << "No Staff members for function " << er.getFunction() << endl;
            }
            waitInput();
            return 0;
        case '0':
            return 1;
        default:
            return 0;
    }
}

int menu_addStaff() {
    string n, f, checker;
    double w;
    Date d;

    cout << "Write the name of the Staff Member you wish to add: " << endl;
    getline(cin, n);
    cout << "Write " << n << "'s birthday " << endl;
    cin >> d;
    cout << "Write " << n << "'s wage " << endl;
    cin >> w; failInput(w); cin.ignore(1000,'\n');

    cout << "Write " << n << "'s function " << endl;
    cin >> f;
    failInput(f);

    Staff *s = new Staff(n, d, w, f);

    cout << "Do you wish to add the Staff Member you have created?: " << endl;
    cout << "1. Add Staff Member " << endl;
    cout << "Any other key. Cancel adding Staff Member " << endl;
    cin.ignore(1000,'\n');
    getline(cin,checker);
    if (checker != "1"){
        cout << "Staff Member was not added!!" << endl;
    }
    else{
        national_team->addStaff(s);
        cout << n << " was successfully added as a Staff member!!" << endl;
    }
    return 1;
}

int menu_updateStaff(){
    unsigned int index;
    national_team->showStaffTable();
    vector<Staff*> v_staff = national_team->getStaff();

    cout << "Write the index of the Staff Member you wish to update." << endl;
    cout << "Press [a] or other letter to exit." << endl;

    while (cin >> index && !cin.eof()) {
        v_staff = national_team->getStaff();
        if (index >= v_staff.size()) {
            cout << "Invalid index" << endl;
            continue;
        } else {
            Staff *staff = v_staff[index];
            string name = staff->getName();
            string new_name;
            string function;
            Date birthday;
            double salary;
            char n;
            cout << "Which field you want to change in staff member " << name << endl;
            cout << "Select the correspondent index: " << endl;
            cout << "1. Change name" << endl;
            cout << "2. Change birthday" << endl;
            cout << "3. Change function" << endl;
            cout << "4. Change salary" << endl;

            cin >> n;

            switch(n) {
                case '1':
                    cin.ignore(1000, '\n');
                    cout << name << "'s new Name: " << endl;
                    getline(cin, new_name);
                    for (auto it = v_staff.begin(); it != v_staff.end(); it++) {
                        if ((*it)->getName() == new_name) throw PersonAlreadyExists(new_name);
                    }
                    staff->setName(new_name);
                    break;
                case '2':
                    cout << name << "'s new birthday " << endl;
                    cin >> birthday;
                    staff->setBirthday(birthday);
                    break;
                case '3':
                    cout << name << "'s new function " << endl;
                    cin >> function;
                    staff->setFunction(function);
                    break;
                case '4':
                    cout << name << "'s new salary " << endl;
                    cin >> salary;
                    failInput(salary);
                    staff->setSalary(salary);
                    break;
                default:
                    cout << "Invalid index" << endl;
                    break;
            }
            national_team->showStaffTable();
            cout << "Write the index of another Player you wish to update." << endl;
            cout << "Press [a] or other letter to exit." << endl;
        }
    }
    cout << "Stopped updating Staff Members!!" << endl;
    cin.clear();
    cin.ignore(1000,'\n');

}

int menu_removeStaff() {
    unsigned int index;
    vector<Staff*> v_staff;
    national_team->showStaffTable();

    cout << "Write the index of the Staff Member you wish to remove " << endl;
    cout << "Press [a] or other letter to exit." << endl;

    while(cin >> index && !cin.eof()){
        v_staff = national_team->getStaff();
        if (index >= v_staff.size()) {
            cout << "Invalid index" << endl;
            continue;
        }
        else {
            string name = v_staff[index]->getName();
            national_team->removeStaff(v_staff[index]);
            national_team->showStaffTable();
            cout << name << " was successfully removed!!" << endl;
            cout << "Press [a] or other letter to exit." << endl;
        }
    }
    cout << "Stopped removing Staff Members!!" << endl;
    cin.clear();
    cin.ignore(1000,'\n');
    waitInput();
    return 1;
}

int menu_staff() {
    char menu;

    cout << "========================================= " << endl;
    cout << "               Staff Menu                 " << endl;
    cout << "========================================= \n" << endl;

    cout << "1. View all Staff Members " << endl;
    cout << "2. Search Staff Members " << endl;
    cout << "3. Add Staff Members " << endl;
    cout << "4. Update Staff Members " << endl;
    cout << "5. Remove Staff Members " << endl;
    cout << "0. Return to Main Menu " << endl << endl;

    cin.clear();
    cin >> menu;
    cin.ignore(1000,'\n');

    switch(menu)
    {
        case '1':    //View player info
            while(!menu_allStaff());
            return 0;
        case '2':
            while(!menu_searchStaffMembers());
            return 0;
        case '3':
            try {
                while(!menu_addStaff());
            }
            catch (PersonAlreadyExists &er) {
                cout << "Staff Member named " << er.getName() << " already exists!!" << endl;
            }
            catch (CantUseThatName &er) {
                cout << "Can't use " << er.getName() << " has a name!!" << endl;
            }
            waitInput();
            return 0;
        case '4':
            try {
                while(!menu_updateStaff());
            }
            catch (PersonAlreadyExists & er){
                cout << "There already is a Staff Member named " << er.getName() << endl;
            }
            waitInput();
            return 0;
        case '5':
            while(!menu_removeStaff());
            return 0;
        case '0':    //Exit function
            return 1;
        default:     //Invalid input
            return 0;
    }
}

//Competition!

int menu_searchGame() {
    cout << "Write the name of the opponent: " << endl;
    string opponent;
    Date d;
    getline(cin, opponent);
    cout << "Write the Date of Game: " << endl;
    cin >> d;

    vector<Game *> all_games = national_team->getGames();
    for(size_t i = 0; i < all_games.size(); i++) {
        if(all_games[i]->getOpponent() == opponent && all_games[i]->getDate().isEqualTo(d)){
            all_games[i]->info();
            waitInput();
            return 1;
        }
    }
    throw (GameNotFound(opponent, d));
}

int menu_games(){
    char menu;
    vector<Game *> print_it = national_team->getGames(); // Vector to show all games! Can't be initialized in switch case
    //cout << string(50, '\n');  //Clear Screen that works on linux(more portable)

    cout << "========================================= " << endl;
    cout << "             Games Menu                   " << endl;
    cout << "========================================= \n" << endl;

    cout << "1. Show all games " << endl;
    cout << "2. Search a Game" << endl;
    cout << "0. Return to Main Menu " << endl << endl;

    cin.clear();
    cin >> menu;
    cin.ignore(1000,'\n');


    switch(menu) {
        case '1':
            for(size_t i = 0; i < print_it.size(); i++){
                print_it[i]->info();
                cout << endl;
            }
            waitInput();
            return 0;
        case '2':
            try {
                while(!menu_searchGame());
            }
            catch(GameNotFound & er) {
                cout << endl;
                cout << "Game:" << endl;
                cout << "Opponent: " << er.getOpponent() << endl;
                cout << "Date: " << er.getDate() << endl;
                cout << "This Game wasn't found" << endl;
            }
            waitInput();
            return 0;
        case '0':
            return 1;
        default:     //Invalid input
            return 0;
    }
}

int menu_payCompetitions(){
    try {
        cout << "National Football Team Competitions" << endl;
        for(int i = 0; i < (national_team->getCompetition()).size(); i++){
            cout << i << ". " << national_team->getCompetition()[i]->getCompetitionName();
            if (national_team->getCompetition()[i]->getPaid())
                cout << " - Paid!" << endl;
            else cout << " - Not paid!" << endl;
        }
        int index;
        cout << "Choose one competition to pay" << endl;
        cout << "Press [a] or other letter to exit." << endl;
        while (cin >> index && !cin.eof()) {
            if(index >= national_team->getCompetition().size()) {
                cout << "Invalid index" << endl;
                continue;
            }
            else {
                national_team->getCompetition()[index]->payPlayers();
                cout << "Competition successfully paid!" << endl;
            }
        }
        cin.clear();
        cin.ignore(1000, '\n');
        return 1;
    }
    catch(AlreadyPaid &er) {
        cout << "The " << er.getName() << " has already been paid to players." << endl;
        return 1;
    }
}

int menu_competitionGames(Competition * comp){
    char menu;
    unsigned int index;
    vector<Game *> v_games = comp->getGames();
    cout << "========================================= " << endl;
    cout << "             Games Menu                   " << endl;
    cout << "========================================= \n" << endl;

    cout << "1. Show all games from this competition" << endl;
    cout << "2. Search a Game" << endl;
    cout << "3. Add a Game" << endl;
    cout << "4. Update a Game " << endl;
    cout << "5. Remove a Game " << endl;
    cout << "0. Return to Main Menu " << endl << endl;

    cin.clear();
    cin >> menu;
    cin.ignore(1000,'\n');

    switch(menu) {
        case '1':
            comp->showGames();
            waitInput();
            return 0;
        case '2':
            try {
                cout << "Write the name of the Game's Opponent: " << endl;
                string opponent;
                Date d;
                getline(cin, opponent);
                cout << "Write the Date of Game: " << endl;
                cin >> d;
                comp->findGame(opponent, d)->info();
            }
            catch(GameNotFound &er) {
                cout << endl;
                cout << "Game:" << endl;
                cout << "Opponent: " << er.getOpponent() << endl;
                cout << "Date: " << er.getDate() << endl;
                cout << "This Game wasn't found" << endl;
            }
            waitInput();
            return 0;
        case '3':
            try{
                string country,city,stadium,opponent,checker;
                Date d;
                Statistics stats;

                cout << "Write the Game's opponent " << endl;
                getline(cin,opponent);
                cout << "Write the Game's country " << endl;
                getline(cin,country);
                cout << "Write the Game's city " << endl;
                getline(cin,city);
                cout << "Write the Game's stadium " << endl;
                getline(cin,stadium);
                cout << "Write the Game's date " << endl;
                cin >> d;
                Game *game = new Game(opponent,country,city,stadium, d, comp->getCalled(), stats);
                game->info();

                cout << "Do you wish to add this game? " << endl;
                cout << "1. Add Game " << endl;
                cout << "Any other key. Cancel adding Game " << endl;
                getline(cin,checker);
                if (checker != "1"){
                    cout << "Game was not added!" << endl;
                }
                else{

                    comp->addGame(game);
                    cout << "Game successfully added!!" << endl;
                }
            }
            catch(GameAlreadyExists &er){
                cout << endl;
                cout << "Game:" << endl;
                cout << "Opponent: " << er.getOpponent() << endl;
                cout << "Country: " << er.getCountry() << endl;
                cout << "City: " << er.getCity() << endl;
                cout << "Stadium: " << er.getStadium() << endl;
                cout << "Date: " << er.getDate() << endl;
                cout << "This Game already exists!!" << endl;
            }
            waitInput();
            return 0;
        case '4':
            try{
                for(size_t i = 0; i < v_games.size(); i++){
                    cout << "Game number: " << i << endl;
                    cout << "Opponent " << v_games[i]->getOpponent() << endl;
                    cout << "Date: " << v_games[i]->getDate() << endl << endl;
                }

                cout << "Write the number of the Game you wish to update " << endl;
                cout << "Press [a] or other letter to exit." << endl;

                while(cin >> index && !cin.eof()){

                    if (index >= v_games.size()) {
                        cout << "Index too high!!" << endl;
                        continue;
                    }
                    else {
                        v_games = comp->getGames();
                        Game* game = v_games[index];
                        int goalS, goalsC, shots, ballP, yellowC, redC, injured, freeKicks, cornerKicks;
                        string country,city,stadium,opponent, checker;
                        Date d;
                        Statistics stats;

                        char n;
                        cout << "Which field you want to change in this game? " << endl;
                        cout << "Select the correspondent index: " << endl;
                        cout << "1 -> Change opponent" << endl;
                        cout << "2 -> Change country" << endl;
                        cout << "3 -> Change city" << endl;
                        cout << "4 -> Change stadium" << endl;
                        cout << "5 -> Change date" << endl;
                        cout << "6 -> Change Statistics" << endl;

                        cin >> n;
                        switch(n) {
                            case '1':
                                cin.ignore(1000, '\n');
                                cout << "Write the Game's opponent " << endl;
                                getline(cin, opponent);
                                game->setOpponent(opponent);
                                break;
                            case '2':
                                cin.ignore(1000, '\n');
                                cout << "Write the Game's country " << endl;
                                getline(cin, country);
                                game->setCountry(country);
                                break;
                            case '3':
                                cin.ignore(1000, '\n');
                                cout << "Write the Game's city " << endl;
                                getline(cin, city);
                                game->setCity(city);
                                break;
                            case '4':
                                cin.ignore(1000, '\n');
                                cout << "Write the Game's stadium " << endl;
                                getline(cin, stadium);
                                game->setStadium(stadium);
                                break;
                            case '5':
                                cout << "Write the Game's date " << endl;
                                cin >> d;
                                game->setGameDate(d);
                                break;
                            case '6':
                                cout << "Number of goals scored: " << endl;
                                cin >> goalS; failInput(goalS); cin.ignore(1000,'\n');
                                stats.setGoalsScored(goalS);
                                cout << "Number of goals conceded: " <<  endl;
                                cin >> goalsC;failInput(goalsC); cin.ignore(1000,'\n');
                                stats.setGoalsConceded(goalsC);
                                cout << "Number of shots: " <<endl;
                                cin >> shots;failInput(shots); cin.ignore(1000,'\n');
                                stats.setShots(shots);
                                cout << "Percentage of ball possession: "  << endl;
                                cin >> ballP;failInput(ballP); cin.ignore(1000,'\n');
                                stats.setBallPossession(ballP);
                                cout << "Number of yellow cards: "  << endl;
                                cin >> yellowC;failInput(yellowC); cin.ignore(1000,'\n');
                                stats.setYellowCards(yellowC);
                                cout << "Number of red cards: "  << endl;
                                cin >> redC;failInput(redC); cin.ignore(1000,'\n');
                                stats.setRedCards(redC);
                                cout << "Number of Injured players: " << endl;
                                cin >> injured;failInput(injured); cin.ignore(1000,'\n');
                                stats.setInjured(injured);
                                cout << "Number of free kicks: "  << endl;
                                cin >> freeKicks;failInput(freeKicks); cin.ignore(1000,'\n');
                                stats.setFreeKicks(freeKicks);
                                cout << "Number of corner kicks: " << endl;
                                cin >> cornerKicks;failInput(cornerKicks);  cin.ignore(1000,'\n');
                                stats.setCornerKicks(cornerKicks);
                                game->setStats(stats);
                                break;
                            default:
                                cout << "Invalid index" << endl;
                                break;
                        }
                        cout << "Game was successfully updated!!" << endl;
                        cout << "Press [a] or other letter to exit." << endl;
                    }
                }
                cout << "Stopped updating Games!!" << endl;
                cin.clear();
                cin.ignore(1000,'\n');
            }
            catch(GameAlreadyExists &er){
                cout << endl;
                cout << "Game:" << endl;
                cout << "Opponent: " << er.getOpponent() << endl;
                cout << "Country: " << er.getCountry() << endl;
                cout << "City: " << er.getCity() << endl;
                cout << "Stadium: " << er.getStadium() << endl;
                cout << "Date: " << er.getDate() << endl;
                cout << "This Game already exists!!" << endl;
            }
            waitInput();
            return 0;
        case '5':
            //É preciso meter os jogos numa tabela com Oponentes , Date e indexs
            //comp->showGamesTable();
            for(size_t i = 0; i < v_games.size(); i++){
                cout << "Game number: " << i << endl;
                cout << "Opponent " << v_games[i]->getOpponent() << endl;
                cout << "Date: " << v_games[i]->getDate() << endl << endl;
            }

            cout << "Write the index of the Game you wish to remove " << endl;
            cout << "Press [a] or other letter to exit." << endl;

            while(cin >> index && !cin.eof()){

                if (index >= v_games.size()) {
                    cout << "Index too high!!" << endl;
                    continue;
                }
                else {
                    string opponent = v_games[index]->getOpponent();
                    comp->removeGame(v_games[index]);
                    v_games = comp->getGames();
                    //comp->showGamesTable();
                    for(size_t i = 0; i < v_games.size(); i++){
                        cout << "Game number: " << i << endl;
                        cout << "Opponent " << v_games[i]->getOpponent() << endl;
                        cout << "Date: " << v_games[i]->getDate() << endl << endl;
                    }
                    cout << "Game vs " << opponent << " was successfully removed!!" << endl;
                    cout << "Press [a] or other letter to exit." << endl;
                }
            }
            cout << "Stopped removing Games!!" << endl;
            cin.clear();
            cin.ignore(1000,'\n');
            waitInput();
            return 0;
        case '0':
            return 1;
        default:     //Invalid input
            return 0;
    }

}

int menu_calledCompetition(Competition* comp){
    map<Player *, int> m = comp->getCalledInjured();
    cout << setw(19) << "Name" << " | " << setw(10) << "Birthday" <<" | ";
    cout << setw(12) << "Club" << " | " << setw(10) << "Position" << " | " << setw(6) << "Weight" << " | ";
    cout << setw(8) << "Height" << " | " << setw(7) << "Value" << " | " << setw(9) <<  "Earnings" << " | ";
    cout << setw(12) << "Days Injured" << " |" << endl;

    for(auto it : m) {
        (it.first)->infoTable();
        cout << setw(13) << (it.second) << " |" <<  endl;
    }
    waitInput();
    return 1;
}

int menu_detailedCompetition(Competition * comp){
    char menu;
    cout << "========================================= " << endl;
    cout << "            Competition Menu              " << endl;
    cout << "========================================= " << endl;
    cout << "This menu is about the Competition:" << endl;
    cout << comp->getCompetitionName() << endl << endl;
    cout << "1. Competition Games" << endl;
    cout << "2. View called Players" << endl;
    cout << "3. Money spent in this competition (Excluding Staff Members Salary)" << endl;
    cout << "0. Return to the previous Competition Menu " << endl << endl;

    cin.clear();
    cin >> menu;
    cin.ignore(1000,'\n');
    switch(menu){
        case '1':
            while(!menu_competitionGames(comp));
            return 0;
        case '2':
            while(!menu_calledCompetition(comp));
            return 0;
        case '3':
            cout << "Number of days of this competition: " << comp->getStartDate().daysUntil(comp->getEndDate()) << endl;
            cout << "Money spent in Accommodation:  " << comp->getMoneyAccommodation() << endl;
            cout << "Paid to players as Insurances: " << comp->getMoneyInsurance() << endl;
            cout << endl;
            waitInput();
            return 0;
        case '0':    //Exit function
            return 1;
        default:     //Invalid input
            return 0;
    }
}

int menu_chooseCompetition() {
    vector<Competition*> comp = national_team->getCompetition();
    unsigned int index;
    cout << "Write the number of the Competition you wish to view" << endl;
    cout << "Press [a] or other letter to exit." << endl;

    for(size_t i = 0; i < comp.size(); i++)
        cout << i << ". " <<comp[i]->getCompetitionName() << endl;

    while(cin >> index && !cin.eof()){
        if(index >= comp.size())
            cout << "Invalid index" << endl;
        else{
            while(!menu_detailedCompetition(comp[index]));
            return 1;
        }
    }
    cin.clear();
    cin.ignore(1000, '\n');
    return 1;
}

int menu_creatCompetition() {
    int index;
    string name, players, checker;
    Date start, end;
    map<Player*, int> m_players;
    vector<Player*> team_players = national_team->getPlayers();
    vector<int> v_index;
    double acc;
    size_t n = team_players.size();
    cout << "Write the Competition's name: " << endl;
    getline(cin,name);
    cout << "Write " << name << "'s beginning date: " << endl;
    cin >> start;
    cout << "Write " << name << "'s ending date: " << endl;
    cin >> end;

    while (start.isAfter(end)){
        cout << "Date of end is before of date of start! ";
        cin >> end;
    }
    cout << endl;
    cout << "Write the money for accommodation: " << endl;
    cin >> acc; failInput(acc);
    cin.ignore(1000,'\n');
    national_team->showPlayersTable();
    cout << endl;

    cout << "Write the index of the player you wish to add" << endl;
    cout << "Press [a] or other letter to exit." << endl;

    while(cin >> index && !cin.eof()) {
        if (index >= n) {
            cout << "Index too high!!" << endl;
            continue;
        } else if (find(v_index.begin(), v_index.end(), index) != v_index.end()) {
            cout << team_players[index]->getName() << " was already added" << endl;
            continue;
        } else {
            m_players.insert(pair<Player *, int>(team_players[index], 0));
            v_index.push_back(index);
            cout << team_players[index]->getName() << " was successfully added" << endl;
        }
    }
    cin.clear();
    cin.ignore(1000,'\n');
    cout << "Add games in Competitions Menu." << endl << endl;
    cout << "Are you sure you want to add this competition?" << endl;
    cout << "1. Add the competition: " << name << endl;
    cout << "   Any other key to go back without adding the competition." << endl;

    getline(cin,checker);
    if(checker != "1")
        cout << name << " was not added" << endl;
    else {
        cout << "Competition " <<name << " was added" << endl;
        Competition * comp = new Competition(name, m_players, start, end, acc);
        national_team->addCompetition(comp);
    }
    return 1;
}

int menu_updateCompetition() {
    vector<Competition*> comp = national_team->getCompetition();
    int index;
    cout << "Write the number of the Competition you wish to update " << endl;
    cout << "Press [a] or other letter to exit." << endl;

    for (size_t i = 0; i < comp.size(); i++){
        cout << "Competition number: " << i << " " << comp[i]->getCompetitionName() << endl;
    }

    while(cin >> index && !cin.eof()){
        if (index >= comp.size()) {
            cout << "Invalid index" << endl;
            continue;
        }
        else {
            string players, checker;
            Date start,end;
            map<Player*, int> m_players;
            vector<Player*> team_players = national_team->getPlayers();
            vector<int> v_index;
            size_t num = team_players.size();
            Competition * co = comp[index];
            string name = co->getCompetitionName();
            string new_name;
            int money;
            cin.ignore(1000,'\n');
            int n, nt;
            int n_switches;
            cout << "Which field you want to change in this competition: " << name << endl;
            cout << "Select the correspondent index: " << endl;
            cout << "1. Change competition name" << endl;
            cout << "2. Change date" << endl;
            cout << "3. Change money paid for accommodation" << endl;
            cout << "4. Change called players" << endl;
            cout << "5. Update player injuries" << endl;
            cout << "Press [a] or other letter to exit." << endl;

            while(cin >> n_switches && !cin.eof()){
                map<Player *, int> m_player = co->getCalledInjured();
                vector<Player *> v_player = co->getCalled();
                if(n_switches >= 6){
                    cout << "Invalid index, please try again!!" << endl;
                }
                else{
                    string message;
                    switch(n_switches) {
                        case 1:
                            cout << "Write the Competition's name: " << endl;
                            cin.ignore(1000, '\n');
                            getline(cin, new_name);
                            co->setName(new_name);
                            message = "Name successfully changed!!";
                            break;
                        case 2:
                            cout << "Write " << name << "'s beginning date: " << endl;
                            cin >> start;
                            cout << "Write " << name << "'s ending date: " << endl;
                            cin >> end;
                            while (start.isAfter(end)){
                                cout << "Date of end is before of date of start! ";
                                cin >> end;
                            }
                            co->setStart(start);
                            co->setEnd(end);
                            message = "Dates successfully changed";
                            break;
                        case 3:
                            cout << "Write " << name << "'s money for accommodation: " << endl;
                            cin >> money; failInput(money); cin.ignore(1000,'\n');
                            co->setMoneyAccommodation(money);
                            message = "Money accommodation successfully changed";
                            break;
                        case 4:
                            national_team->showPlayersTable(); cout << endl;
                            cout << "Select the index of ALL players this competition should call" << endl;
                            cout << "Press [a] or other letter to exit." << endl;
                            n = team_players.size();
                            while(cin >> index && !cin.eof()) {
                                if (index >= n) {
                                    cout << "Invalid index" << endl;
                                    continue;
                                } else if (find(v_index.begin(), v_index.end(), index) != v_index.end()) {
                                    cout << team_players[index]->getName() << " was already added!!" << endl;
                                    continue;
                                } else {
                                    m_players.insert(pair<Player*, int>(team_players[index],0));
                                    v_index.push_back(index);
                                    cout << team_players[index]->getName() << " was successfully added!!" << endl;
                                }
                            }

                            co->setPlayerInjuries(m_players);
                            cin.clear();
                            cin.ignore(1000,'\n');
                            message = "Called Players successfully changed";
                            break;
                        case 5:
                            cout << "Select the index of player you want to update the injured time" << endl;
                            cout << "Press [a] or other letter to exit." << endl;

                            for (size_t i  = 0; i < v_player.size(); i++) {
                                cout << "Index " << i << ": " << v_player[i]->getName() << endl;
                            }

                            n = co->getCalled().size();
                            while(cin >> index && !cin.eof()) {
                                if (index >= n) {
                                    cout << "Invalid index" << endl;
                                    continue;
                                } else {
                                    cout << "Number of days " << v_player[index]->getName() << " was injured in this competition: " << endl;
                                    cin >> nt; failInput(nt);
                                    while(nt > co->getStartDate().daysUntil(co->getEndDate()) || nt < 0) {
                                        cout << "This competition only have " << co->getStartDate().daysUntil(co->getEndDate()) << " days" << endl;
                                        cin >> nt;
                                        failInput(nt);
                                    }
                                    co->updatePlayerInjuries(v_player[index], nt);
                                    cout << "Select the index of player you want to update the injured time" << endl;
                                    cout << "Press [a] or other letter to exit." << endl;
                                    cin.clear();
                                    cin.ignore(1000, '\n');
                                }
                            }
                            message = "Injured time of player updated!";
                            break;
                        default:
                            break;
                    }
                    cout << message << endl << endl;
                    cout << "Which field you want to change in this competition " << name << endl;
                    cout << "Select the correspondent index: " << endl;
                    cout << "1. Change competition name" << endl;
                    cout << "2. Change date" << endl;
                    cout << "3. Change money paid for accommodation" << endl;
                    cout << "4. Change called players" << endl;
                    cout << "5. Update player injuries" << endl;

                    cout << "Press [a] or other letter to exit." << endl;
                }
            }
        }
    }
    cout << "Stopped updating Competitions" << endl;
    cin.clear();
    cin.ignore(1000,'\n');
    return 1;
}

int menu_removeCompetition() {
    int index;
    string name;
    vector<Competition*> comp = national_team->getCompetition();
    cout << "Write the index of the Competition you wish to remove " << endl;
    cout << "Press [a] or other letter to exit." << endl;

    for (size_t i = 0; i < comp.size(); i++){
        cout << "Competition number: " << i << " " << comp[i]->getCompetitionName() << endl;
    }

    while(cin >> index && !cin.eof()){
        if (index >= comp.size()) {
            cout << "Index too high!!" << endl;
            continue;
        }
        else {
            name = comp[index]->getCompetitionName();
            national_team->removeCompetition(comp[index]);
            comp = national_team->getCompetition();
            for (size_t i = 0; i < comp.size(); i++){
                cout << "Competition number: " << i << " " << comp[i]->getCompetitionName() << endl;
            }
            cout << name << " was successfully removed!!" << endl;
            cout << "Press [a] or other letter to exit." << endl;
        }
    }
    cout << "Stopped removing Competitions!" << endl;
    cin.clear();
    cin.ignore(1000,'\n');
    waitInput();
    return 1;
}

int menu_tournaments()
{
    char menu;
    //cout << string(50, '\n');  //Clear Screen that works on linux(more portable)

    cout << "========================================= " << endl;
    cout << "            Competitions Menu             " << endl;
    cout << "========================================= \n" << endl;

    cout << "1. Show all competitions" << endl;
    cout << "2. Information about all games" << endl;
    cout << "3. Pay competitions fees" << endl;
    cout << "4. Detailed information about one competition" << endl;
    cout << "5. Create a new Competition " << endl;
    cout << "6. Update a Competition " << endl;
    cout << "7. Remove a Competition " << endl;
    cout << "0. Return to Main Menu " << endl << endl;

    cin.clear();
    cin >> menu;
    cin.ignore(1000,'\n');

    switch(menu)
    {
        case '1':    //Show all competitions
            for(int i = 0; i < (national_team->getCompetition()).size(); i++)
                cout << (*(national_team->getCompetition()[i])) << endl;
            waitInput();
            return 0;
        case '2':
            while(!menu_games());
            return 0;
        case '3':
            while(!menu_payCompetitions());
            return 0;
        case '4':
            while(!menu_chooseCompetition());
            return 0;
        case '5':
            try{
                while(!menu_creatCompetition());
            }
            catch(CompetitionAlreadyExists &er){
                cout << "Competition " << er.getName() << " already exists" << endl;
            }
            return 0;
        case '6':
            try{
                while(!menu_updateCompetition());
            }
            catch(CompetitionAlreadyExists &er){
                cout << "Competition " << er.getName() << " already exists" << endl;
            }
            return 0;
        case '7':
            while(!menu_removeCompetition());
            return 0;
        case '0':    //Exit function
            return 1;
        default:     //Invalid input
            return 0;
    }
}

int menu_info()
{
    //cout << string(50, '\n');  //Clear Screen that works on linux(more portable)

    cout << "========================================= " << endl;
    cout << "            Team Information             " << endl;
    cout << "========================================= \n" << endl;

    cout << "Team Name: " << national_team->getTeamName() << endl;
    cout << "Number of Players: " << national_team->getPlayers().size() << endl;
    cout << "Number of Competitions: " << national_team->getCompetition().size() << endl;
    cout << "Competitions not paid: " << national_team->missingPay() << endl;
    cout << "Money spent with accommodation: " << national_team->getMoneyAccommodation() << endl;
    cout << "Money spent with players in competitions: " << national_team->getMoneyPlayers() << endl;
    cout << "Money spent with staff per month: " << national_team->getMoneyStaff() << endl;

    waitInput();
    return 1;
}

int menu_credits() {

    //cout << string(50, '\n');  //Clear Screen that works on linux(more portable)

    cout << "This app was created by:" << endl << endl;
    cout << "Diogo Samuel Fernandes" << endl;
    cout << "Hugo Guimaraes" << endl;
    cout << "Joao Carlos Pires" << endl << endl;

    waitInput();
    return 1;
}

int mainMenu(string &file_name) {
    char menu;

    //cout << string(50, '\n');  //Clear Screen that works on linux(more portable)
    cout << "========================================= " << endl;
    cout << "          National Football Team          " << endl;
    cout << "                Main Menu                 " << endl;
    cout << "========================================= \n" << endl;
    cout << "1. Player Menu" << endl;
    cout << "2. Staff Menu" << endl;
    cout << "3. Competitions Menu" << endl;
    cout << "4. View Team Stats" << endl;
    cout << "5. Save Information" << endl;
    cout << "6. App Info" << endl;
    cout << "0. Exit" << endl << endl;

    cin.clear();
    cin >> menu;
    cin.ignore(1000,'\n');

    switch(menu)
    {
        case '1':    //View player info
            while(!menu_players());
            return 0;
        case '2':    //View staff info
            while(!menu_staff());
            return 0;
        case '3':    //View app info
            while(!menu_tournaments());
            return 0;
        case '4':    //View app info
            while(!menu_info());
            return 0;
        case '5':
            national_team->updateFile(file_name);
            cout << endl << "Information saved successfully in file: " << file_name << endl;
            waitInput();
            return 0;
        case '6':    //View app info
            while(!menu_credits());
            return 0;
        case '0':    //Exit function
            char confirmation;
            cout << "Are you sure you want to exit? [y/N] \nDon't forget to save your work before you leave." << endl;
            cin.clear();
            cin >> confirmation;
            cin.ignore(1000,'\n');
            if (confirmation == 'y') {
                exit(0);
            }
            return 0;
        default:     //Invalid input
            return 0;
    }
}

int fileMenu(){
    ifstream teamFile;
    string filename;

    cout << "   Write the filename you wish to read: " << endl;
    cout << "0. Go back to the previous menu" << endl;
    cin.clear();
    cin >> filename;
    cin.ignore(1000,'\n');
    teamFile.open(filename);

    if(filename == "0") return 1;

    while (teamFile.fail())
    {
        cin.clear();
        cout << "Incorrect filename, please enter again: " << endl;
        cin >> filename;
        teamFile.open(filename);

        if(filename == "0") return 1;
    }
    national_team = new Team(filename);
    while(!mainMenu(filename));
    return 1;
}

int createNewTeamMenu(){
    string team_name;

    cout << "   Write the name of your Team: " << endl;
    cout << "0. Go back to the previous menu" << endl;
    cin.clear();
    cin >> team_name;
    cin.ignore(1000,'\n');

    if(team_name == "0") return 1;

    national_team = new Team();
    national_team->setTeamName(team_name);
    string file_name = team_name + ".txt";
    while(!mainMenu(file_name));
    return 1;
}

int initMenu(){
    char menu;
    cout << "========================================= " << endl;
    cout << "          National Football Team          " << endl;
    cout << "========================================= \n" << endl;
    cout << "Choose and option:" << endl;
    cout << "1. Select the team file to read " << endl;
    cout << "2. Create a new team file " << endl;
    cout << "0. Exit program" << endl << endl;

    cin.clear();
    cin >> menu;
    cin.ignore(1000,'\n');

    switch(menu){
        case '1': //Select the Team File to read
            while(!fileMenu());
            return 0;
        case '2': //Create a new Team File
            while(!createNewTeamMenu());
            return 0;
        case '0': //Exits program
            return 1;
        default:  //Goes back
            return 0;
    }
}

