//
// Created by Oğuz Kerem Yıldız on 25.12.2020.
//

#ifndef COOKIES_CPP_WEIGHTEDGRAPH_H
#define COOKIES_CPP_WEIGHTEDGRAPH_H
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <utility>
#include "../Tuple/Triplet.h"
#include "../Set/DisjointSet.h"
#include "../Graph/LengthInterface.h"
#include <iostream>

using namespace std;

template<class...> class WeightedGraph;

template<class Symbol, class Length, class sizet> class WeightedGraph<Symbol, Length, sizet> {
private:
    unordered_map<Symbol, vector<pair<Symbol, Length>>, sizet> edgeList;
    unordered_set<Symbol, sizet> vertexList;
    LengthInterface<Length> *lengthInterface;
    bool containsAll(unordered_set<Symbol, sizet> elements);
    pair<bool, int> containsElement(Symbol edge, Symbol element);
    Symbol findMinimum(unordered_set<Symbol, sizet> visited, unordered_map<Symbol, pair<Length, Symbol>, sizet> map);
    void depthFirstSearch(WeightedGraph<Symbol, Length, sizet> &connectedComponent, Symbol i, unordered_map<Symbol, bool, sizet> &visited);
public:
    WeightedGraph();
    WeightedGraph(LengthInterface<Length> *lengthInterface);
    WeightedGraph(unordered_set<Symbol, sizet> vertexList, LengthInterface<Length> *lengthInterface);
    void clear();
    bool isEmpty();
    bool containsKey(Symbol element);
    bool contains(Symbol element);
    void addDirectedEdge(Symbol from, Symbol to, Length length);
    void addUndirectedEdge(Symbol from, Symbol to, Length length);
    void addUndirectedEdge(Symbol from, Symbol to, Length lengthFrom, Length lengthTo);
    vector<Symbol> getKeySet();
    unordered_set<Symbol, sizet> getVertexList();
    int size();
    void put(Symbol index, vector<pair<Symbol, Length>> list);
    vector<pair<Symbol, Length>> get(Symbol symbol);
    pair<Symbol, Length> get(Symbol element, int index);
    unordered_map<Symbol, pair<Length, Symbol>, sizet> bellmanFord(Symbol edge);
    vector<vector<Length>> floydWarshall();
    Length prims();
    unordered_map<Symbol, pair<Length, Symbol>, sizet> dijkstra(Symbol edge);
    vector<WeightedGraph<Symbol, Length, sizet>> connectedComponents();
};

template<class Symbol, class Length> class WeightedGraph<Symbol, Length> {
private:
    unordered_map<Symbol, vector<pair<Symbol, Length>>> edgeList;
    unordered_set<Symbol> vertexList;
    LengthInterface<Length> *lengthInterface;
    unordered_map<int, Symbol> invert(unordered_map<Symbol, int> map);
    bool containsAll(unordered_set<Symbol> elements);
    vector<Triplet<Symbol, Symbol, Length>> sort(vector<Triplet<Symbol, Symbol, Length>> list);
    pair<bool, int> containsElement(Symbol edge, Symbol element);
    Symbol findMinimum(unordered_set<Symbol> visited, unordered_map<Symbol, pair<Length, Symbol>> map);
    void depthFirstSearch(WeightedGraph<Symbol, Length> &connectedComponent, Symbol i, unordered_map<Symbol, bool> &visited);
public:
    WeightedGraph();
    WeightedGraph(LengthInterface<Length> *lengthInterface);
    WeightedGraph(unordered_set<Symbol> vertexList, LengthInterface<Length> *lengthInterface);
    void clear();
    bool isEmpty();
    bool containsKey(Symbol element);
    bool contains(Symbol element);
    void addDirectedEdge(Symbol from, Symbol to, Length length);
    void addUndirectedEdge(Symbol from, Symbol to, Length length);
    void addUndirectedEdge(Symbol from, Symbol to, Length lengthFrom, Length lengthTo);
    vector<Symbol> getKeySet();
    unordered_set<Symbol> getVertexList();
    int size();
    void put(Symbol index, vector<pair<Symbol, Length>> list);
    vector<pair<Symbol, Length>> get(Symbol symbol);
    pair<Symbol, Length> get(Symbol element, int index);
    unordered_map<Symbol, pair<Length, Symbol>> bellmanFord(Symbol edge);
    vector<vector<Length>> floydWarshall();
    pair<unordered_map<int, Symbol>, vector<vector<Length>>> floydWarshallWithKeys();
    Length prims();
    Length kruskal();
    unordered_map<Symbol, pair<Length, Symbol>> dijkstra(Symbol edge);
    vector<WeightedGraph<Symbol, Length>> connectedComponents();
};

