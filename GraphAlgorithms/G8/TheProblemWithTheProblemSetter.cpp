//
// Created by Oğuz Kerem Yıldız on 5.02.2021.
//
#include <iostream>
#include <fstream>
#include "Graph/WeightedGraph.h"
#include "Graph/ResidualEdge.h"
#include "Graph/IntegerLength.h"
#include "Problem.h"
#include <vector>
#include <unordered_map>

using namespace std;

struct problem_hash {
    size_t operator() (const Problem& problem) const {
        return problem.getNo() ^ problem.getCategories();
    }
};

string toString(vector<int> list) {
    string str = "[";
    for (int i = 0; i < list.size(); ++i) {
        if (list.size() - 1 == i) {
            str += to_string(list.at(i));
        } else {
            str += to_string(list.at(i)) + ", ";
        }
    }
    str += "]";
    return str;
}

void print(unordered_map<string, vector<Problem>> map, const vector<int>& boundary) {
    for (int i = 0; i < boundary.size(); i++) {
        vector<int> list = vector<int>();
        for (int j = 0; j < map["category" + to_string(i + 1)].size(); j++) {
            list.push_back(map["category" + to_string(i + 1)].at(j).getNo());
        }
        cout << toString(list) << endl;
    }
}

bool containsValue(const unordered_map<string, string>& previousMap, const string& element) {
    for (auto &entry : previousMap) {
        if (entry.second == element) {
            return true;
        }
    }
    return false;
}

unordered_map<string, string> breadthFirstSearch(WeightedGraph<string, int>* graph, const string& source) {
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
            if (graph->containsKey(current)) {
                set.insert(current);
                for (int j = 0; j < graph->get(current).size(); j++) {
                    if (set.find(graph->get(current).at(j).first) == set.end() && static_cast<ResidualEdge<int>*>(graph->get(current).at(j).second)->getResidual() > 0) {
                        set.insert(graph->get(current, j).first);
                        map[iterate + 1].push_back(graph->get(current, j).first);
                        returning[graph->get(current, j).first] = current;
                    }
                }
            }
        }
        iterate++;
    } while (!map[iterate].empty());
    return returning;
}

void removeAll(vector<Problem> &currentList, const vector<Problem>& list) {
    for (auto & i : list) {
        currentList.erase(remove(currentList.begin(), currentList.end(), i), currentList.end());
    }
}

bool check(WeightedGraph<string, int>* graph, vector<string> path, int now, Problem problem) {
    int total = problem.findTotal(now);
    for (int j = 0; j < graph->get(path.at(3)).size(); j++) {
        string current = graph->get(path.at(3), j).first;
        if (current == path.at(2)) {
            if (static_cast<ResidualEdge<int>*>(graph->get(path.at(3), j).second)->getFlow() + total <= graph->get(path.at(3), j).second->getLength()) {
                for (int i = 0; i < graph->get(path.at(1)).size(); i++) {
                    if (graph->get(path.at(1), i).first == path.at(0)) {
                        return static_cast<ResidualEdge<int>*>(graph->get(path.at(1), i).second)->getFlow() + total <= graph->get(path.at(1), i).second->getLength();
                    }
                }
            } else {
                return false;
            }
        }
    }
    return false;
}

