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

template<class Symbol, class Length> class WeightedGraph {
private:
    unordered_map<Symbol, vector<pair<Symbol, Length>>> edgeList;
    unordered_set<Symbol> vertexList;
    LengthInterface<Length> *lengthInterface;
    unordered_map<int, Symbol> invert(unordered_map<Symbol, int> map);
    bool containsAll(unordered_set<Symbol> elements);
    vector<Triplet<Symbol, Symbol, Length>> sort(vector<Triplet<Symbol, Symbol, Length>> list);
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
    vector<pair<Symbol, Length>> get(Symbol index);
    pair<Symbol, Length> get(Symbol element, int index);
    unordered_map<Symbol, pair<Length, Symbol>> bellmanFord(Symbol edge);
    void printShortestPathBellmanFord(Symbol key);
    vector<vector<Length>> floydWarshall();
    pair<unordered_map<int, Symbol>, vector<vector<int>>> floydWarshallWithKeys();
    void printAllShortestPath();
    Length prims();
    Length kruskal();
};

template<class Symbol, class Length> WeightedGraph<Symbol, Length>::WeightedGraph() = default;

template<class Symbol, class Length> WeightedGraph<Symbol, Length>::WeightedGraph(LengthInterface<Length> *lengthInterface) {
    edgeList = unordered_map<Symbol, vector<pair<Symbol, Length>>>();
    vertexList = unordered_set<Symbol>();
    this->lengthInterface = lengthInterface;
}

template<class Symbol, class Length> WeightedGraph<Symbol, Length>::WeightedGraph(unordered_set<Symbol> vertexList, LengthInterface<Length> *lengthInterface) {
    edgeList = unordered_map<Symbol, vector<pair<Symbol, Length>>>();
    this->vertexList = vertexList;
    this->lengthInterface = lengthInterface;
}

template<class Symbol, class Length> void WeightedGraph<Symbol, Length>::clear() {
    edgeList.clear();
    vertexList.clear();
}

template<class Symbol, class Length> bool WeightedGraph<Symbol, Length>::isEmpty() {
    return edgeList.empty();
}

template<class Symbol, class Length> bool WeightedGraph<Symbol, Length>::containsKey(Symbol element) {
    return edgeList.find(element) != edgeList.end();
}

template<class Symbol, class Length> bool WeightedGraph<Symbol, Length>::contains(Symbol element) {
    return vertexList.find(element) != vertexList.end();
}

template<class Symbol, class Length> void WeightedGraph<Symbol, Length>::addDirectedEdge(Symbol from, Symbol to, Length length) {
    vertexList.insert(from);
    vertexList.insert(to);
    edgeList[from].push_back(pair<Symbol, Length>(to, length));
}

template<class Symbol, class Length> void WeightedGraph<Symbol, Length>::addUndirectedEdge(Symbol from, Symbol to, Length length) {
    addDirectedEdge(from, to, length);
    addDirectedEdge(to, from, length);
}

template<class Symbol, class Length> void WeightedGraph<Symbol, Length>::addUndirectedEdge(Symbol from, Symbol to, Length lengthFrom, Length lengthTo) {
    addDirectedEdge(from, to, lengthTo);
    addDirectedEdge(to, from, lengthFrom);
}

template<class Symbol, class Length> vector<Symbol> WeightedGraph<Symbol, Length>::getKeySet() {
    vector<Symbol> keySet = vector<Symbol>();
    for (auto& key : edgeList) {
        keySet.push_back(key.first);
    }
    return keySet;
}

template<class Symbol, class Length> unordered_set<Symbol> WeightedGraph<Symbol, Length>::getVertexList() {
    return vertexList;
}

template<class Symbol, class Length> int WeightedGraph<Symbol, Length>::size() {
    return edgeList.size();
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

template<class Symbol, class Length> vector<pair<Symbol, Length>> WeightedGraph<Symbol, Length>::get(Symbol index) {
    return edgeList[index];
}

template<class Symbol, class Length> pair<Symbol, Length> WeightedGraph<Symbol, Length>::get(Symbol element, int index) {
    return edgeList[element].at(index);
}

template<class Symbol, class Length> unordered_map<Symbol, pair<Length, Symbol>> WeightedGraph<Symbol, Length>::bellmanFord(Symbol edge) {
    unordered_map<Symbol, pair<Length, Symbol>> map = unordered_map<Symbol, pair<Length, Symbol>>();
    map[edge] = pair<Length, Symbol>(lengthInterface->min(), edge);
    for (Symbol element : vertexList) {
        if (element != edge) {
            map[element] = pair<Length, Symbol>(lengthInterface->max(), NULL);
        }
    }
    for (int t = 0; t < vertexList.size() - 1; t++) {
        for (auto& key : map) {
            if (this->containsKey(key.first)) {
                for (int i = 0; i < this->get(key.first).size(); i++) {
                    pair<Symbol, Length> element = this->get(key.first).at(i);
                    if (map[key.first].first != lengthInterface->max()) {
                        if (lengthInterface->compare(map[element.first].first, lengthInterface->add(element.second, map[key.first].first)) > 0) {
                            map[element.first] = pair<Symbol, Length>(lengthInterface->add(element.second, map[key.first].first), key.first);
                        }
                    }
                }
            }
        }
    }
    return map;
}

template<class Symbol, class Length> void WeightedGraph<Symbol, Length>::printShortestPathBellmanFord(Symbol key) {
    unordered_map<Symbol, pair<Length, Symbol>> map = this->bellmanFord(key);
    for (auto& element : map) {
        cout << std::to_string(5) + " -> " + std::to_string(element.first) + " = " + std::to_string(map[element.first].first) + " " +  std::to_string(map[element.first].second) << endl;
    }
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

template<class Symbol, class Length> pair<unordered_map<int, Symbol>, vector<vector<int>>> WeightedGraph<Symbol, Length>::floydWarshallWithKeys() {
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
    return pair<unordered_map<int, Symbol>, vector<vector<int>>>(invert(map), array);
}

template<class Symbol, class Length> unordered_map<int, Symbol> WeightedGraph<Symbol, Length>::invert(unordered_map<Symbol, int> map) {
    unordered_map<int, Symbol> inv = unordered_map<int, Symbol>();
    for (auto &key : map) {
        inv[map[key.first]] = key.first;
    }
    return inv;
}

template<class Symbol, class Length> void WeightedGraph<Symbol, Length>::printAllShortestPath() {
    pair<unordered_map<int, Symbol>, vector<vector<Length>>> pair;
    pair = this->floydWarshallWithKeys();
    for (int i = 0; i < pair.second.size(); i++) {
        for (int j = 0; j < pair.second.at(i).size(); j++) {
            cout << std::to_string(pair.first[i]) + " -> " + std::to_string(pair.first[j]) + " = " + std::to_string(pair.second.at(i).at(j)) << endl;
        }
    }
}

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

#endif //COOKIES_CPP_WEIGHTEDGRAPH_H