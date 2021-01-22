//
// Created by Oğuz Kerem Yıldız on 22.01.2021.
//
#include <iostream>
#include <utility>
#include <fstream>
#include "Cube.h"
#include "Graph/Graph.h"
#include "Tuple/Triplet.h"
#include <vector>

using namespace std;

struct cube_hash {
    size_t operator() (const Cube& cube) const {
        return hash<int>()(cube.getWeight()) ^ std::hash<int>()(cube.getBottom()) ^ hash<int>()(cube.getTop()) ^ hash<int>()(cube.getRight()) ^ hash<int>()(cube.getLeft()) ^ hash<int>()(cube.getFront()) ^ hash<int>()(cube.getBack());
    }
};

static vector<pair<int, string>> bestList;

string pairString(const pair<int, string>& p) {
    return "[" + to_string(p.first) + ", " + p.second + "]";
}

Graph<Cube, cube_hash> addEdge(vector<Cube> cubes) {
    Graph<Cube, cube_hash> graph = Graph<Cube, cube_hash>();
    for (int i = 0; i < cubes.size(); i++) {
        graph.put(cubes.at(i), vector<Cube>());
        if (i + 1 < cubes.size()) {
            for (int j = i + 1; j < cubes.size(); j++) {
                graph.addDirectedEdge(cubes.at(i), cubes.at(j));
            }
        }
    }
    return graph;
}

string convertToString(int i) {
    string str;
    switch (i) {
        case 0:
            str = "front";
            break;
        case 1:
            str = "back";
            break;
        case 2:
            str = "left";
            break;
        case 3:
            str = "right";
            break;
        case 4:
            str = "top";
            break;
        case 5:
            str = "bottom";
            break;
        default:
            break;
    }
    return str;
}

vector<pair<int, string>> search(Graph<Cube, cube_hash> graph, vector<Cube> current, vector<pair<int, string>> &list, Triplet<int, int, int> now, int reverse) {
    for (Cube cube : current) {
        if (cube.containsElement(reverse)) {
            for (int j = 0; j < 6; j++) {
                if (cube.get(j) == reverse) {
                    vector<pair<int, string>> oldList = vector<pair<int, string>>(list.begin(), list.end());
                    list.emplace_back(cube.getWeight(), convertToString(j));
                    if (!graph.get(cube).empty()) {
                        search(graph, graph.get(cube), list, Triplet<int, int, int>(cube.getWeight(), cube.getReverse(j).first, cube.getReverse(j).second), cube.getReverse(j).first);
                    }
                    if (bestList.size() < list.size()) {
                        bestList.clear();
                        bestList.insert(bestList.end(), list.begin(), list.end());
                    }
                    list.clear();
                    list.insert(list.end(), oldList.begin(), oldList.end());
                }
            }
        }
    }
    return bestList;
}

vector<pair<int, string>> find(Graph<Cube, cube_hash> graph) {
    vector<pair<int, string>> best = vector<pair<int, string>>();
    vector<pair<int, string>> currentBest;
    vector<pair<int, string>> start = vector<pair<int, string>>();
    int iteration = 0;
    for (Cube key : graph.getKeySet()) {
        for (int i = 0; i < 6; i++) {
            start.emplace_back(key.getWeight(), convertToString(i));
            currentBest = search(graph, graph.get(key), start, Triplet<int, int, int>(key.getWeight(), key.get(i), i), key.getReverse(i).first);
            start.clear();
            if (currentBest.size() > best.size()) {
                best.clear();
                best.insert(best.end(), currentBest.begin(), currentBest.end());
            }
            currentBest.clear();
        }
        iteration++;
        if (best.size() >= graph.size() - iteration) {
            return best;
        }
    }
    return best;
}

int main() {
    fstream file;
    file.open("Cubes.txt", ios::in);
    if (file.fail()) {
        cout << "file not reading" << endl;
    } else {
        vector<Cube> cubes = vector<Cube>();
        vector<pair<int, string>> list;
        bestList = vector<pair<int, string>>();
        Graph<Cube, cube_hash> graph;
        int times = 10000;
        int count = 1;
        while (times != 0) {
            int weight = 1;
            file >> times;
            if (times > 0) {
                for (int i = 0; i < times; i++) {
                    Cube cube = Cube(0, 0, 0, 0, 0, 0, weight);
                    for (int j = 0; j < 6; j++) {
                        int current;
                        file >> current;
                        cube.add(j, current);
                    }
                    cubes.push_back(cube);
                    weight++;
                }
                graph = addEdge(cubes);
                cout << "Case #" + to_string(count) << endl;
                list = find(graph);
                cout << list.size() << endl;
                for (const pair<int, string>& integerStringPair : list) {
                    cout << pairString(integerStringPair) << endl;
                }
                graph.clear();
                cubes.clear();
                list.clear();
                bestList.clear();
                count++;
            }
        }
    }
}