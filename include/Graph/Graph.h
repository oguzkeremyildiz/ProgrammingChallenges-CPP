//
// Created by Oğuz Kerem Yıldız on 24.12.2020.
//

#ifndef COOKIES_CPP_GRAPH_H
#define COOKIES_CPP_GRAPH_H
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <utility>

using namespace std;

template<class Symbol> class Graph {
private:
    unordered_set<Symbol> vertexList;
    unordered_map<Symbol, vector<Symbol>> edgeList;
    void depthFirstSearch(Graph<Symbol> &connectedComponent, Symbol i, unordered_map<Symbol, bool> &visited);
public:
    Graph();
    Graph(unordered_set<Symbol> vertexList);
    bool containsKey(Symbol element);
    bool contains(Symbol element);
    bool isEmpty();
    int size();
    void put(Symbol index, vector<Symbol> list);
    vector<Symbol> get(Symbol index);
    Symbol get(Symbol element, int index);
    void addDirectedEdge(Symbol from, Symbol to);
    void addUnDirectedEdge(Symbol from, Symbol to);
    void clear();
    vector<vector<Symbol>> getValues();
    vector<Symbol> getKeySet();
    unordered_set<Symbol> getVertexList();
    vector<Graph<Symbol>> connectedComponents();
};

template<class Symbol> Graph<Symbol>::Graph() {
    edgeList = unordered_map<Symbol, vector<Symbol>>();
    vertexList = unordered_set<Symbol>();
}

template<class Symbol> Graph<Symbol>::Graph(unordered_set<Symbol> vertexList) {
    edgeList = unordered_map<Symbol, vector<Symbol>>();
    this->vertexList = vertexList;
}

template<class Symbol> bool Graph<Symbol>::containsKey(Symbol element) {
    return edgeList.find(element) != edgeList.end();
}

template<class Symbol> bool Graph<Symbol>::contains(Symbol element) {
    return vertexList.find(element) != vertexList.end();
}

template<class Symbol> bool Graph<Symbol>::isEmpty() {
    return edgeList.empty();
}

template<class Symbol> int Graph<Symbol>::size() {
    return edgeList.size();
}

template<class Symbol> void Graph<Symbol>::put(Symbol index, vector<Symbol> list) {
    vertexList.insert(index);
    edgeList[index] = list;
    if (list.size() > 0) {
        for (Symbol element : list) {
            vertexList.insert(element);
        }
    }
}

template<class Symbol> vector<Symbol> Graph<Symbol>::get(Symbol index) {
    return edgeList[index];
}

template<class Symbol> Symbol Graph<Symbol>::get(Symbol element, int index) {
    return edgeList[element].at(index);
}

template<class Symbol> void Graph<Symbol>::addDirectedEdge(Symbol from, Symbol to) {
    vertexList.insert(from);
    vertexList.insert(to);
    edgeList[from].push_back(to);
}

template<class Symbol> void Graph<Symbol>::addUnDirectedEdge(Symbol from, Symbol to) {
    addDirectedEdge(from, to);
    addDirectedEdge(to, from);
}

template<class Symbol> void Graph<Symbol>::clear() {
    edgeList.clear();
    vertexList.clear();
}

template<class Symbol> vector<vector<Symbol>> Graph<Symbol>::getValues() {
    vector<vector<Symbol>> values = vector<vector<Symbol>>();
    for (auto& key : edgeList) {
        values.push_back(key.second);
    }
    return values;
}

template<class Symbol> vector<Symbol> Graph<Symbol>::getKeySet() {
    vector<Symbol> keySet = vector<Symbol>();
    for (auto& key : edgeList) {
        keySet.push_back(key.first);
    }
    return keySet;
}

template<class Symbol> unordered_set<Symbol> Graph<Symbol>::getVertexList() {
    return vertexList;
}

template<class Symbol> vector<Graph<Symbol>> Graph<Symbol>::connectedComponents() {
    vector<Graph<Symbol>> graphs = vector<Graph<Symbol>>();
    int i;
    unordered_map<Symbol, bool> visited = unordered_map<Symbol, bool>();
    for (Symbol vertex: vertexList) {
        visited[vertex] = false;
    }
    for (Symbol vertex: vertexList) {
        if (!visited[vertex]) {
            visited[vertex] = true;
            Graph<Symbol> connectedComponent = Graph<Symbol>();
            depthFirstSearch(connectedComponent, vertex, visited);
            if (!connectedComponent.isEmpty()) {
                graphs.push_back(connectedComponent);
            }
        }
    }
    return graphs;
}

template<class Symbol> void Graph<Symbol>::depthFirstSearch(Graph<Symbol> &connectedComponents, Symbol i, unordered_map<Symbol, bool> &visited) {
    if (containsKey(i)) {
        connectedComponents.put(i, get(i));
        for (Symbol toNode : get(i)) {
            if (!visited[toNode]) {
                visited[toNode] = true;
                depthFirstSearch(connectedComponents, toNode, visited);
            }
        }
    }
}
#endif //COOKIES_CPP_GRAPH_H