template<class Symbol, class Length, class sizet> WeightedGraph<Symbol, Length, sizet>::WeightedGraph() = default;

template<class Symbol, class Length> WeightedGraph<Symbol, Length>::WeightedGraph() = default;

template<class Symbol, class Length, class sizet> WeightedGraph<Symbol, Length, sizet>::WeightedGraph(LengthInterface<Length> *lengthInterface) {
    edgeList = unordered_map<Symbol, vector<pair<Symbol, Length>>, sizet>();
    vertexList = unordered_set<Symbol, sizet>();
    this->lengthInterface = lengthInterface;
}

template<class Symbol, class Length> WeightedGraph<Symbol, Length>::WeightedGraph(LengthInterface<Length> *lengthInterface) {
    edgeList = unordered_map<Symbol, vector<pair<Symbol, Length>>>();
    vertexList = unordered_set<Symbol>();
    this->lengthInterface = lengthInterface;
}

template<class Symbol, class Length, class sizet> WeightedGraph<Symbol, Length, sizet>::WeightedGraph(unordered_set<Symbol, sizet> vertexList, LengthInterface<Length> *lengthInterface) {
    edgeList = unordered_map<Symbol, vector<pair<Symbol, Length>>, sizet>();
    this->vertexList = vertexList;
    this->lengthInterface = lengthInterface;
}

template<class Symbol, class Length> WeightedGraph<Symbol, Length>::WeightedGraph(unordered_set<Symbol> vertexList, LengthInterface<Length> *lengthInterface) {
    edgeList = unordered_map<Symbol, vector<pair<Symbol, Length>>>();
    this->vertexList = vertexList;
    this->lengthInterface = lengthInterface;
}

template<class Symbol, class Length, class sizet> void WeightedGraph<Symbol, Length, sizet>::clear() {
    edgeList.clear();
    vertexList.clear();
}

template<class Symbol, class Length> void WeightedGraph<Symbol, Length>::clear() {
    edgeList.clear();
    vertexList.clear();
}

template<class Symbol, class Length, class sizet> bool WeightedGraph<Symbol, Length, sizet>::isEmpty() {
    return edgeList.empty();
}

template<class Symbol, class Length> bool WeightedGraph<Symbol, Length>::isEmpty() {
    return edgeList.empty();
}

template<class Symbol, class Length, class sizet> bool WeightedGraph<Symbol, Length, sizet>::containsKey(Symbol element) {
    return edgeList.find(element) != edgeList.end();
}

template<class Symbol, class Length> bool WeightedGraph<Symbol, Length>::containsKey(Symbol element) {
    return edgeList.find(element) != edgeList.end();
}

template<class Symbol, class Length, class sizet> bool WeightedGraph<Symbol, Length, sizet>::contains(Symbol element) {
    return vertexList.find(element) != vertexList.end();
}

template<class Symbol, class Length> bool WeightedGraph<Symbol, Length>::contains(Symbol element) {
    return vertexList.find(element) != vertexList.end();
}

template<class Symbol, class Length, class sizet> void WeightedGraph<Symbol, Length, sizet>::addDirectedEdge(Symbol from, Symbol to, Length length) {
    vertexList.insert(from);
    vertexList.insert(to);
    edgeList[from].push_back(pair<Symbol, Length>(to, length));
}

