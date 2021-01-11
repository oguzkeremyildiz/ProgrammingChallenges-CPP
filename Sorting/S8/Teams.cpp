//
// Created by Oğuz Kerem Yıldız on 10.01.2021.
//

#include "Teams.h"

Teams::Teams() {

}

bool Teams::containTeam(string name) {
    bool boolean = false;
    for (Team value : teams) {
        if (value.getName() == name) {
            boolean = true;
            break;
        }
    }
    return boolean;
}

void Teams::removeTeam(Team team) {
    teams.erase(remove(teams.begin(), teams.end(), team), teams.end());
}

void Teams::addTeam(Team &team) {
    teams.push_back(team);
}

Team Teams::getTeam(int index) {
    return teams.at(index);
}

int Teams::size() {
    return teams.size();
}

void Teams::clear() {
    teams.clear();
}

int Teams::mostPoint(Teams &team) {
    int biggestPoint = 0;
    for (Team value : teams) {
        if ((value.getWins() * 3) + (value.getTies()) > biggestPoint) {
            team.clear();
            biggestPoint = (value.getWins() * 3) + (value.getTies());
            team.addTeam(value);
        } else if ((value.getWins() * 3) + (value.getTies()) == biggestPoint) {
            team.addTeam(value);
        }
    }
    return team.size();
}

int Teams::mostWins(Teams &team) {
    int biggestWins = 0;
    for (Team value : teams) {
        if (value.getWins() > biggestWins) {
            team.clear();
            biggestWins = value.getWins();
            team.addTeam(value);
        } else if (value.getWins() == biggestWins) {
            team.addTeam(value);
        }
    }
    return team.size();
}

int Teams::mostGoalDifference(Teams &team) {
    int biggestDifference = 0;
    for (Team value : teams) {
        if (value.getGoal() - value.getGoalAgainst() > biggestDifference) {
            team.clear();
            biggestDifference = value.getGoal() - value.getGoalAgainst();
            team.addTeam(value);
        } else if (value.getGoal() - value.getGoalAgainst() == biggestDifference) {
            team.addTeam(value);
        }
    }
    return team.size();
}

int Teams::mostGoal(Teams &team) {
    int mostGoal = 0;
    for (Team value : teams) {
        if (value.getGoal() > mostGoal) {
            team.clear();
            mostGoal = value.getGoal();
            team.addTeam(value);
        } else if (value.getGoal() == mostGoal) {
            team.addTeam(value);
        }
    }
    return team.size();
}

void Teams::lexicographic(Teams &team) {
    vector<string> names = vector<string>();
    for (Team value : teams) {
        names.push_back(value.getName());
    }
    sort(names.begin(), names.end());
    for (Team value : teams) {
        if (value.getName() == names.at(0)) {
            team.addTeam(value);
            break;
        }
    }
}

int Teams::mostGamePlayed(Teams &team) {
    int mostGamePlayed = 0;
    for (Team value : teams) {
        if (value.getGames() > mostGamePlayed) {
            team.clear();
            mostGamePlayed = value.getGames();
            team.addTeam(value);
        } else if (value.getGames() == mostGamePlayed) {
            team.addTeam(value);
        }
    }
    return team.size();
}

void Teams::setGoal(int index, int goal) {
    teams.at(index).setGoal(goal);
}

void Teams::setGames(int index, int games) {
    teams.at(index).setGames(games);
}

void Teams::setWins(int index, int wins) {
    teams.at(index).setWins(wins);
}

void Teams::setLoses(int index, int loses) {
    teams.at(index).setLoses(loses);
}

void Teams::setTies(int index, int ties) {
    teams.at(index).setTies(ties);
}

void Teams::setGoalAgainst(int index, int goalAgainst) {
    teams.at(index).setGoalAgainst(goalAgainst);
}
