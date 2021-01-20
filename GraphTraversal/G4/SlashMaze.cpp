//
// Created by Oğuz Kerem Yıldız on 20.01.2021.
//
#include <unordered_set>
#include <vector>
#include <iostream>
#include <fstream>
#include "Graph/Graph.h"

using namespace std;

template <class T>
inline void hash_combine(std::size_t & seed, const T & v)
{
    std::hash<T> hasher;
    seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

template <typename C> struct ContainerHasher
{
    typedef typename C::value_type value_type;
    inline size_t operator()(const C & c) const
    {
        size_t seed = 0;
        for (typename C::const_iterator it = c.begin(), end = c.end(); it != end; ++it)
        {
            hash_combine<value_type>(seed, *it);
        }
        return seed;
    }
};

static unordered_set<unordered_set<int>, ContainerHasher<unordered_set<int>>> founded;

unordered_set<int> addAll(vector<int> v) {
    unordered_set<int> set = unordered_set<int>();
    for (int i = 0; i < v.size(); ++i) {
        set.insert(v.at(i));
    }
    return set;
}

vector<int> breadthFirstSearch(Graph<int> graph, int current, unordered_set<int> &visited, int iterate, int target, vector<int> &list) {
    for (int i = 0; i < graph.get(current).size(); i++) {
        unordered_set<int> elements = addAll(graph.get(current));
        if (elements.find(target) != elements.end() && iterate > 2) {
            if (founded.find(visited) == founded.end()) {
                list.push_back(visited.size());
                founded.insert(visited);
                return list;
            }
        }
        if (visited.find(graph.get(current).at(i)) == visited.end()) {
            visited.insert(graph.get(current).at(i));
            iterate++;
            breadthFirstSearch(graph, graph.get(current).at(i), visited, iterate, target, list);
            iterate--;
        }
    }
    return list;
}

unordered_set<int> find(Graph<int> graph) {
    unordered_set<int> circulars = unordered_set<int>();
    unordered_set<int> visited = unordered_set<int>();
    for (int i = 1; i <= graph.size(); i++) {
        visited.insert(i);
        vector<int> empty;
        vector<int> v = breadthFirstSearch(graph, i, visited, 0, i, empty);
        circulars.insert(v.begin(), v.end());
        visited.clear();
    }
    return circulars;
}

Graph<int> addEdge(string **maze, int *squares, unordered_set<int> set, int squaresLength, int maze1Length, int maze2Length) {
    int current = 0;
    bool boolean = true;
    Graph<int> graph = Graph<int>();
    for (int i = 0; i < squaresLength; i++) {
        graph.put(i + 1, vector<int>());
    }
    for (int i = 0; i < maze1Length; i++) {
        for (int j = 0; j < maze2Length; j++) {
            if (set.find(squares[current]) == set.end()) {
                if (i + 1 < maze1Length) {
                    i++;
                    j = 0;
                } else {
                    boolean = false;
                    break;
                }
            }
            while (set.find(squares[current]) == set.end()) {
                current++;
                if (current == squaresLength) {
                    boolean = false;
                    break;
                }
            }
            if (boolean) {
                if (set.find(squares[current]) != set.end()) {
                    if (maze[i][j] == "/") {
                        if (j + 1 < maze2Length) {
                            if (maze[i][j + 1] == "/") {
                                if (current + maze2Length - 1 < squaresLength) {
                                    graph.addUnDirectedEdge(squares[current], squares[current + maze2Length - 1]);
                                }
                                if (current - maze2Length + 1 > 0) {
                                    graph.addUnDirectedEdge(squares[current], squares[current - maze2Length + 1]);
                                }
                            } else if (current + maze2Length - 1 < squaresLength) {
                                graph.addUnDirectedEdge(squares[current], squares[current + maze2Length - 1]);
                                if (current + maze2Length < squaresLength) {
                                    graph.addUnDirectedEdge(squares[current], squares[current + maze2Length]);
                                }
                            }
                        }
                    } else {
                        if (j + 1 < maze2Length) {
                            if (maze[i][j + 1] != "/") {
                                if (current + maze2Length < squaresLength) {
                                    graph.addUnDirectedEdge(squares[current], squares[current + maze2Length]);
                                }
                            } else {
                                if (current - maze2Length + 1 > 0) {
                                    graph.addUnDirectedEdge(squares[current], squares[current - maze2Length + 1]);
                                }
                            }
                        }
                        if (current - maze2Length > 0) {
                            graph.addUnDirectedEdge(squares[current], squares[current - maze2Length]);
                        }
                    }
                }
                if (current + 1 != squaresLength) {
                    current++;
                } else {
                    boolean = false;
                    break;
                }
            } else {
                break;
            }
        }
        if (!boolean) {
            break;
        }
    }
    return graph;
}

int main() {
    fstream file;
    file.open("Maze.txt", ios::in);
    if (file.fail()) {
        cout << "file not reading" << endl;
    } else {
        Graph<int> graph;
        unordered_set<int> set = unordered_set<int>();
        founded = unordered_set<unordered_set<int>, ContainerHasher<unordered_set<int>>>();
        unordered_set<int> connectedGraphs;
        int current = 1;
        while (!file.eof()) {
            string **maze;
            int row, column;
            file >> row;
            file >> column;
            int total = 0, added = 0;
            for (int i = 0; i < (column * 2) - 1; i++) {
                if (i % 2 == 0) {
                    for (int j = 0; j < row - 1; j++) {
                        added++;
                        set.insert(added);
                    }
                    total += row - 1;
                } else {
                    added += row;
                    total += row;
                }
            }
            int *squares = (int *)calloc(total, sizeof(int));
            for (int i = 0; i < total; i++) {
                squares[i] = i + 1;
            }
            if (row != 0 && column != 0) {
                maze = (string **)calloc(column, sizeof(string *));
                for (int i = 0; i < column; ++i) {
                    maze[i] = (string*) calloc(row, sizeof(string));
                }
                for (int i = 0; i < column; i++) {
                    for (int j = 0; j < row; j++) {
                        file >> maze[i][j];
                    }
                }
                graph = addEdge(maze, squares, set, total, column, row);
                connectedGraphs = find(graph);
                cout << "Maze #" + to_string(current) + ":" << endl;
                if (!connectedGraphs.empty()) {
                    int size = 0;
                    for (int connectedGraph : connectedGraphs) {
                        if (connectedGraph > size) {
                            size = connectedGraph;
                        }
                    }
                    cout << to_string(connectedGraphs.size()) + " Cycles; the longest has length " + to_string(size) + "." << endl;
                } else {
                    cout << "There are no cycles." << endl;
                }
                graph.clear();
                connectedGraphs.clear();
                set.clear();
                founded.clear();
                current++;
            }
        }
    }
}