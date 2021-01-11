//
// Created by Oğuz Kerem Yıldız on 11.01.2021.
//
#include <iostream>
#include <vector>
#include <unordered_set>
#include <fstream>
#include <utility>
#include "Tuple/Triplet.h"
#include "Graph/WeightedGraph.h"
#include "Graph/IntegerLength.h"
#include "Graph/LengthInterface.h"

using namespace std;

static vector<Triplet<int, int, int>> outputs;
static unordered_set<int> visited;

void printBestOutput() {
    Triplet<int, int, int> best = Triplet<int, int, int>(INT_MAX, INT_MAX, INT_MAX);
    for (Triplet<int, int, int> output : outputs) {
        if (best.getA() == INT_MAX) {
            best = output;
        } else {
            if (best.getB() < output.getB()) {
                best = output;
            }
        }
    }
    cout << "[" + to_string(best.getA()) + ", " + to_string(best.getB()) + ", " + to_string(best.getC()) + "]" << endl;
}

vector<Triplet<int, int, int>> addOutput(vector<Triplet<int, int, int>> &sequence, int finish) {
    vector<Triplet<int, int, int>> output = vector<Triplet<int, int, int>>();
    for (Triplet<int, int, int> integerIntegerIntegerTriplet : sequence) {
        if (integerIntegerIntegerTriplet.getA() == finish) {
            output.push_back(integerIntegerIntegerTriplet);
        }
    }
    for (auto & i : output) {
        sequence.erase(remove(sequence.begin(), sequence.end(), i), sequence.end());
    }
    return output;
}

void next(WeightedGraph<int, int> &graph, vector<pair<int, int>> &currentEdge, int index, int finish, int max, int length) {
    vector<Triplet<int, int, int>> sequence = vector<Triplet<int, int, int>>();
    for (pair<int, int> nextEdge : currentEdge) {
        if (visited.find(nextEdge.first) == visited.end()) {
            if (length > nextEdge.second) {
                if (nextEdge.second > max) {
                    sequence.emplace_back(nextEdge.first, max, index);
                } else {
                    sequence.emplace_back(nextEdge.first, nextEdge.second, index);
                }
            } else {
                if (length > max) {
                    sequence.emplace_back(nextEdge.first, max, index);
                } else {
                    sequence.emplace_back(nextEdge.first, length, index);
                }
            }
        }
    }
    vector<Triplet<int, int, int>> v = addOutput(sequence, finish);
    outputs.insert(outputs.end(), v.begin(), v.end());
    if (!sequence.empty() || visited.size() != graph.size()) {
        for (Triplet<int, int, int> element : sequence) {
            visited.insert(element.getA());
            vector<pair<int, int>> c = graph.get(element.getA());
            next(graph, c, index + 1, finish, max, element.getB());
        }
    }
}

void breadthFirstSearch(WeightedGraph<int, int> &graph, int start, int finish, int max) {
    outputs = vector<Triplet<int, int, int>>();
    visited = unordered_set<int>();
    visited.insert(1);
    int index = 2;
    vector<pair<int, int>> s = graph.get(start);
    next(graph, s, index, finish, max, graph.get(graph.getKeySet().at(graph.getKeySet().size() - 1), 0).second);
    printBestOutput();
}

int main() {
    fstream file;
    file.open("Guide.txt", ios::in);
    if (file.fail()) {
        cout << "file not reading" << endl;
    } else {
        int vertexSize = 1000;
        int times = 1000;
        int from, to, length, start, finish, max, scenario = 0;
        LengthInterface<int> *lengthInterface = new IntegerLength();
        WeightedGraph<int, int> graph = WeightedGraph<int, int>(lengthInterface);
        outputs = vector<Triplet<int, int, int>>();
        while (vertexSize != 0 || times != 0) {
            scenario++;
            file >> vertexSize;
            file >> times;
            if (vertexSize != 0 || times != 0) {
                for (int i = 1; i <= vertexSize; i++) {
                    graph.put(i, vector<pair<int, int>>());
                }
                for (int i = 0; i < times; i++) {
                    file >> from;
                    file >> to;
                    file >> length;
                    graph.addUndirectedEdge(from, to, length, length);
                }
                file >> start;
                file >> finish;
                file >> max;
                cout << "Scenario #" + to_string(scenario) << endl;
                breadthFirstSearch(graph, start, finish, max);
                outputs.clear();
                graph.clear();
            }
        }
    }
}