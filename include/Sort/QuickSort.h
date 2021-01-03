//
// Created by Oğuz Kerem Yıldız on 3.01.2021.
//

#ifndef COOKIES_CPP_QUICKSORT_H
#define COOKIES_CPP_QUICKSORT_H
#include "Comparator.h"
#include <utility>
#include <vector>

using namespace std;

template<class Symbol> class QuickSort {
private:
    Comparator<Symbol> *comparator;
    vector<Symbol> swap(vector<Symbol> list, int i, int j);
    Symbol* swap(Symbol *array, int i, int j);
    pair<int, vector<Symbol>> partition(vector<Symbol> list, int first, int second);
    pair<int, Symbol*> partition(Symbol *array, int first, int second);
public:
    QuickSort();
    QuickSort(Comparator<Symbol> *comparator);
    vector<Symbol> sort(vector<Symbol> list, int first, int last);
    Symbol* sort(Symbol *array, int first, int last);
};

template<class Symbol> QuickSort<Symbol>::QuickSort() = default;

template<class Symbol> QuickSort<Symbol>::QuickSort(Comparator<Symbol> *comparator) {
    this->comparator = comparator;
}

template<class Symbol> vector<Symbol> QuickSort<Symbol>::swap(vector<Symbol> list, int i, int j) {
    Symbol tmp;
    tmp = list.at(i);
    list.at(i) = list.at(j);
    list.at(j) = tmp;
    return list;
}

template<class Symbol> pair<int, vector<Symbol>> QuickSort<Symbol>::partition(vector<Symbol> list, int first, int second) {
    Symbol x = list.at(second);
    int i = first - 1, j;
    for (j = first; j < second; j++) {
        if (comparator->compare(list.at(j), x) < 0) {
            i++;
            list = swap(list, i, j);
        }
    }
    list = swap(list, i + 1, second);
    return pair<int, vector<Symbol>>(i + 1, list);
}

template<class Symbol> vector<Symbol> QuickSort<Symbol>::sort(vector<Symbol> list, int first, int last) {
    int pivot;
    if (first < last) {
        pair<int, vector<Symbol>> p = partition(list, first, last);
        pivot = p.first;
        list = p.second;
        list = sort(list, first, pivot - 1);
        list = sort(list, pivot + 1, last);
    }
    return list;
}

template<class Symbol> Symbol *QuickSort<Symbol>::swap(Symbol *array, int i, int j) {
    Symbol tmp;
    tmp = array[i];
    array[i] = array[j];
    array[j] = tmp;
    return array;
}

template<class Symbol> pair<int, Symbol*> QuickSort<Symbol>::partition(Symbol *array, int first, int second) {
    Symbol x = array[second];
    int i = first - 1, j;
    for (j = first; j < second; j++) {
        if (comparator->compare(array[j], x) < 0) {
            i++;
            array = swap(array, i, j);
        }
    }
    array = swap(array, i + 1, second);
    return pair<int, Symbol*>(i + 1, array);
}

template<class Symbol> Symbol *QuickSort<Symbol>::sort(Symbol *array, int first, int last) {
    int pivot;
    if (first < last) {
        pair<int, Symbol*> p = partition(array, first, last);
        pivot = p.first;
        array = p.second;
        array = sort(array, first, pivot - 1);
        array = sort(array, pivot + 1, last);
    }
    return array;
}

#endif //COOKIES_CPP_QUICKSORT_H