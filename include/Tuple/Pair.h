//
// Created by Oğuz Kerem Yıldız on 23.12.2020.
//

#ifndef COOKIES_CPP_PAIR_H
#define COOKIES_CPP_PAIR_H

template<class K, class V> class Pair {
private:
    K key;
    V value;
public:
    Pair();
    Pair(K key, V value);
    K getKey() const;
    V getValue() const;
};

template<class K, class V> Pair<K, V>::Pair() = default;

template<class K, class V> Pair<K, V>::Pair(K key, V value) {
    this->key = key;
    this->value = value;
}

template<class K, class V> K Pair<K, V>::getKey() const {
    return this->key;
}

template<class K, class V> V Pair<K, V>::getValue() const {
    return this->value;
}

template <class K, class V>
bool operator ==(Pair<K, V> pair1, Pair<K, V> pair2) {
    return pair1.getKey() == pair2.getKey() && pair1.getValue() == pair2.getValue();
}

template <class K, class V>
bool operator !=(Pair<K, V> pair1, Pair<K, V> pair2) {
    return pair1.getKey() != pair2.getKey() || pair1.getValue() != pair2.getValue();
}

#endif //COOKIES_CPP_PAIR_H
