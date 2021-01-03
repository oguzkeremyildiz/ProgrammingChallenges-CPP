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
    void swap(vector<Symbol> &list, int i, int j);
    void swap(Symbol *array, int i, int j);
    int partition(vector<Symbol> &list, int first, int second);
    int partition(Symbol *array, int first, int second);
public:
    QuickSort();
    QuickSort(Comparator<Symbol> *comparator);
    void sort(vector<Symbol> &list, int first, int last);
    void sort(Symbol *array, int first, int last);
};

template<class Symbol> QuickSort<Symbol>::QuickSort() = default;

template<class Symbol> QuickSort<Symbol>::QuickSort(Comparator<Symbol> *comparator) {
    this->comparator = comparator;
}

template<class Symbol> void QuickSort<Symbol>::swap(vector<Symbol> &list, int i, int j) {
    Symbol tmp;
    tmp = list.at(i);
    list.at(i) = list.at(j);
    list.at(j) = tmp;
}

template<class Symbol> int QuickSort<Symbol>::partition(vector<Symbol> &list, int first, int second) {
    Symbol x = list.at(second);
    int i = first - 1, j;
    for (j = first; j < second; j++) {
        if (comparator->compare(list.at(j), x) < 0) {
            i++;
            swap(list, i, j);
        }
    }
    swap(list, i + 1, second);
    return i + 1;
}

template<class Symbol> void QuickSort<Symbol>::sort(vector<Symbol> &list, int first, int last) {
    int pivot;
    if (first < last) {
        pivot = partition(list, first, last);
        sort(list, first, pivot - 1);
        sort(list, pivot + 1, last);
    }
}

template<class Symbol> void QuickSort<Symbol>::swap(Symbol *array, int i, int j) {
    Symbol tmp;
    tmp = array[i];
    array[i] = array[j];
    array[j] = tmp;
}

template<class Symbol> int QuickSort<Symbol>::partition(Symbol *array, int first, int second) {
    Symbol x = array[second];
    int i = first - 1, j;
    for (j = first; j < second; j++) {
        if (comparator->compare(array[j], x) < 0) {
            i++;
            swap(array, i, j);
        }
    }
    swap(array, i + 1, second);
    return i + 1;
}

template<class Symbol> void QuickSort<Symbol>::sort(Symbol *array, int first, int last) {
    int pivot;
    if (first < last) {
        pivot = partition(array, first, last);
        sort(array, first, pivot - 1);
        sort(array, pivot + 1, last);
    }
}

#endif //COOKIES_CPP_QUICKSORT_H