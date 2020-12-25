//
// Created by Oğuz Kerem Yıldız on 25.12.2020.
//

#include <fstream>
#include "Graph/WeightedGraph.h"
#include "Graph/DoubleLength.h"
#include <iostream>
#include <vector>
#include "utility"

using namespace std;

double length(pair<double, double> first, pair<double, double> second) {
    double x = abs(first.first) - abs(second.first);
    double y = abs(first.second) - abs(second.second);
    return sqrt((x * x) + (y * y));
}

bool contains(vector<pair<int, double>> vector, pair<int, double> pair) {
    for (int i = 0; i < vector.size(); i++) {
        if (vector.at(i) == pair) {
            return true;
        }
    }
    return false;
}

WeightedGraph<int, double> addEdges(vector<pair<double, double>> coordinates) {
    LengthInterface<double> *lengthInterface = new DoubleLength();
    WeightedGraph<int, double> graph = WeightedGraph<int, double>(lengthInterface);
    for (int i = 0; i < coordinates.size(); i++) {
        pair<double, double> first = coordinates.at(i);
        for (int j = 0; j < coordinates.size(); j++) {
            pair<double, double> second = coordinates.at(j);
            if (second != first) {
                if (graph.containsKey(i)) {
                    if (!contains(graph.get(i), pair<int, double>(j, length(first, second)))) {
                        graph.addUndirectedEdge(i, j, length(first, second), length(first, second));
                    }
                } else {
                    graph.addUndirectedEdge(i, j, length(first, second), length(first, second));
                }
            }
        }
    }
    return graph;
}

int main() {
    fstream file;
    file.open("Freckles.txt", ios::in);
    if (file.fail()) {
        cout << "file not reading" << endl;
    } else {
        LengthInterface<double> *lengthInterface = new DoubleLength();
        WeightedGraph<int, double> graph = WeightedGraph<int, double>(lengthInterface);
        vector<pair<double, double>> coordinates = vector<pair<double, double>>();
        string times, sequence;
        double d1, d2;
        file >> times;
        for (int i = 0; i < stoi(times); i++) {
            file >> sequence;
            for (int j = 0; j < stoi(sequence); j++) {
                file >> d1;
                file >> d2;
                coordinates.emplace_back(d1, d2);
            }
            graph = addEdges(coordinates);
            cout << graph.kruskal() << endl;
        }
    }
}