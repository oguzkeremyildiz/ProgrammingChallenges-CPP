//
// Created by Oğuz Kerem Yıldız on 11.01.2021.
//
#include <fstream>
#include <iostream>
#include <vector>
#include "Teams.h"

using namespace std;

void reserve(string line, vector<string> &features) {
    string element;
    for (int i = 0; i < line.length(); i++) {
        if (line.at(i) != '#' && line.at(i) != '@') {
            element += line.at(i);
        } else {
            features.push_back(element);
            element = "";
        }
    }
    features.push_back(element);
}

void print(Teams &teams) {
    int i = 0;
    while (teams.size() != 0) {
        i++;
        Teams team = Teams();
        if (teams.mostPoint(team) == 1) {
            cout << to_string(i) + ") " + team.getTeam(0).getName() + " " + to_string(team.getTeam(0).getWins() * 3 + (team.getTeam(0).getTies())) + "p, " + to_string(team.getTeam(0).getGames()) + "g " + "(" + to_string(team.getTeam(0).getWins()) + "-" + to_string(team.getTeam(0).getTies()) + "-" + to_string(team.getTeam(0).getLoses()) + "), " + to_string(team.getTeam(0).getGoal() - team.getTeam(0).getGoalAgainst()) + "gd (" + to_string(team.getTeam(0).getGoal()) + "-" + to_string(team.getTeam(0).getGoalAgainst()) + ")" << endl;
            teams.removeTeam(team.getTeam(0));
        } else if (teams.mostPoint(team) > 1) {
            team.clear();
            if (teams.mostWins(team) == 1) {
                cout << to_string(i) + ") " + team.getTeam(0).getName() + " " + to_string(team.getTeam(0).getWins() * 3 + (team.getTeam(0).getTies())) + "p, " + to_string(team.getTeam(0).getGames()) + "g " + "(" + to_string(team.getTeam(0).getWins()) + "-" + to_string(team.getTeam(0).getTies()) + "-" + to_string(team.getTeam(0).getLoses()) + "), " + to_string(team.getTeam(0).getGoal() - team.getTeam(0).getGoalAgainst()) + "gd (" + to_string(team.getTeam(0).getGoal()) + "-" + to_string(team.getTeam(0).getGoalAgainst()) + ")" << endl;
                teams.removeTeam(team.getTeam(0));
            } else if (teams.mostWins(team) > 1){
                team.clear();
                if (teams.mostGoalDifference(team) == 1) {
                    cout << to_string(i) + ") " + team.getTeam(0).getName() + " " + to_string(team.getTeam(0).getWins() * 3 + (team.getTeam(0).getTies())) + "p, " + to_string(team.getTeam(0).getGames()) + "g " + "(" + to_string(team.getTeam(0).getWins()) + "-" + to_string(team.getTeam(0).getTies()) + "-" + to_string(team.getTeam(0).getLoses()) + "), " + to_string(team.getTeam(0).getGoal() - team.getTeam(0).getGoalAgainst()) + "gd (" + to_string(team.getTeam(0).getGoal()) + "-" + to_string(team.getTeam(0).getGoalAgainst()) + ")" << endl;
                    teams.removeTeam(team.getTeam(0));
                } else if (teams.mostGoalDifference(team) > 1){
                    team.clear();
                    if (teams.mostGoal(team) == 1) {
                        cout << to_string(i) + ") " + team.getTeam(0).getName() + " " + to_string(team.getTeam(0).getWins() * 3 + (team.getTeam(0).getTies())) + "p, " + to_string(team.getTeam(0).getGames()) + "g " + "(" + to_string(team.getTeam(0).getWins()) + "-" + to_string(team.getTeam(0).getTies()) + "-" + to_string(team.getTeam(0).getLoses()) + "), " + to_string(team.getTeam(0).getGoal() - team.getTeam(0).getGoalAgainst()) + "gd (" + to_string(team.getTeam(0).getGoal()) + "-" + to_string(team.getTeam(0).getGoalAgainst()) + ")" << endl;
                        teams.removeTeam(team.getTeam(0));
                    } else if (teams.mostGoal(team) > 1){
                        team.clear();
                        if (teams.mostGamePlayed(team) == 1) {
                            cout << to_string(i) + ") " + team.getTeam(0).getName() + " " + to_string(team.getTeam(0).getWins() * 3 + (team.getTeam(0).getTies())) + "p, " + to_string(team.getTeam(0).getGames()) + "g " + "(" + to_string(team.getTeam(0).getWins()) + "-" + to_string(team.getTeam(0).getTies()) + "-" + to_string(team.getTeam(0).getLoses()) + "), " + to_string(team.getTeam(0).getGoal() - team.getTeam(0).getGoalAgainst()) + "gd (" + to_string(team.getTeam(0).getGoal()) + "-" + to_string(team.getTeam(0).getGoalAgainst()) + ")" << endl;
                            teams.removeTeam(team.getTeam(0));
                        } else if (teams.mostGamePlayed(team) > 1) {
                            team.clear();
                            teams.lexicographic(team);
                            teams.removeTeam(team.getTeam(0));
                            team.clear();
                        }
                    }
                }
            }
        }
    }
}

