//
// Created by Oğuz Kerem Yıldız on 24.12.2020.
//

#ifndef COOKIES_CPP_DISJOINTSET_H
#define COOKIES_CPP_DISJOINTSET_H
#include "../Set/Set.h"
#include <unordered_map>
#include <vector>

using namespace std;

template<class T> class DisjointSet {
private:
    unordered_map<T, int> map;
public:
    Set<T> *sets;
    int count;
    DisjointSet();
    DisjointSet(vector<T> elements);
    DisjointSet(T *elements, int size);
    int size;
    int findSetWithIndex(int index);
    int findSetWithType(T type);
    void unionWithIndex(int index1, int index2);
    void unionWithType(T element1, T element2);
};

template<class T> DisjointSet<T>::DisjointSet() = default;

template<class T> DisjointSet<T>::DisjointSet(vector<T> elements) {
    size = elements.size();
    map = unordered_map<T, int>();
    sets = new Set<T>[elements.size()];
    count = elements.size();
    for (int i = 0; i < elements.size(); i++) {
        map[elements.at(i)] = i;
        sets[i] = Set<T>(elements.at(i), i);
    }
}

template<class T> DisjointSet<T>::DisjointSet(T *elements, int size) {
    this->size = size;
    map = unordered_map<T, int>();
    sets = new Set<T>[size];
    count = size;
    for (int i = 0; i < size; i++) {
        map[elements[i]] = i;
        sets[i] = Set<T>(elements[i], i);
    }
}

template<class T> int DisjointSet<T>::findSetWithIndex(int index) {
    if (sets[index].parent != index) {
        return findSetWithIndex(sets[index].parent);
    }
    return sets[index].parent;
}

template<class T> int DisjointSet<T>::findSetWithType(T type) {
    if (sets[map[type]].parent != map[type]) {
        return findSetWithIndex(sets[map[type]].parent);
    }
    return sets[map[type]].parent;
}

template<class T> void DisjointSet<T>::unionWithIndex(int index1, int index2) {
    int x;
    int y;
    x = findSetWithIndex(index1);
    y = findSetWithIndex(index2);
    if (sets[x].depth < sets[y].depth) {
        sets[x].parent = y;
    } else {
        sets[y].parent = x;
        if (sets[x].depth == sets[y].depth) {
            sets[x].depth++;
        }
    }
}

template<class T> void DisjointSet<T>::unionWithType(T element1, T element2) {
    int x;
    int y;
    x = findSetWithType(element1);
    y = findSetWithType(element2);
    if (sets[x].depth < sets[y].depth) {
        sets[x].parent = y;
    } else {
        sets[y].parent = x;
        if (sets[x].depth == sets[y].depth) {
            sets[x].depth++;
        }
    }
}

#endif //COOKIES_CPP_DISJOINTSET_H
