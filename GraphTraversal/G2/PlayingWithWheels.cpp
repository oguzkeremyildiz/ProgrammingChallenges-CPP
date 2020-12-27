//
// Created by Oğuz Kerem Yıldız on 27.12.2020.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include "Graph/Graph.h"
#include <utility>

using namespace std;

static unordered_set<int> edgeList;
static bool boolFind;
static int iterate;

int firstDigit(int digit, int number) {
    switch (digit) {
        case 0:
            return number % 10;
        case 1:
            return (number / 10) % 10;
        case 2:
            return (number / 100) % 10;
        case 3:
            return (number / 1000) % 10;
    }
    return -1;
}

int incrementDigit(int digit, int number) {
    int currentDigit = firstDigit(digit, number);
    switch (digit) {
        case 0:
            if (currentDigit == 9) {
                return number - 9;
            } else {
                return number + 1;
            }
        case 1:
            if (currentDigit == 9) {
                return number - 90;
            } else {
                return number + 10;
            }
        case 2:
            if (currentDigit == 9) {
                return number - 900;
            } else {
                return number + 100;
            }
        case 3:
            if (currentDigit == 9) {
                return number - 9000;
            } else {
                return number + 1000;
            }
    }
    return -1;
}

int decrementDigit(int digit, int number) {
    int currentDigit = firstDigit(digit, number);
    switch (digit) {
        case 0:
            if (currentDigit == 0) {
                return number + 9;
            } else {
                return number - 1;
            }
        case 1:
            if (currentDigit == 0) {
                return number + 90;
            } else {
                return number - 10;
            }
        case 2:
            if (currentDigit == 0) {
                return number + 900;
            } else {
                return number - 100;
            }
        case 3:
            if (currentDigit == 0) {
                return number + 9000;
            } else {
                return number - 1000;
            }
    }
    return -1;
}

pair<Graph<int>, bool> constructCandidates(Graph<int> graph, int target) {
    bool check = false;
    int candidateOne;
    int candidateTwo;
    for (int i = 0; i < graph.get(iterate - 1).size(); i++) {
        for (int j = 0; j < 4; j++) {
            candidateOne = incrementDigit(j, graph.get(iterate - 1).at(i));
            if (edgeList.find(candidateOne) == edgeList.end()) {
                graph.addDirectedEdge(iterate, candidateOne);
                edgeList.insert(candidateOne);
                if (target == candidateOne) {
                    cout << to_string(candidateOne) + " " + to_string(iterate) << endl;
                    boolFind = false;
                    check = false;
                    break;
                } else {
                    check = true;
                }
            }
            candidateTwo = decrementDigit(j, graph.get(iterate - 1).at(i));
            if (edgeList.find(candidateTwo) == edgeList.end()) {
                graph.addDirectedEdge(iterate, candidateTwo);
                edgeList.insert(candidateTwo);
                if (target == candidateTwo) {
                    cout << to_string(candidateTwo) + " " + to_string(iterate) << endl;
                    boolFind = false;
                    check = false;
                    break;
                } else {
                    check = true;
                }
            }
        }
    }
    return pair<Graph<int>, bool>(graph, check);
}

Graph<int> addEdge(Graph<int> graph, int target) {
    iterate++;
    graph.put(iterate, vector<int>());
    bool check = true;
    while (check) {
        pair<Graph<int>, bool> candidates = constructCandidates(graph, target);
        graph = candidates.first;
        check = candidates.second;
        if (check) {
            iterate++;
            graph.put(iterate, vector<int>());
        }
    }
    return graph;
}

int main() {
    fstream file;
    file.open("Wheels.txt", ios::in);
    if (file.fail()) {
        cout << "file not reading" << endl;
    } else {
        int times, current, currentWheel;
        file >> times;
        edgeList = unordered_set<int>();
        Graph<int> graph = Graph<int>();
        for (int i = 0; i < times; i++) {
            boolFind = true;
            iterate = 0;
            file >> currentWheel;
            graph.put(0, vector<int>());
            graph.addDirectedEdge(0, currentWheel);
            int target;
            file >> target;
            file >> current;
            edgeList.insert(graph.get(0).at(0));
            for (int j = 0; j < current; j++) {
                int source;
                file >> source;
                edgeList.insert(source);
            }
            graph = addEdge(graph, target);
            if (boolFind) {
                cout << -1 << endl;
            }
            graph.clear();
            edgeList.clear();
        }
    }
}