void setGraphAndMap(WeightedGraph<string, int>* &graph, unordered_map<string, vector<Problem>> &map, vector<string> path, unordered_map<string, vector<Problem>> &used, vector<Problem> list) {
    vector<Problem> currentList = vector<Problem>();
    for (int i = 0; i < list.size(); ++i) {
        Problem problem = list.at(i);
        currentList.push_back(problem);
    }
    for (auto &entry : used) {
        removeAll(currentList, entry.second);
    }
    bool boolean = false;
    for (Problem problem : currentList) {
        if (problem.contains(stoi(path.at(1).substr(8))) && check(graph, path, stoi(path.at(1).substr(8)), problem)) {
            int total = problem.findTotal(stoi(path.at(1).substr(8)));
            used[path.at(1)].push_back(problem);
            map[path.at(1)].push_back(problem);
            boolean = true;
            for (int j = 0; j < graph->get(path.at(3)).size(); j++) {
                string current = graph->get(path.at(3), j).first;
                if (current == path.at(2)) {
                    static_cast<ResidualEdge<int>*>(graph->get(path.at(3), j).second)->setFlow(static_cast<ResidualEdge<int>*>(graph->get(path.at(3), j).second)->getFlow() + total);
                    for (int k = 0; k < graph->get(path.at(2)).size(); k++) {
                        if (graph->get(path.at(2), k).first == path.at(3)) {
                            static_cast<ResidualEdge<int>*>(graph->get(path.at(2), k).second)->setFlow(static_cast<ResidualEdge<int>*>(graph->get(path.at(2), k).second)->getFlow() - total);
                            break;
                        }
                    }
                    break;
                }
            }
            for (int j = 0; j < graph->get(path.at(1)).size(); j++) {
                string current = graph->get(path.at(1), j).first;
                if (current == path.at(0)) {
                    static_cast<ResidualEdge<int>*>(graph->get(path.at(1), j).second)->setFlow(static_cast<ResidualEdge<int>*>(graph->get(path.at(1), j).second)->getFlow() + total);
                    for (int k = 0; k < graph->get(path.at(0)).size(); k++) {
                        if (graph->get(path.at(0), k).first == path.at(1)) {
                            static_cast<ResidualEdge<int>*>(graph->get(path.at(0), k).second)->setFlow(static_cast<ResidualEdge<int>*>(graph->get(path.at(0), k).second)->getFlow() - total);
                            break;
                        }
                    }
                    break;
                }
            }
            break;
        }
    }
    if (!boolean) {
        for (auto &entry : map) {
            string key = entry.first;
            if (key != path.at(1)) {
                for (int i = 0; i < map[key].size(); i++) {
                    if (map[key].at(i).contains(stoi(path.at(1).substr(8))) && find(used[path.at(1)].begin(), used[path.at(1)].end(), map[key].at(i)) == used[path.at(1)].end()) {
                        int total = map[key].at(i).findTotal(stoi(path.at(1).substr(8)));
                        used[path.at(1)].push_back(map[key].at(i));
                        map[path.at(1)].push_back(map[key].at(i));
                        // check
                        map[key].erase(map[key].begin() + i);
                        for (int j = 0; j < graph->get(path.at(3)).size(); j++) {
                            string current = graph->get(path.at(3), j).first;
                            if (current == path.at(2)) {
                                static_cast<ResidualEdge<int>*>(graph->get(path.at(3), j).second)->setFlow(static_cast<ResidualEdge<int>*>(graph->get(path.at(3), j).second)->getFlow() + total);
                                for (int k = 0; k < graph->get(path.at(2)).size(); k++) {
                                    if (graph->get(path.at(2), k).first == path.at(3)) {
                                        static_cast<ResidualEdge<int>*>(graph->get(path.at(2), k).second)->setFlow(static_cast<ResidualEdge<int>*>(graph->get(path.at(2), k).second)->getFlow() - total);
                                        break;
                                    }
                                }
                                break;
                            }
                        }
                        for (int j = 0; j < graph->get(path.at(1)).size(); j++) {
                            string current = graph->get(path.at(1), j).first;
                            if (current == path.at(0)) {
                                static_cast<ResidualEdge<int>*>(graph->get(path.at(1), j).second)->setFlow(static_cast<ResidualEdge<int>*>(graph->get(path.at(1), j).second)->getFlow() + total);
                                for (int k = 0; k < graph->get(path.at(0)).size(); k++) {
                                    if (graph->get(path.at(0), k).first == path.at(1)) {
                                        static_cast<ResidualEdge<int>*>(graph->get(path.at(0), k).second)->setFlow(static_cast<ResidualEdge<int>*>(graph->get(path.at(0), k).second)->getFlow() - total);
                                        break;
                                    }
                                }
                                break;
                            }
                        }
                        vector<string> anotherPath;
                        for (int j = 0; j < path.size(); ++j) {
                            anotherPath.push_back(path.at(j));
                        }
                        anotherPath.at(1) = key;
                        for (int j = 0; j < graph->get(anotherPath.at(3)).size(); j++) {
                            string current = graph->get(anotherPath.at(3), j).first;
                            if (current == anotherPath.at(2)) {
                                static_cast<ResidualEdge<int>*>(graph->get(anotherPath.at(3), j).second)->setFlow(static_cast<ResidualEdge<int>*>(graph->get(anotherPath.at(3), j).second)->getFlow() - total);
                                for (int k = 0; k < graph->get(anotherPath.at(2)).size(); k++) {
                                    if (graph->get(anotherPath.at(2), k).first == anotherPath.at(3)) {
                                        static_cast<ResidualEdge<int>*>(graph->get(anotherPath.at(2), k).second)->setFlow(static_cast<ResidualEdge<int>*>(graph->get(anotherPath.at(2), k).second)->getFlow() + total);
                                        break;
                                    }
                                }
                                break;
                            }
                        }
                        for (int j = 0; j < graph->get(anotherPath.at(1)).size(); j++) {
                            string current = graph->get(anotherPath.at(1), j).first;
                            if (current == anotherPath.at(0)) {
                                static_cast<ResidualEdge<int>*>(graph->get(anotherPath.at(1), j).second)->setFlow(static_cast<ResidualEdge<int>*>(graph->get(anotherPath.at(1), j).second)->getFlow() - total);
                                for (int k = 0; k < graph->get(anotherPath.at(0)).size(); k++) {
                                    if (graph->get(anotherPath.at(0), k).first == anotherPath.at(1)) {
                                        static_cast<ResidualEdge<int>*>(graph->get(anotherPath.at(0), k).second)->setFlow(static_cast<ResidualEdge<int>*>(graph->get(anotherPath.at(0), k).second)->getFlow() + total);
                                        break;
                                    }
                                }
                                break;
                            }
                        }
                        break;
                    }
                }
            }
        }
    }
}

