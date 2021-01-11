//
// Created by Oğuz Kerem Yıldız on 10.01.2021.
//

#ifndef PROGRAMMINGCHALLENGES_CPP_TEAM_H
#define PROGRAMMINGCHALLENGES_CPP_TEAM_H
#include <iostream>

using namespace std;

class Team {
private:
    string name;
    int goal;
    int games;
    int wins;
    int loses;
    int ties;
    int goalAgainst;
public:
    Team(string name, int goal, int games, int wins, int loses, int ties, int goalAgainst);
    Team();
    string getName();
    void setName(string n);
    int getGoal();
    void setGoal(int g);
    int getGames();
    void setGames(int g);
    int getWins();
    void setWins(int w);
    int getLoses();
    void setLoses(int l);
    int getTies();
    void setTies(int t);
    int getGoalAgainst();
    void setGoalAgainst(int g);
};
bool operator ==(Team t1, Team t2);

#endif //PROGRAMMINGCHALLENGES_CPP_TEAM_H