template<class Symbol, class Length> void WeightedGraph<Symbol, Length>::addDirectedEdge(Symbol from, Symbol to, Length length) {
    vertexList.insert(from);
    vertexList.insert(to);
    edgeList[from].push_back(pair<Symbol, Length>(to, length));
}

template<class Symbol, class Length, class sizet> void WeightedGraph<Symbol, Length, sizet>::addUndirectedEdge(Symbol from, Symbol to, Length length) {
    addDirectedEdge(from, to, length);
    addDirectedEdge(to, from, length);
}

template<class Symbol, class Length> void WeightedGraph<Symbol, Length>::addUndirectedEdge(Symbol from, Symbol to, Length length) {
    addDirectedEdge(from, to, length);
    addDirectedEdge(to, from, length);
}

template<class Symbol, class Length, class sizet> void WeightedGraph<Symbol, Length, sizet>::addUndirectedEdge(Symbol from, Symbol to, Length lengthFrom, Length lengthTo) {
    addDirectedEdge(from, to, lengthTo);
    addDirectedEdge(to, from, lengthFrom);
}

template<class Symbol, class Length> void WeightedGraph<Symbol, Length>::addUndirectedEdge(Symbol from, Symbol to, Length lengthFrom, Length lengthTo) {
    addDirectedEdge(from, to, lengthTo);
    addDirectedEdge(to, from, lengthFrom);
}

template<class Symbol, class Length, class sizet> vector<Symbol> WeightedGraph<Symbol, Length, sizet>::getKeySet() {
    vector<Symbol> keySet = vector<Symbol>();
    for (auto& key : edgeList) {
        keySet.push_back(key.first);
    }
    return keySet;
}

template<class Symbol, class Length> vector<Symbol> WeightedGraph<Symbol, Length>::getKeySet() {
    vector<Symbol> keySet = vector<Symbol>();
    for (auto& key : edgeList) {
        keySet.push_back(key.first);
    }
    return keySet;
}

template<class Symbol, class Length, class sizet> unordered_set<Symbol, sizet> WeightedGraph<Symbol, Length, sizet>::getVertexList() {
    return vertexList;
}

template<class Symbol, class Length> unordered_set<Symbol> WeightedGraph<Symbol, Length>::getVertexList() {
    return vertexList;
}

template<class Symbol, class Length, class sizet> int WeightedGraph<Symbol, Length, sizet>::size() {
    return edgeList.size();
}

template<class Symbol, class Length> int WeightedGraph<Symbol, Length>::size() {
    return edgeList.size();
}

template<class Symbol, class Length, class sizet> void WeightedGraph<Symbol, Length, sizet>::put(Symbol index, vector<pair<Symbol, Length>> list) {
    vertexList.insert(index);
    edgeList[index] = list;
    if (list.size() > 0) {
        for (pair<Symbol, Length> element : list) {
            vertexList.insert(element.first);
        }
    }
}

template<class Symbol, class Length> void WeightedGraph<Symbol, Length>::put(Symbol index, vector<pair<Symbol, Length>> list) {
    vertexList.insert(index);
    edgeList[index] = list;
    if (list.size() > 0) {
        for (pair<Symbol, Length> element : list) {
            vertexList.insert(element.first);
        }
    }
}

template<class Symbol, class Length, class sizet> vector<pair<Symbol, Length>> WeightedGraph<Symbol, Length, sizet>::get(Symbol symbol) {
    return edgeList[symbol];
}

template<class Symbol, class Length> vector<pair<Symbol, Length>> WeightedGraph<Symbol, Length>::get(Symbol index) {
    return edgeList[index];
}

template<class Symbol, class Length, class sizet> pair<Symbol, Length> WeightedGraph<Symbol, Length, sizet>::get(Symbol element, int index) {
    return edgeList[element].at(index);
}

template<class Symbol, class Length> pair<Symbol, Length> WeightedGraph<Symbol, Length>::get(Symbol element, int index) {
    return edgeList[element].at(index);
}

