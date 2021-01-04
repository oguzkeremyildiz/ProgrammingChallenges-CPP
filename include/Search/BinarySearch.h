//
// Created by Oğuz Kerem Yıldız on 4.01.2021.
//

#ifndef COOKIES_CPP_BINARYSEARCH_H
#define COOKIES_CPP_BINARYSEARCH_H
#include "../Comparator.h"
#include <vector>

using namespace std;

template<class Symbol> class BinarySearch {
private:
    Comparator<Symbol> *comparator;
public:
    BinarySearch();
    BinarySearch(Comparator<Symbol> *comparator);
    int search(vector<Symbol> list, int left, int right, Symbol x);
    int search(Symbol *list, int left, int right, Symbol x);
};

template<class Symbol> BinarySearch<Symbol>::BinarySearch(Comparator<Symbol> *comparator) {
    this->comparator = comparator;
}

template<class Symbol> int BinarySearch<Symbol>::search(vector<Symbol> list, int left, int right, Symbol x) {
    if (right >= left) {
        int mid = left + (right - left) / 2;
        if (comparator->compare(list.at(mid), x) == 0) {
            return mid;
        }
        if (comparator->compare(list.at(mid), x) > 0) {
            return search(list, left, mid - 1, x);
        }
        return search(list, mid + 1, right, x);
    }
    return -1;
}

template<class Symbol> int BinarySearch<Symbol>::search(Symbol *array, int left, int right, Symbol x) {
    if (right >= left) {
        int mid = left + (right - left) / 2;
        if (comparator->compare(array[mid], x) == 0) {
            return mid;
        }
        if (comparator->compare(array[mid], x) > 0) {
            return search(array, left, mid - 1, x);
        }
        return search(array, mid + 1, right, x);
    }
    return -1;
}

template<class Symbol> BinarySearch<Symbol>::BinarySearch() = default;

#endif //COOKIES_CPP_BINARYSEARCH_H
