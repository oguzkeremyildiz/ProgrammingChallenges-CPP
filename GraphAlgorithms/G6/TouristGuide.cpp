//
// Created by Oğuz Kerem Yıldız on 19.01.2021.
//
#include <fstream>
#include <iostream>
#include <vector>
#include "Graph/Graph.h"
#include <utility>
#include <unordered_set>

using namespace std;

struct pair_hash
{
    template <class T1, class T2>
    std::size_t operator() (const std::pair<T1, T2> &pair) const
    {
        return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
    }
};

static vector<vector<string>> list;
static unordered_set<string> stringVisited;

vector<string> clone(vector<string> v) {
    vector<string> returning = vector<string>();
    for (int i = 0; i < v.size(); ++i) {
        returning.push_back(v.at(i));
    }
    return returning;
}

vector<string> findCamera(vector<vector<string>> paths, const string& start, const string& finish) {
    vector<string> vec = vector<string>();
    if (paths.size() > 1) {
        for (int i = 0; i < paths.at(0).size(); i++) {
            bool boolean = true;
            for (int j = 1; j < paths.size(); j++) {
                if (find(paths.at(j).begin(), paths.at(j).end(), paths.at(0).at(i)) == paths.at(j).end()) {
                    boolean = false;
                    break;
                }
            }
            if (boolean) {
                if (paths.at(0).at(i) != start && paths.at(0).at(i) != finish) {
                    vec.push_back(paths.at(0).at(i));
                }
            }
        }
    } else if (paths.size() == 1) {
        for (int i = 0; i < paths.at(0).size(); i++) {
            string current = paths.at(0).at(i);
            if (current != start && current != finish) {
                vec.push_back(current);
            }
        }
    }
    return vec;
}

vector<vector<string>> depthFirstSearch(Graph<string> graph, const string& start, const string& finish, vector<string> &sequence) {
    for (int i = 0; i < graph.get(start).size(); i++) {
        if (stringVisited.find(graph.get(start, i)) == stringVisited.end()) {
            stringVisited.insert(graph.get(start, i));
            sequence.push_back(graph.get(start, i));
            if (graph.get(start, i) != finish) {
                depthFirstSearch(graph, graph.get(start, i), finish, sequence);
            } else {
                list.push_back(clone(sequence));
            }
            sequence.pop_back();
            stringVisited.clear();
            stringVisited.insert(sequence.begin(), sequence.end());
        }
    }
    return list;
}

void find(Graph<string> graph, unordered_set<string> &cameras) {
    vector<vector<string>> paths;
    unordered_set<pair<string, string>, pair_hash> visited = unordered_set<pair<string, string>, pair_hash>();
    for (const string& key1 : graph.getKeySet()) {
        for (const string& key2 : graph.getKeySet()) {
            if (key1 != key2 && visited.find(pair<string, string>(key1, key2)) == visited.end()) {
                visited.insert(pair<string, string>(key1, key2));
                visited.insert(pair<string, string>(key2, key1));
                list = vector<vector<string>>();
                stringVisited = unordered_set<string>();
                vector<string> v;
                paths = depthFirstSearch(graph, key1, key2, v);
                vector<string> currentCameras = findCamera(paths, key1, key2);
                cameras.insert(currentCameras.begin(), currentCameras.end());
            }
        }
    }
}

int main() {
    fstream file;
    file.open("Tourist.txt", ios::in);
    if (file.fail()) {
        cout << "file not reading" << endl;
    } else {
        Graph<string> graph = Graph<string>();
        int iterate = 0;
        while (!file.eof()) {
            iterate++;
            string graphSize;
            file >> graphSize;
            if (graphSize != "0") {
                for (int i = 0; i < stoi(graphSize); i++) {
                    string edge;
                    file >> edge;
                    graph.put(edge, vector<string>());
                }
                string edges;
                file >> edges;
                for (int i = 0; i < stoi(edges); i++) {
                    string from, to;
                    file >> from;
                    file >> to;
                    graph.addUnDirectedEdge(from, to);
                }
                vector<Graph<string>> graphs = graph.connectedComponents();
                unordered_set<string> cameras = unordered_set<string>();
                unordered_set<string> allCameras = unordered_set<string>();
                for (const Graph<string>& stringGraph : graphs) {
                    find(stringGraph, cameras);
                    allCameras.insert(cameras.begin(), cameras.end());
                }
                cout << "City map #" + to_string(iterate) + ": " + to_string(allCameras.size()) + " camera(s) found" << endl;
                for (const string& camera : allCameras) {
                    cout << camera << endl;
                }
                graph.clear();
                graphs.clear();
                cameras.clear();
                allCameras.clear();
            } else {
                break;
            }
        }
    }
}