template<class Symbol, class Length, class sizet> unordered_map<Symbol, pair<Length, Symbol>, sizet> WeightedGraph<Symbol, Length, sizet>::bellmanFord(Symbol edge) {
    unordered_map<Symbol, pair<Length, Symbol>, sizet> map = unordered_map<Symbol, pair<Length, Symbol>, sizet>();
    map[edge] = pair<Length, Symbol>(lengthInterface->min(), edge);
    for (Symbol element : vertexList) {
        if (element != edge) {
            map[element] = pair<Length, Symbol>(lengthInterface->max(), Symbol());
        }
    }
    for (int t = 0; t < vertexList.size() - 1; t++) {
        for (auto& key : map) {
            if (this->containsKey(key.first)) {
                for (int i = 0; i < this->get(key.first).size(); i++) {
                    pair<Symbol, Length> element = this->get(key.first).at(i);
                    if (map[key.first].first != lengthInterface->max()) {
                        if (lengthInterface->compare(map[element.first].first, lengthInterface->add(element.second, map[key.first].first)) > 0) {
                            map[element.first] = pair<Length, Symbol>(lengthInterface->add(element.second, map[key.first].first), key.first);
                        }
                    }
                }
            }
        }
    }
    return map;
}

template<class Symbol, class Length> unordered_map<Symbol, pair<Length, Symbol>> WeightedGraph<Symbol, Length>::bellmanFord(Symbol edge) {
    unordered_map<Symbol, pair<Length, Symbol>> map = unordered_map<Symbol, pair<Length, Symbol>>();
    map[edge] = pair<Length, Symbol>(lengthInterface->min(), edge);
    for (Symbol element : vertexList) {
        if (element != edge) {
            map[element] = pair<Length, Symbol>(lengthInterface->max(), Symbol());
        }
    }
    for (int t = 0; t < vertexList.size() - 1; t++) {
        for (auto& key : map) {
            if (this->containsKey(key.first)) {
                for (int i = 0; i < this->get(key.first).size(); i++) {
                    pair<Symbol, Length> element = this->get(key.first).at(i);
                    if (map[key.first].first != lengthInterface->max()) {
                        if (lengthInterface->compare(map[element.first].first, lengthInterface->add(element.second, map[key.first].first)) > 0) {
                            map[element.first] = pair<Length, Symbol>(lengthInterface->add(element.second, map[key.first].first), key.first);
                        }
                    }
                }
            }
        }
    }
    return map;
}

template<class Symbol, class Length, class sizet> vector<vector<Length>> WeightedGraph<Symbol, Length, sizet>::floydWarshall() {
    vector<vector<Length>> array = vector<vector<Length>>();
    for (int i = 0; i < vertexList.size(); i++) {
        vector<Length> v = vector<Length>();
        array.push_back(v);
        for (int j = 0; j < vertexList.size(); j++) {
            array.at(array.size() - 1).push_back(lengthInterface->min());
        }
    }
    Length current;
    unordered_map<Symbol, int, sizet> map = unordered_map<Symbol, int, sizet>();
    int i = -1;
    for (Symbol key : vertexList) {
        i++;
        map[key] = i;
    }
    for (int j = 0; j < vertexList.size(); j++) {
        for (int k = 0; k < vertexList.size(); k++) {
            if (j != k) {
                array.at(j).at(k) = lengthInterface->max();
            }
        }
    }
    for (Symbol key : this->getKeySet()) {
        for (int k = 0; k < this->get(key).size(); k++) {
            array.at(map[key]).at(map[this->get(key).at(k).first]) = this->get(key).at(k).second;
        }
    }
    for (int j = 0; j < vertexList.size(); j++) {
        for (int k = 0; k < vertexList.size(); k++) {
            for (int l = 0; l < vertexList.size(); l++) {
                if (lengthInterface->compare(array.at(k).at(j), lengthInterface->max()) != 0 && lengthInterface->compare(array.at(j).at(l), lengthInterface->max()) != 0) {
                    current = lengthInterface->add(array.at(k).at(j), array.at(j).at(l));
                    if (lengthInterface->compare(array.at(k).at(l), current) > 0) {
                        array.at(k).at(l) = current;
                    }
                }
            }
        }
    }
    return array;
}

