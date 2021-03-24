//
// Created by Oğuz Kerem Yıldız on 1.02.2021.
//
#include <iostream>
#include <fstream>
#include "Graph/WeightedGraph.h"
#include "Graph/ResidualEdge.h"
#include "Graph/IntegerLength.h"
#include <vector>

using namespace std;

int sum(const vector<int>& list) {
    int sum = 0;
    for (int i : list) {
        sum += i;
    }
    return sum;
}

void print(unordered_map<string, vector<string>> map, const vector<int>& teamList) {
    unordered_map<string, int> check = unordered_map<string, int>();
    for (auto &string : map) {
        check[string.first] = 0;
    }
    for (int i = 0; i < teamList.size(); i++) {
        for (auto &key : map) {
            if (find(map[key.first].begin(), map[key.first].end(), "team" + to_string(i + 1)) != map[key.first].end() && check[key.first] != map[key.first].size()) {
                check[key.first] = check[key.first] + 1;
                cout << key.first.substr(5) + " ";
            }
        }
        cout << "" << endl;
    }
}

WeightedGraph<string, int> setGraph(vector<int> teamList, vector<int> tableList) {
    LengthInterface<int> *lengthInterface = new IntegerLength();
    WeightedGraph<string, int> graph = WeightedGraph<string, int>(lengthInterface);
    for (int i = 0; i < teamList.size(); i++) {
        graph.addUndirectedEdge("s", "team" + to_string(i + 1), new ResidualEdge<int>(teamList.at(i), 0, lengthInterface), new ResidualEdge<int>(teamList.at(i), lengthInterface));
    }
    for (int i = 0; i < tableList.size(); i++) {
        graph.addUndirectedEdge("table" + to_string(i + 1), "t", new ResidualEdge<int>(tableList.at(i), 0, lengthInterface), new ResidualEdge<int>(tableList.at(i), lengthInterface));
    }
    for (int i = 0; i < teamList.size(); i++) {
        for (int j = 0; j < tableList.size(); j++) {
            graph.addUndirectedEdge("team" + to_string(i + 1), "table" + to_string(j + 1), new ResidualEdge<int>(1, 0, lengthInterface), new ResidualEdge<int>(1, lengthInterface));
        }
    }
    return graph;
}

bool containsValue(unordered_map<string, string> previousMap, string element) {
    for (auto &entry : previousMap) {
        if (entry.second == element) {
            return true;
        }
    }
    return false;
}

unordered_map<string, string> breadthFirstSearch(WeightedGraph<string, int> graph, const string& source) {
    unordered_map<string, string> returning = unordered_map<string, string>();
    unordered_set<string> set = unordered_set<string>();
    unordered_map<int, vector<string>> map = unordered_map<int, vector<string>>();
    int iterate = 0;
    map[iterate] = vector<string>();
    map[iterate].push_back(source);
    set.insert(source);
    do {
        map[iterate + 1] = vector<string>();
        for (int i = 0; i < map[iterate].size(); i++) {
            string current = map[iterate].at(i);
            if (graph.containsKey(current)) {
                set.insert(current);
                for (int j = 0; j < graph.get(current).size(); j++) {
                    if (set.find(graph.get(current).at(j).first) == set.end() && static_cast<ResidualEdge<int>*>(graph.get(current).at(j).second)->getResidual() > 0) {
                        set.insert(graph.get(current, j).first);
                        map[iterate + 1].push_back(graph.get(current, j).first);
                        returning[graph.get(current, j).first] = current;
                    }
                }
            }
        }
        iterate++;
    } while (!map[iterate].empty());
    return returning;
}

void setGraphAndMap(WeightedGraph<string, int> &graph, unordered_map<string, vector<string>> &map, vector<string> &list) {
    if (find(map[list.at(1)].begin(), map[list.at(1)].end(), list.at(2)) == map[list.at(1)].end()) {
        reverse(list.begin(), list.end());
        for (int i = 0; i < list.size(); i++) {
            if (i + 1 < list.size()) {
                if (graph.containsKey(list.at(i))) {
                    for (int j = 0; j < graph.get(list.at(i)).size(); j++) {
                        if (list.at(i + 1) == graph.get(list.at(i), j).first) {
                            static_cast<ResidualEdge<int>*>(graph.get(list.at(i), j).second)->setFlow(static_cast<ResidualEdge<int>*>(graph.get(list.at(i), j).second)->getFlow() + 1);
                            for (int k = 0; k < graph.get(list.at(i + 1)).size(); k++) {
                                string current = graph.get(list.at(i + 1)).at(k).first;
                                if (current == list.at(i)) {
                                    static_cast<ResidualEdge<int>*>(graph.get(list.at(i + 1), k).second)->setFlow(static_cast<ResidualEdge<int>*>(graph.get(list.at(i + 1), k).second)->getFlow() - 1);
                                }
                            }
                        }
                    }
                }
            }
        }
        map[list.at(2)].push_back(list.at(1));
    }
}

bool isASolution(unordered_map<string, vector<string>> map, const vector<int>& teamList) {
    int total = 0;
    for (auto &key : map) {
        total += map[key.first].size();
    }
    return total == sum(teamList);
}

void fordFulkerson(const vector<int>& teamList, const vector<int>& tableList, WeightedGraph<string, int> &graph) {
    string source = "s";
    string sink = "t";
    unordered_map<string, vector<string>> map = unordered_map<string, vector<string>>();
    for (int i = 0; i < tableList.size(); i++) {
        map["table" + to_string(i + 1)] = vector<string>();
    }
    unordered_map<string, string> previousMap;
    vector<string> list = vector<string>();
    do {
        list.clear();
        previousMap = breadthFirstSearch(graph, source);
        if (previousMap.find(sink) != previousMap.end() && containsValue(previousMap, source)) {
            string current = sink;
            list.push_back(sink);
            while (find(list.begin(), list.end(), source) == list.end()) {
                list.push_back(previousMap[current]);
                current = previousMap[current];
            }
            setGraphAndMap(graph, map, list);
        }
    } while (find(list.begin(), list.end(), source) != list.end());
    if (isASolution(map, teamList)) {
        cout << "1" << endl;
        print(map, teamList);
    } else {
        cout << "0" << endl;
    }
}

int main() {
    fstream file;
    file.open("Dinner.txt", ios::in);
    if (file.fail()) {
        cout << "file not reading" << endl;
    } else {
        WeightedGraph<string, int> graph;
        int teams = 1000;
        int tables = 1000;
        while (teams != 0 && tables != 0) {
            file >> teams;
            file >> tables;
            if (teams != 0 && tables != 0) {
                vector<int> teamList = vector<int>();
                for (int i = 0; i < teams; i++) {
                    int element;
                    file >> element;
                    teamList.push_back(element);
                }
                vector<int> tableList = vector<int>();
                for (int i = 0; i < tables; i++) {
                    int element;
                    file >> element;
                    tableList.push_back(element);
                }
                graph = setGraph(teamList, tableList);
                if (sum(teamList) <= sum(tableList)) {
                    fordFulkerson(teamList, tableList, graph);
                } else {
                    cout << "0" << endl;
                }
                teamList.clear();
                tableList.clear();
                graph.clear();
            }
        }
    }
}