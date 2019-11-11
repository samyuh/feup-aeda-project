#ifndef AEDA_GAME_H
#define AEDA_GAME_H

#include <string>
#include <vector>
#include <ostream>
#include "Player.h"
#include "Statistics.h"

using namespace std;

class Game
{
private:
    string opponent;
    string country; /*!< Game's country */
    string city;    /*!< Game's city    */
    string stadium; /*!< Game's stadium */
    Date gameDate;  /*!< Game's Date    */
    vector<Player *> called_players; /*!< Vector with called players */
    Statistics game_stats;
public:
    Game(string opponent, string country, string city, string stadium, Date gameDate);
    Game(string opponent, string country, string city, string stadium, Date gameDate, vector<Player *> called_players, Statistics stats);

    string getOpponent() const;
    string getCountry() const;
    string getCity() const;
    string getStadium() const;
    Date getDate() const;
    vector<Player *> getCalledPlayers() const;
    void info() const;
    //Stats stats getStats()const;
};
class GameNotFound{
    string country,city,stadium;

public:
    GameNotFound(string country,string city,string stadium) :
            country(country), city(city), stadium(stadium){}
    string getCountry() const {return country;}
    string getCity() const {return city;}
    string getStadium() const {return stadium;}
};

class GameAlreadyExists{
    string country,city,stadium,opponent;
    Date d;

public:
    GameAlreadyExists(string opponent, string country,string city,string stadium, Date d) :
            opponent(opponent),country(country), city(city), stadium(stadium), d(d){}
    string getCountry() const {return country;}
    string getCity() const {return city;}
    string getStadium() const {return stadium;}
    string getOpponent() const {return opponent;}
    Date getDate() const {return d;}
};

#endif