template<class Symbol, class Length> vector<vector<Length>> WeightedGraph<Symbol, Length>::floydWarshall() {
    vector<vector<Length>> array = vector<vector<Length>>();
    for (int i = 0; i < vertexList.size(); i++) {
        vector<Length> v = vector<Length>();
        array.push_back(v);
        for (int j = 0; j < vertexList.size(); j++) {
            array.at(array.size() - 1).push_back(lengthInterface->min());
        }
    }
    Length current;
    unordered_map<Symbol, int> map = unordered_map<Symbol, int>();
    int i = -1;
    for (Symbol key : vertexList) {
        i++;
        map[key] = i;
    }
    for (int j = 0; j < vertexList.size(); j++) {
        for (int k = 0; k < vertexList.size(); k++) {
            if (j != k) {
                array.at(j).at(k) = lengthInterface->max();
            }
        }
    }
    for (Symbol key : this->getKeySet()) {
        for (int k = 0; k < this->get(key).size(); k++) {
            array.at(map[key]).at(map[this->get(key).at(k).first]) = this->get(key).at(k).second;
        }
    }
    for (int j = 0; j < vertexList.size(); j++) {
        for (int k = 0; k < vertexList.size(); k++) {
            for (int l = 0; l < vertexList.size(); l++) {
                if (lengthInterface->compare(array.at(k).at(j), lengthInterface->max()) != 0 && lengthInterface->compare(array.at(j).at(l), lengthInterface->max()) != 0) {
                    current = lengthInterface->add(array.at(k).at(j), array.at(j).at(l));
                    if (lengthInterface->compare(array.at(k).at(l), current) > 0) {
                        array.at(k).at(l) = current;
                    }
                }
            }
        }
    }
    return array;
}

template<class Symbol, class Length> pair<unordered_map<int, Symbol>, vector<vector<Length>>> WeightedGraph<Symbol, Length>::floydWarshallWithKeys() {
    vector<vector<Length>> array = vector<vector<Length>>();
    for (int i = 0; i < vertexList.size(); i++) {
        vector<Length> v = vector<Length>();
        array.push_back(v);
        for (int j = 0; j < vertexList.size(); j++) {
            array.at(array.size() - 1).push_back(lengthInterface->min());
        }
    }
    Length current;
    unordered_map<Symbol, int> map = unordered_map<Symbol, int>();
    int i = -1;
    for (Symbol key : vertexList) {
        i++;
        map[key] = i;
    }
    for (int j = 0; j < vertexList.size(); j++) {
        for (int k = 0; k < vertexList.size(); k++) {
            if (j != k) {
                array.at(j).at(k) = lengthInterface->max();
            }
        }
    }
    for (Symbol key : this->getKeySet()) {
        for (int k = 0; k < this->get(key).size(); k++) {
            array.at(map[key]).at(map[this->get(key).at(k).first]) = this->get(key).at(k).second;
        }
    }
    for (int j = 0; j < vertexList.size(); j++) {
        for (int k = 0; k < vertexList.size(); k++) {
            for (int l = 0; l < vertexList.size(); l++) {
                if (lengthInterface->compare(array.at(k).at(j), lengthInterface->max()) != 0 && lengthInterface->compare(array.at(j).at(l), lengthInterface->max()) != 0) {
                    current = lengthInterface->add(array.at(k).at(j), array.at(j).at(l));
                    if (lengthInterface->compare(array.at(k).at(l), current) > 0) {
                        array.at(k).at(l) = current;
                    }
                }
            }
        }
    }
    return pair<unordered_map<int, Symbol>, vector<vector<Length>>>(invert(map), array);
}

template<class Symbol, class Length> unordered_map<int, Symbol> WeightedGraph<Symbol, Length>::invert(unordered_map<Symbol, int> map) {
    unordered_map<int, Symbol> inv = unordered_map<int, Symbol>();
    for (auto &key : map) {
        inv[map[key.first]] = key.first;
    }
    return inv;
}