bool isASolution(unordered_map<string, vector<Problem>> map, vector<int> size) {
    int totalElement = 0;
    for (auto &entry : map) {
        string key = entry.first;
        totalElement += map[key].size();
    }
    int total = 0;
    for (int i = 0; i < size.size(); ++i) {
        total += size.at(i);
    }
    return totalElement == total;
}

void fordFulkerson(WeightedGraph<string, int>* &graph, vector<Problem> list, vector<int> boundary) {
    string source = "s";
    string sink = "t";
    unordered_map<string, vector<Problem>> used = unordered_map<string, vector<Problem>>();
    unordered_set<Problem, problem_hash> allUsed = unordered_set<Problem, problem_hash>();
    unordered_map<string, vector<Problem>> map = unordered_map<string, vector<Problem>>();
    for (int i = 0; i < boundary.size(); i++) {
        map["category" + to_string(i + 1)] = vector<Problem>();
        used["category" + to_string(i + 1)] = vector<Problem>();
    }
    unordered_map<string, string> previousMap;
    vector<string> path = vector<string>();
    do {
        path.clear();
        previousMap = breadthFirstSearch(graph, source);
        if (previousMap.find(sink) != previousMap.end() && containsValue(previousMap, source)) {
            string current = sink;
            path.push_back(sink);
            while (find(path.begin(), path.end(), source) == path.end()) {
                path.push_back(previousMap.at(current));
                current = previousMap.at(current);
            }
            setGraphAndMap(graph, map, path, used, list);
            for (auto &entry : used) {
                allUsed.insert(entry.second.begin(), entry.second.end());
            }
            if (allUsed.size() == list.size()) {
                break;
            }
        }
    } while (find(path.begin(), path.end(), source) != path.end());
    if (isASolution(map, boundary)) {
        cout << "1" << endl;
        print(map, boundary);
    } else {
        cout << "0" << endl;
    }
}

WeightedGraph<string, int>* setGraph(const vector<Problem>& list, vector<int> boundary) {
    auto* graph = new WeightedGraph<string, int>(new IntegerLength());
    string source = "s";
    string sink = "t";
    graph->addUndirectedEdge(source, "problems", new ResidualEdge<int>(list.size(), 0, new IntegerLength()), new ResidualEdge<int>(list.size(), new IntegerLength()));
    for (int i = 0; i < boundary.size(); i++) {
        graph->addUndirectedEdge("problems", "category" + to_string(i + 1), new ResidualEdge<int>(boundary.at(i), 0, new IntegerLength()), new ResidualEdge<int>(boundary.at(i), new IntegerLength()));
    }
    for (int i = 0; i < boundary.size(); i++) {
        graph->addUndirectedEdge("category" + to_string(i + 1), sink, new ResidualEdge<int>(boundary.at(i), 0, new IntegerLength()), new ResidualEdge<int>(boundary.at(i), new IntegerLength()));
    }
    return graph;
}

bool suitable(const vector<Problem>& problems, vector<int> boundary) {
    for (int i = 0; i < boundary.size(); i++) {
        int total = 0;
        for (Problem problem : problems) {
            total += problem.findTotal((i + 1));
        }
        if (total < boundary.at(i)) {
            return false;
        }
    }
    return true;
}

int main() {
    fstream file;
    file.open("ProblemSetter.txt", ios::in);
    if (file.fail()) {
        cout << "file not reading" << endl;
    } else {
        while (true) {
            int categories, problems;
            file >> categories;
            file >> problems;
            vector<Problem> list = vector<Problem>();
            vector<int> boundary = vector<int>();
            WeightedGraph<string, int>* graph;
            if (categories != 0 && problems != 0) {
                for (int i = 0; i < categories; i++) {
                    int current;
                    file >> current;
                    boundary.push_back(current);
                }
                for (int i = 0; i < problems; i++) {
                    int category;
                    file >> category;
                    list.emplace_back((i + 1), category);
                    for (int j = 0; j < category; j++) {
                        int current;
                        file >> current;
                        list.at(list.size() - 1).addCategory(current);
                    }
                }
                graph = setGraph(list, boundary);
                if (suitable(list, boundary)) {
                    fordFulkerson(graph, list, boundary);
                } else {
                    cout << "0" << endl;
                }
            } else {
                break;
            }
        }
    }
}