void setTeam(Teams &teams, vector<string> &matches) {
    vector<string> features = vector<string>();
    for (string match : matches) {
        features.clear();
        reserve(match, features);
        if (teams.containTeam(features.at(0))) {
            for (int j = 0; j < teams.size(); j++) {
                int wins = 0;
                int loses = 0;
                int ties = 0;
                if (stoi(features.at(1)) > stoi(features.at(2))) {
                    wins = 1;
                } else if (stoi(features.at(1)) < stoi(features.at(2))) {
                    loses = 1;
                } else {
                    ties = 1;
                }
                if (teams.getTeam(j).getName() == (features.at(0))) {
                    teams.setGoal(j, teams.getTeam(j).getGoal() + stoi(features.at(1)));
                    teams.setGames(j, teams.getTeam(j).getGames() + 1);
                    teams.setWins(j, teams.getTeam(j).getWins() + wins);
                    teams.setLoses(j, teams.getTeam(j).getLoses() + loses);
                    teams.setTies(j, teams.getTeam(j).getTies() + ties);
                    teams.setGoalAgainst(j, teams.getTeam(j).getGoalAgainst() + stoi(features.at(2)));
                    break;
                }
            }
        } else {
            int wins = 0;
            int loses = 0;
            int ties = 0;
            if (stoi(features.at(1)) > stoi(features.at(2))) {
                wins = 1;
            } else if (stoi(features.at(1)) < stoi(features.at(2))) {
                loses = 1;
            } else {
                ties = 1;
            }
            Team t = Team(features.at(0), stoi(features.at(1)), 1, wins, loses, ties, stoi(features.at(2)));
            teams.addTeam(t);
        }
        if (teams.containTeam(features.at(3))) {
            for (int j = 0; j < teams.size(); j++) {
                int wins = 0;
                int loses = 0;
                int ties = 0;
                if (stoi(features.at(2)) > stoi(features.at(1))) {
                    wins = 1;
                } else if (stoi(features.at(2)) < stoi(features.at(1))) {
                    loses = 1;
                } else {
                    ties = 1;
                }
                if (teams.getTeam(j).getName() == features.at(3)) {
                    teams.setGoal(j, teams.getTeam(j).getGoal() + stoi(features.at(2)));
                    teams.setGames(j, teams.getTeam(j).getGames() + 1);
                    teams.setWins(j, teams.getTeam(j).getWins() + wins);
                    teams.setLoses(j, teams.getTeam(j).getLoses() + loses);
                    teams.setTies(j, teams.getTeam(j).getTies() + ties);
                    teams.setGoalAgainst(j, teams.getTeam(j).getGoalAgainst() + stoi(features.at(1)));
                    break;
                }
            }
        } else {
            int wins = 0;
            int loses = 0;
            int ties = 0;
            if (stoi(features.at(2)) > stoi(features.at(1))) {
                wins = 1;
            } else if (stoi(features.at(2)) < stoi(features.at(1))) {
                loses = 1;
            } else {
                ties = 1;
            }
            Team t = Team(features.at(3), stoi(features.at(2)), 1, wins, loses, ties, stoi(features.at(1)));
            teams.addTeam(t);
        }
    }
}

int main() {
    fstream file;
    file.open("Football.txt", ios::in);
    if (file.fail()) {
        cout << "file not reading" << endl;
    } else {
        int times;
        int time;
        string line, teamName;
        Teams teams = Teams();
        vector<string> matches = vector<string>();
        getline(file, line);
        time = stoi(line);
        for (int i = 0; i < time; i++) {
            getline(file, teamName);
            getline(file, line);
            times = stoi(line);
            for (int j = 0; j < times; j++) {
                getline(file, line);
            }
            getline(file, line);
            times = stoi(line);
            for (int t = 0; t < times; t++) {
                getline(file, line);
                matches.push_back(line);
            }
            cout << teamName << endl;
            setTeam(teams, matches);
            print(teams);
            matches.clear();
        }
    }
}