template<class Symbol, class Length, class sizet> Length WeightedGraph<Symbol, Length, sizet>::prims() {
    Length total = lengthInterface->min();
    if (vertexList.size() > 2) {
        unordered_set<Symbol, sizet> elements = unordered_set<Symbol, sizet>();
        for (Symbol element : vertexList) {
            elements.insert(element);
            break;
        }
        while (!containsAll(elements)) {
            Symbol edge = Symbol();
            Length minimum = lengthInterface->max();
            for (Symbol element : elements) {
                for (int i = 0; i < get(element).size(); i++) {
                    pair<Symbol, Length> pair = get(element, i);
                    if (elements.find(pair.first) == elements.end() && lengthInterface->compare(pair.second, minimum) < 0) {
                        minimum = pair.second;
                        edge = pair.first;
                    }
                }
            }
            if (edge != Symbol()) {
                elements.insert(edge);
                total = lengthInterface->add(total, minimum);
            }
        }
    } else {
        for (Symbol key : getKeySet()) {
            total = get(key, 0).second;
            break;
        }
    }
    return total;
}

/**
 * can't handle default values!
 */
template<class Symbol, class Length> Length WeightedGraph<Symbol, Length>::prims() {
    Length total = lengthInterface->min();
    if (vertexList.size() > 2) {
        unordered_set<Symbol> elements = unordered_set<Symbol>();
        for (Symbol element : vertexList) {
            elements.insert(element);
            break;
        }
        while (!containsAll(elements)) {
            Symbol edge = Symbol();
            Length minimum = lengthInterface->max();
            for (Symbol element : elements) {
                for (int i = 0; i < get(element).size(); i++) {
                    pair<Symbol, Length> pair = get(element, i);
                    if (elements.find(pair.first) == elements.end() && lengthInterface->compare(pair.second, minimum) < 0) {
                        minimum = pair.second;
                        edge = pair.first;
                    }
                }
            }
            if (edge != Symbol()) {
                elements.insert(edge);
                total = lengthInterface->add(total, minimum);
            }
        }
    } else {
        for (Symbol key : getKeySet()) {
            total = get(key, 0).second;
            break;
        }
    }
    return total;
}

template<class Symbol, class Length, class sizet> bool WeightedGraph<Symbol, Length, sizet>::containsAll(unordered_set<Symbol, sizet> elements) {
    for (Symbol element : vertexList) {
        if (elements.find(element) == elements.end()) {
            return false;
        }
    }
    return true;
}

template<class Symbol, class Length> bool WeightedGraph<Symbol, Length>::containsAll(unordered_set<Symbol> elements) {
    for (Symbol element : vertexList) {
        if (elements.find(element) == elements.end()) {
            return false;
        }
    }
    return true;
}

template<class Symbol, class Length> Length WeightedGraph<Symbol, Length>::kruskal() {
    Length total = lengthInterface->min();
    vector<Triplet<Symbol, Symbol, Length>> list = vector<Triplet<Symbol, Symbol, Length>>();
    Symbol *nodes = new Symbol[vertexList.size()];
    int j = -1;
    for (Symbol element : vertexList) {
        j++;
        nodes[j] = element;
    }
    DisjointSet<Symbol> set = DisjointSet<Symbol>(nodes, vertexList.size());
    for (auto &key : edgeList) {
        for (int i = 0; i < edgeList[key.first].size(); i++) {
            Triplet<Symbol, Symbol, Length> triplet = Triplet<Symbol, Symbol, Length>(edgeList[key.first].at(i).first, key.first, edgeList[key.first].at(i).second);
            if (find(list.begin(), list.end(), triplet) == list.end()) {
                list.push_back(Triplet<Symbol, Symbol, Length>(key.first, edgeList[key.first].at(i).first, edgeList[key.first].at(i).second));
            }
        }
    }
    list = sort(list);
    for (Triplet<Symbol, Symbol, Length> tripletElement : list) {
        if (set.findSetWithType(tripletElement.getA()) != set.findSetWithType(tripletElement.getB())) {
            set.unionWithType(tripletElement.getA(), tripletElement.getB());
            total = lengthInterface->add(total, tripletElement.getC());
        }
    }
    return total;
}

