//
// Created by Oğuz Kerem Yıldız on 10.01.2021.
//

#include "Team.h"

Team::Team() = default;

Team::Team(string name, int goal, int games, int wins, int loses, int ties, int goalAgainst) {
    this->name = name;
    this->goal = goal;
    this->games = games;
    this->wins = wins;
    this->loses = loses;
    this->ties = ties;
    this->goalAgainst = goalAgainst;
}

string Team::getName() {
    return name;
}

void Team::setName(string n) {
    this->name = n;
}

int Team::getGoal() {
    return goal;
}

void Team::setGoal(int g) {
    this->goal = g;
}

int Team::getGames() {
    return games;
}

void Team::setGames(int g) {
    this->games = g;
}

int Team::getWins() {
    return wins;
}

void Team::setWins(int w) {
    this->wins = w;
}

int Team::getLoses() {
    return loses;
}

void Team::setLoses(int l) {
    this->loses = l;
}

int Team::getTies() {
    return ties;
}

void Team::setTies(int t) {
    this->ties = t;
}

int Team::getGoalAgainst() {
    return goalAgainst;
}

void Team::setGoalAgainst(int g) {
    this->goalAgainst = g;
}

bool operator ==(Team t1, Team t2) {
    return t1.getName() == t2.getName() && t1.getGoal() == t2.getGoal() && t1.getGames() == t2.getGames() && t1.getGoalAgainst() == t2.getGoalAgainst() && t1.getLoses() == t2.getLoses() && t1.getTies() == t2.getTies() && t1.getWins() == t2.getWins();
}