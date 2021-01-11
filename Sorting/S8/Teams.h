//
// Created by Oğuz Kerem Yıldız on 10.01.2021.
//

#ifndef PROGRAMMINGCHALLENGES_CPP_TEAMS_H
#define PROGRAMMINGCHALLENGES_CPP_TEAMS_H
#include <vector>
#include "Team.h"

using namespace std;

class Teams {
private:
    vector<Team> teams = vector<Team>();
public:
    Teams();
    bool containTeam(string name);
    void removeTeam(Team team);
    void addTeam(Team &team);
    Team getTeam(int index);
    int size();
    void clear();
    int mostPoint(Teams &team);
    int mostWins(Teams &team);
    int mostGoalDifference(Teams &team);
    int mostGoal(Teams &team);
    int mostGamePlayed(Teams &team);
    void lexicographic(Teams &team);
    void setGoal(int index, int goal);
    void setGames(int index, int games);
    void setWins(int index, int wins);
    void setLoses(int index, int loses);
    void setTies(int index, int ties);
    void setGoalAgainst(int index, int goalAgainst);
};

#endif //PROGRAMMINGCHALLENGES_CPP_TEAMS_H