template<class Symbol, class Length> vector<Triplet<Symbol, Symbol, Length>> WeightedGraph<Symbol, Length>::sort(vector<Triplet<Symbol, Symbol, Length>> list) {
    for (int i = 0; i < list.size(); i++) {
        for (int j = 0; j < list.size(); j++) {
            if (lengthInterface->compare(list.at(i).getC(), list.at(j).getC()) < 0) {
                Triplet<Symbol, Symbol, Length> tmp = list.at(i);
                list.at(i) = list.at(j);
                list.at(j) = tmp;
            }
        }
    }
    return list;
}

template<class Symbol, class Length, class sizet> pair<bool, int> WeightedGraph<Symbol, Length, sizet>::containsElement(Symbol edge, Symbol element) {
    for (int i = 0; i < get(edge).size(); i++) {
        if (get(edge, i).first == element) {
            return pair<bool, int>(true, i);
        }
    }
    return pair<bool, int>(false, -1);
}

template<class Symbol, class Length> pair<bool, int> WeightedGraph<Symbol, Length>::containsElement(Symbol edge, Symbol element) {
    for (int i = 0; i < get(edge).size(); i++) {
        if (get(edge, i).first == element) {
            return pair<bool, int>(true, i);
        }
    }
    return pair<bool, int>(false, -1);
}

template<class Symbol, class Length, class sizet> Symbol WeightedGraph<Symbol, Length, sizet>::findMinimum(unordered_set<Symbol, sizet> visited, unordered_map<Symbol, pair<Length, Symbol>, sizet> map) {
    Symbol element = Symbol();
    Length length = lengthInterface->max();
    for (auto &key : map) {
        if (visited.find(key.first) == visited.end()) {
            if (lengthInterface->compare(length, key.second.first) > 0) {
                length = key.second.first;
                element = key.first;
            }
        }
    }
    return element;
}

template<class Symbol, class Length> Symbol WeightedGraph<Symbol, Length>::findMinimum(unordered_set<Symbol> visited, unordered_map<Symbol, pair<Length, Symbol>> map) {
    Symbol element = Symbol();
    Length length = lengthInterface->max();
    for (auto &key : map) {
        if (visited.find(key.first) == visited.end()) {
            if (lengthInterface->compare(length, key.second.first) > 0) {
                length = key.second.first;
                element = key.first;
            }
        }
    }
    return element;
}

template<class Symbol, class Length, class sizet> unordered_map<Symbol, pair<Length, Symbol>, sizet> WeightedGraph<Symbol, Length, sizet>::dijkstra(Symbol edge) {
    unordered_set<Symbol, sizet> visited = unordered_set<Symbol, sizet>();
    unordered_map<Symbol, pair<Length, Symbol>, sizet> map = unordered_map<Symbol, pair<Length, Symbol>, sizet>();
    visited.insert(edge);
    for (Symbol element : vertexList) {
        if (edge == element) {
            map[element] = pair<Length, Symbol>(lengthInterface->min(), edge);
        } else if (containsElement(edge, element).first) {
            map[element] = pair<Length, Symbol>(get(edge, containsElement(edge, element).second).second, edge);
        } else {
            map[element] = pair<Length, Symbol>(lengthInterface->max(), Symbol());
        }
    }
    for (int i = 0; i < vertexList.size() - 1; i++) {
        Symbol key = findMinimum(visited, map);
        visited.insert(key);
        if (containsKey(key)) {
            for (int j = 0; j < get(key).size(); j++) {
                if (lengthInterface->compare(lengthInterface->add(map[key].first, get(key, j).second), map[get(key, j).first].first) < 0) {
                    map[get(key, j).first] = pair<Length, Symbol>(lengthInterface->add(map[key].first, get(key, j).second), key);
                }
            }
        }
    }
    return map;
}

