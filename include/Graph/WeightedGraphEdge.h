//
// Created by Oğuz Kerem Yıldız on 1.02.2021.
//

#ifndef COOKIES_CPP_WEIGHTEDGRAPHEDGE_H
#define COOKIES_CPP_WEIGHTEDGRAPHEDGE_H
#include <unordered_map>
#include <unordered_set>
#include "LengthInterface.h"
#include <utility>
#include <vector>
#include "Edge.h"

using namespace std;

template<class Symbol, class Length> class WeightedGraphEdge {
private:
    unordered_map<Symbol, vector<pair<Symbol, Edge<Length>>>> edgeList;
    unordered_set<Symbol> vertexList;
    LengthInterface<Length> *lengthInterface;
    void depthFirstSearch(WeightedGraphEdge<Symbol, Length> &connectedComponent, Symbol i, unordered_map<Symbol, bool> &visited);
public:
    WeightedGraphEdge();
    WeightedGraphEdge(LengthInterface<Length> *lengthInterface);
    WeightedGraphEdge(unordered_set<Symbol> vertexList, LengthInterface<Length> *lengthInterface);
    void clear();
    bool isEmpty();
    bool containsKey(Symbol element);
    bool contains(Symbol element);
    void addDirectedEdge(Symbol from, Symbol to, Edge<Length> length);
    void addUndirectedEdge(Symbol from, Symbol to, Edge<Length> length);
    void addUndirectedEdge(Symbol from, Symbol to, Edge<Length> lengthFrom, Edge<Length> lengthTo);
    void put(Symbol index, vector<pair<Symbol, Edge<Length>>> list);
    int size();
    vector<Symbol> getKeySet();
    unordered_set<Symbol> getVertexList();
    vector<pair<Symbol, Edge<Length>>> get(Symbol index);
    pair<Symbol, Edge<Length>> get(Symbol element, int index);
    vector<WeightedGraphEdge<Symbol, Length>> connectedComponents();
    void setFlow(Symbol first, int index, Length length);
};

template<class Symbol, class Length> WeightedGraphEdge<Symbol, Length>::WeightedGraphEdge() = default;

template<class Symbol, class Length> WeightedGraphEdge<Symbol, Length>::WeightedGraphEdge(LengthInterface<Length> *lengthInterface) {
    edgeList = unordered_map<Symbol, vector<pair<Symbol, Edge<Length>>>>();
    vertexList = unordered_set<Symbol>();
    this->lengthInterface = lengthInterface;
}

template<class Symbol, class Length> WeightedGraphEdge<Symbol, Length>::WeightedGraphEdge(unordered_set<Symbol> vertexList, LengthInterface<Length> *lengthInterface) {
    edgeList = unordered_map<Symbol, vector<pair<Symbol, Edge<Length>>>>();
    this->vertexList = vertexList;
    this->lengthInterface = lengthInterface;
}

template<class Symbol, class Length> void WeightedGraphEdge<Symbol, Length>::clear() {
    edgeList.clear();
    vertexList.clear();
}

template<class Symbol, class Length> bool WeightedGraphEdge<Symbol, Length>::isEmpty() {
    return edgeList.empty();
}

template<class Symbol, class Length> bool WeightedGraphEdge<Symbol, Length>::containsKey(Symbol element) {
    return edgeList.find(element) != edgeList.end();
}

template<class Symbol, class Length> vector<WeightedGraphEdge<Symbol, Length>> WeightedGraphEdge<Symbol, Length>::connectedComponents() {
    vector<WeightedGraphEdge<Symbol, Length>> graphs = vector<WeightedGraphEdge<Symbol, Length>>();
    int i;
    unordered_map<Symbol, bool> visited = unordered_map<Symbol, bool>();
    for (Symbol vertex: vertexList) {
        visited[vertex] = false;
    }
    for (Symbol vertex: vertexList) {
        if (!visited[vertex]) {
            visited[vertex] = true;
            WeightedGraphEdge<Symbol, Length> connectedComponent = WeightedGraphEdge<Symbol, Length>(lengthInterface);
            depthFirstSearch(connectedComponent, vertex, visited);
            graphs.push_back(connectedComponent);
        }
    }
    return graphs;
}

template<class Symbol, class Length> void WeightedGraphEdge<Symbol, Length>::depthFirstSearch(WeightedGraphEdge<Symbol, Length> &connectedComponent, Symbol i, unordered_map<Symbol, bool> &visited) {
    if (containsKey(i)) {
        connectedComponent.put(i, get(i));
        for (pair<Symbol, Edge<Length>> toNode : get(i)) {
            if (!visited[toNode.first]) {
                visited[toNode.first] = true;
                depthFirstSearch(connectedComponent, toNode.first, visited);
            }
        }
    }
}

template<class Symbol, class Length> vector<pair<Symbol, Edge<Length>>> WeightedGraphEdge<Symbol, Length>::get(Symbol index) {
    return edgeList[index];
}

template<class Symbol, class Length> void WeightedGraphEdge<Symbol, Length>::put(Symbol index, vector<pair<Symbol, Edge<Length>>> list) {
    vertexList.insert(index);
    edgeList[index] = list;
    if (list.size() > 0) {
        for (pair<Symbol, Edge<Length>> element : list) {
            vertexList.insert(element.first);
        }
    }
}

template<class Symbol, class Length> bool WeightedGraphEdge<Symbol, Length>::contains(Symbol element) {
    return vertexList.find(element) != vertexList.end();
}

template<class Symbol, class Length> void WeightedGraphEdge<Symbol, Length>::addDirectedEdge(Symbol from, Symbol to, Edge<Length> length) {
    vertexList.insert(from);
    vertexList.insert(to);
    if (edgeList.find(from) == edgeList.end()) {
        edgeList[from] = vector<pair<Symbol, Edge<Length>>>();
        edgeList[from].push_back(pair<Symbol, Edge<Length>>(to, length));
    } else {
        edgeList[from].push_back(pair<Symbol, Edge<Length>>(to, length));
    }
}

template<class Symbol, class Length> void WeightedGraphEdge<Symbol, Length>::addUndirectedEdge(Symbol from, Symbol to, Edge<Length> length) {
    addDirectedEdge(from, to, length);
    addDirectedEdge(to, from, length);
}

template<class Symbol, class Length> pair<Symbol, Edge<Length>> WeightedGraphEdge<Symbol, Length>::get(Symbol element, int index) {
    return edgeList[element].at(index);
}

template<class Symbol, class Length> int WeightedGraphEdge<Symbol, Length>::size() {
    return edgeList.size();
}

template<class Symbol, class Length> unordered_set<Symbol> WeightedGraphEdge<Symbol, Length>::getVertexList() {
    return vertexList;
}

template<class Symbol, class Length> void WeightedGraphEdge<Symbol, Length>::addUndirectedEdge(Symbol from, Symbol to, Edge<Length> lengthFrom, Edge<Length> lengthTo) {
    addDirectedEdge(from, to, lengthTo);
    addDirectedEdge(to, from, lengthFrom);
}

template<class Symbol, class Length> vector<Symbol> WeightedGraphEdge<Symbol, Length>::getKeySet() {
    vector<Symbol> keySet = vector<Symbol>();
    for (auto& key : edgeList) {
        keySet.push_back(key.first);
    }
    return keySet;
}

template<class Symbol, class Length> void WeightedGraphEdge<Symbol, Length>::setFlow(Symbol first, int index, Length length) {
    edgeList[first].at(index).second.setFlow(length);
}

#endif //COOKIES_CPP_WEIGHTEDGRAPHEDGE_H
