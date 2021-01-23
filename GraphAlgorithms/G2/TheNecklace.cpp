//
// Created by Oğuz Kerem Yıldız on 23.01.2021.
//
#include <iostream>
#include <fstream>
#include <vector>
#include "Node.h"
#include "Graph/Graph.h"

using namespace std;

struct node_hash {
    size_t operator() (const Node& node) const {
        return node.getPair().first ^ node.getPair().second ^ node.getIndex();
    }
};

static bool finished;

void printVisited(vector<Node> visited) {
    cout << "[";
    for (int i = 0; i < visited.size(); i++) {
        Node n = visited.at(i);
        if (i != visited.size() - 1) {
            cout << "[" + to_string(n.getPair().first) + ", " + to_string(n.getPair().second) + "], ";
        } else {
            cout << "[" + to_string(n.getPair().first) + ", " + to_string(n.getPair().second) + "]";
        }
    }
    cout << "]" << endl;
}

void depthFirstSearch(Graph<Node, node_hash> graph, Node current, vector<Node> &visited, Node start) {
    if (finished) {
        return;
    }
    for (int i = 0; i < graph.get(current).size(); i++) {
        if (find(visited.begin(), visited.end(), graph.get(current, i)) == visited.end() && graph.containsKey(graph.get(current, i))) {
            visited.push_back(graph.get(current, i));
            if (visited.size() == graph.size() && graph.get(current, i) == start) {
                printVisited(visited);
                finished = true;
            } else {
                depthFirstSearch(graph, graph.get(current, i), visited, start);
                visited.erase(remove(visited.begin(), visited.end(), graph.get(current, i)), visited.end());
            }
        } else {
            if (visited.size() == graph.size() && graph.get(current, i) == start) {
                printVisited(visited);
                finished = true;
            }
        }
    }
}

void find(Graph<Node, node_hash> graph, Node node) {
    vector<Node> visited = vector<Node>();
    visited.push_back(node);
    depthFirstSearch(graph, node, visited, node);
    if (!finished) {
        cout << "some beads may be lost" << endl;
    }
}

Graph<Node, node_hash> addEdges(vector<Node> nodes) {
    Graph<Node, node_hash> graph = Graph<Node, node_hash>();
    for (Node node : nodes) {
        graph.put(node, vector<Node>());
        for (Node key : graph.getKeySet()) {
            if (key != node) {
                if (key.getPair().first == node.getPair().first || key.getPair().first == node.getPair().second || key.getPair().second == node.getPair().first || key.getPair().second == node.getPair().second) {
                    graph.addUnDirectedEdge(key, node);
                }
            }
        }
    }
    return graph;
}

int main() {
    fstream file;
    file.open("Necklace.txt", ios::in);
    if (file.fail()) {
        cout << "file not reading" << endl;
    } else {
        vector<Node> nodes = vector<Node>();
        Graph<Node, node_hash> graph;
        int times, size;
        file >> times;
        for (int i = 0; i < times; i++) {
            finished = false;
            file >> size;
            for (int j = 0; j < size; j++) {
                int first, second;
                file >> first;
                file >> second;
                nodes.emplace_back(j, pair<int, int>(first, second));
            }
            graph = addEdges(nodes);
            cout << "Case #" + to_string(i + 1) << endl;
            find(graph, nodes.at(0));
            graph.clear();
            nodes.clear();
        }
    }
}