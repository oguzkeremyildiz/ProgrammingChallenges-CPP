//
// Created by Oğuz Kerem Yıldız on 25.12.2020.
//

#ifndef COOKIES_CPP_PERMUTATION_H
#define COOKIES_CPP_PERMUTATION_H

class Permutation {
private:
    int *a;
    int n;
public:
    int* get();
    Permutation();
    Permutation(int n);
    bool next();
};

Permutation::Permutation() = default;

Permutation::Permutation(int n) {
    int i;
    this->n = n;
    a = new int[n];
    for (i = 0; i < n; i++) {
        a[i] = i;
    }
}

int* Permutation::get() {
    return a;
}

bool Permutation::next() {
    int i = n - 2;
    int j, tmp, k;
    while (i >= 0 && a[i] >= a[i + 1]) {
        i--;
    }
    if (i == -1) {
        return false;
    }
    j = n - 1;
    while (a[i] >= a[j]) {
        j--;
    }
    tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
    k = i + 1;
    j = n - 1;
    while (k < j) {
        tmp = a[k];
        a[k] = a[j];
        a[j] = tmp;
        k++;
        j--;
    }
    return true;
}
#endif //COOKIES_CPP_PERMUTATION_H
