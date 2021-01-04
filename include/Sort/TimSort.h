//
// Created by Oğuz Kerem Yıldız on 4.01.2021.
//

#ifndef COOKIES_CPP_TIMSORT_H
#define COOKIES_CPP_TIMSORT_H
#include "../Comparator.h"
#include <vector>

using namespace std;

template<class Symbol> class TimSort {
private:
    Comparator<Symbol> *comparator;
    void insertionSort(vector<Symbol> &list, int left, int right);
    void merge(vector<Symbol> &list, int l, int m, int r);
    void insertionSort(Symbol *list, int left, int right);
    void merge(Symbol *list, int l, int m, int r);
public:
    TimSort();
    TimSort(Comparator<Symbol> *comparator);
    void sort(vector<Symbol> &list, int length);
    void sort(Symbol *array, int length);
};

template<class Symbol> TimSort<Symbol>::TimSort(Comparator<Symbol> *comparator) {
    this->comparator = comparator;
}

template<class Symbol> void TimSort<Symbol>::insertionSort(vector<Symbol> &list, int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        Symbol temp = list.at(i);
        int j = i - 1;
        while (j >= left && comparator->compare(list.at(j), temp) > 0) {
            list.at(j + 1) = list.at(j);
            j--;
        }
        list.at(j + 1) = temp;
    }
}

template<class Symbol> void TimSort<Symbol>::merge(vector<Symbol> &list, int l, int m, int r) {
    int len1 = m - l + 1, len2 = r - m;
    vector<Symbol> left = vector<Symbol>();
    vector<Symbol> right = vector<Symbol>();
    for (int x = 0; x < len1; x++) {
        left.at(x) = list.at(l + x);
    }
    for (int x = 0; x < len2; x++) {
        right.at(x) = list.at(m + 1 + x);
    }
    int i = 0;
    int j = 0;
    int k = l;
    while (i < len1 && j < len2) {
        if (comparator->compare(left.at(i), right.at(j)) == 0 || comparator->compare(right.at(j), left.at(i)) > 0) {
            list.at(k) = left.at(i);
            i++;
        } else {
            list.at(k) = right.at(j);
            j++;
        }
        k++;
    }
    while (i < len1) {
        list.at(k) = left.at(i);
        k++;
        i++;
    }
    while (j < len2) {
        list.at(k) = right.at(j);
        k++;
        j++;
    }
}

template<class Symbol> void TimSort<Symbol>::sort(vector<Symbol> &list, int length) {
    for (int i = 0; i < length; i += 32) {
        insertionSort(list, i, min((i + 31), (length - 1)));
    }
    for (int size = 32; size < length; size = 2 * size) {
        for (int left = 0; left < length; left += 2 * size) {
            int mid = left + size - 1;
            int right = min((left + 2 * size - 1), (length - 1));
            merge(list, left, mid, right);
        }
    }
}

template<class Symbol> void TimSort<Symbol>::sort(Symbol *array, int length) {
    for (int i = 0; i < length; i += 32) {
        insertionSort(array, i, min((i + 31), (length - 1)));
    }
    for (int size = 32; size < length; size = 2 * size) {
        for (int left = 0; left < length; left += 2 * size) {
            int mid = left + size - 1;
            int right = min((left + 2 * size - 1), (length - 1));
            merge(array, left, mid, right);
        }
    }
}

template<class Symbol> void TimSort<Symbol>::insertionSort(Symbol *list, int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        Symbol temp = list[i];
        int j = i - 1;
        while (j >= left && comparator->compare(list[j], temp) > 0) {
            list[j + 1] = list[j];
            j--;
        }
        list[j + 1] = temp;
    }
}

template<class Symbol> void TimSort<Symbol>::merge(Symbol *list, int l, int m, int r) {
    int len1 = m - l + 1, len2 = r - m;
    vector<Symbol> left = vector<Symbol>();
    vector<Symbol> right = vector<Symbol>();
    for (int x = 0; x < len1; x++) {
        left.at(x) = list[l + x];
    }
    for (int x = 0; x < len2; x++) {
        right.at(x) = list[m + 1 + x];
    }
    int i = 0;
    int j = 0;
    int k = l;
    while (i < len1 && j < len2) {
        if (comparator->compare(left.at(i), right.at(j)) == 0 || comparator->compare(right.at(j), left.at(i)) > 0) {
            list[k] = left.at(i);
            i++;
        } else {
            list[k] = right.at(j);
            j++;
        }
        k++;
    }
    while (i < len1) {
        list[k] = left.at(i);
        k++;
        i++;
    }
    while (j < len2) {
        list[k] = right.at(j);
        k++;
        j++;
    }
}

template<class Symbol> TimSort<Symbol>::TimSort() = default;

#endif //COOKIES_CPP_TIMSORT_H