template<class Symbol, class Length> unordered_map<Symbol, pair<Length, Symbol>> WeightedGraph<Symbol, Length>::dijkstra(Symbol edge) {
    unordered_set<Symbol> visited = unordered_set<Symbol>();
    unordered_map<Symbol, pair<Length, Symbol>> map = unordered_map<Symbol, pair<Length, Symbol>>();
    visited.insert(edge);
    for (Symbol element : vertexList) {
        if (edge == element) {
            map[element] = pair<Length, Symbol>(lengthInterface->min(), edge);
        } else if (containsElement(edge, element).first) {
            map[element] = pair<Length, Symbol>(get(edge, containsElement(edge, element).second).second, edge);
        } else {
            map[element] = pair<Length, Symbol>(lengthInterface->max(), Symbol());
        }
    }
    for (int i = 0; i < vertexList.size() - 1; i++) {
        Symbol key = findMinimum(visited, map);
        visited.insert(key);
        if (containsKey(key)) {
            for (int j = 0; j < get(key).size(); j++) {
                if (lengthInterface->compare(lengthInterface->add(map[key].first, get(key, j).second), map[get(key, j).first].first) < 0) {
                    map[get(key, j).first] = pair<Length, Symbol>(lengthInterface->add(map[key].first, get(key, j).second), key);
                }
            }
        }
    }
    return map;
}

template<class Symbol, class Length, class sizet> vector<WeightedGraph<Symbol, Length, sizet>> WeightedGraph<Symbol, Length, sizet>::connectedComponents() {
    vector<WeightedGraph<Symbol, Length, sizet>> graphs = vector<WeightedGraph<Symbol, Length, sizet>>();
    int i;
    unordered_map<Symbol, bool, sizet> visited = unordered_map<Symbol, bool, sizet>();
    for (Symbol vertex: vertexList) {
        visited[vertex] = false;
    }
    for (Symbol vertex: vertexList) {
        if (!visited[vertex]) {
            visited[vertex] = true;
            WeightedGraph<Symbol, Length, sizet> connectedComponent = WeightedGraph<Symbol, Length, sizet>(lengthInterface);
            depthFirstSearch(connectedComponent, vertex, visited);
            if (!connectedComponent.isEmpty()) {
                graphs.push_back(connectedComponent);
            }
        }
    }
    return graphs;
}

template<class Symbol, class Length> vector<WeightedGraph<Symbol, Length>> WeightedGraph<Symbol, Length>::connectedComponents() {
    vector<WeightedGraph<Symbol, Length>> graphs = vector<WeightedGraph<Symbol, Length>>();
    int i;
    unordered_map<Symbol, bool> visited = unordered_map<Symbol, bool>();
    for (Symbol vertex: vertexList) {
        visited[vertex] = false;
    }
    for (Symbol vertex: vertexList) {
        if (!visited[vertex]) {
            visited[vertex] = true;
            WeightedGraph<Symbol, Length> connectedComponent = WeightedGraph<Symbol, Length>(lengthInterface);
            depthFirstSearch(connectedComponent, vertex, visited);
            if (!connectedComponent.isEmpty()) {
                graphs.push_back(connectedComponent);
            }
        }
    }
    return graphs;
}

template<class Symbol, class Length, class sizet> void WeightedGraph<Symbol, Length, sizet>::depthFirstSearch(WeightedGraph<Symbol, Length, sizet> &connectedComponent, Symbol i, unordered_map<Symbol, bool, sizet> &visited) {
    if (containsKey(i)) {
        connectedComponent.put(i, get(i));
        for (pair<Symbol, Length> toNode : get(i)) {
            if (!visited[toNode.first]) {
                visited[toNode.first] = true;
                depthFirstSearch(connectedComponent, toNode.first, visited);
            }
        }
    }
}

template<class Symbol, class Length> void WeightedGraph<Symbol, Length>::depthFirstSearch(WeightedGraph<Symbol, Length> &connectedComponent, Symbol i, unordered_map<Symbol, bool> &visited) {
    if (containsKey(i)) {
        connectedComponent.put(i, get(i));
        for (pair<Symbol, Length> toNode : get(i)) {
            if (!visited[toNode.first]) {
                visited[toNode.first] = true;
                depthFirstSearch(connectedComponent, toNode.first, visited);
            }
        }
    }
}

#endif //COOKIES_CPP_WEIGHTEDGRAPH_H