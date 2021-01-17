//
// Created by Oğuz Kerem Yıldız on 17.01.2021.
//
#include <iostream>
#include <fstream>
#include <vector>
#include "Graph/Graph.h"

using namespace std;

static vector<string> ladder;

bool isSuitable(string current, string compared) {
    int size;
    if (current.length() == compared.length()) {
        size = 0;
        for (int i = 0; i < current.length(); i++) {
            if (current.at(i) == compared.at(i)) {
                size++;
            }
        }
        return size == current.length() - 1;
    } else if (current.length() == compared.length() + 1) {
        size = 0;
        if (current.at(0) != compared.at(0)) {
            for (int i = 0; i < compared.length(); i++) {
                if (compared.at(i) == current.at(1 + i)) {
                    size++;
                }
            }
            return compared.length() == size;
        } else if (current.at(current.length() - 1) != compared.at(compared.length() - 1)) {
            for (int i = 0; i < compared.length(); i++) {
                if (compared.at(i) == current.at(i)) {
                    size++;
                }
            }
            return compared.length() == size;
        }
    } else if (current.length() + 1 == compared.length()) {
        size = 0;
        if (current.at(0) != compared.at(0)) {
            for (int i = 0; i < current.length(); i++) {
                if (compared.at(1 + i) == current.at(i)) {
                    size++;
                }
            }
            return current.length() == size;
        } else if (current.at(current.length() - 1) != compared.at(compared.length() - 1)) {
            for (int i = 0; i < current.length(); i++) {
                if (compared.at(i) == current.at(i)) {
                    size++;
                }
            }
            return current.length() == size;
        }
    }
    return false;
}

Graph<string> addEdge(vector<string> list) {
    Graph<string> graph = Graph<string>();
    for (int i = 0; i < list.size(); i++) {
        for (int j = i; j < list.size(); j++) {
            if (isSuitable(list.at(i), list.at(j))) {
                if (!graph.containsKey(list.at(j))) {
                    graph.put(list.at(j), vector<string>());
                }
                if (!graph.containsKey(list.at(i))) {
                    graph.put(list.at(i), vector<string>());
                }
                if (list.at(i) < list.at(j)) {
                    graph.addDirectedEdge(list.at(i), list.at(j));
                } else {
                    graph.addDirectedEdge(list.at(j), list.at(i));
                }
            }
        }
    }
    return graph;
}

int depthFirstSearch(Graph<string> graph, string current, vector<string> &visited) {
    for (int i = 0; i < graph.get(current).size(); i++) {
        if (find(visited.begin(), visited.end(), current) == visited.end()) {
            visited.push_back(current);
        }
        if (find(visited.begin(), visited.end(), graph.get(current, i)) == visited.end()) {
            depthFirstSearch(graph, graph.get(current, i), visited);
            if (ladder.size() < visited.size()) {
                ladder.clear();
                ladder.insert(ladder.end(), visited.begin(), visited.end());
            }
            visited.pop_back();
        }
    }
    return ladder.size() + 1;
}

int main() {
    fstream file;
    file.open("Ladders.txt", ios::in);
    if (file.fail()) {
        cout << "file not reading" << endl;
    } else {
        vector<string> list = vector<string>();
        vector<string> visited = vector<string>();
        int best = 0;
        Graph<string> graph;
        while (!file.eof()) {
            string current;
            file >> current;
            list.push_back(current);
        }
        graph = addEdge(list);
        for (const string& key : graph.getKeySet()) {
            ladder = vector<string>();
            int current = depthFirstSearch(graph, key, visited);
            if (current > best) {
                best = current;
            }
            visited.clear();
        }
        cout << best << endl;
    }
}