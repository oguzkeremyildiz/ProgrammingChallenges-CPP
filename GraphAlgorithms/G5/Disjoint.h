//
// Created by Oğuz Kerem Yıldız on 1.02.2021.
//

#ifndef PROGRAMMINGCHALLENGES_CPP_DISJOINT_H
#define PROGRAMMINGCHALLENGES_CPP_DISJOINT_H
#include "Set/DisjointSet.h"
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

template<class T> class Disjoint : public DisjointSet<T> {
private:
    unordered_map<int, unordered_set<int>> enemies;
    unordered_set<int> clone(int item);
public:
    Disjoint() : DisjointSet<T>() {
    }
    const unordered_map<int, unordered_set<int>> &getEnemies() const {
        return enemies;
    }
    explicit Disjoint(vector<T> elements) : DisjointSet<T>(elements) {
        enemies = unordered_map<int, unordered_set<int>>();
        for (int i = 0; i < elements.size(); i++) {
            enemies[i] = unordered_set<int>();
        }
    }
    void commonEnemyMakesFriend() {
        for (auto &item1 : enemies) {
            for (auto &item2 : enemies) {
                if (item1.first != item2.first) {
                    unordered_set<int> enemyList = clone(item1.first);
                    for (int enemy : enemyList) {
                        if (enemies[item2.first].find(enemy) != enemies[item2.first].end()) {
                            unionWithType(item1.first, item2.first);
                        }
                    }
                }
            }
        }
    }
    bool isEnemy(int element1, int element2) {
        int set1 = DisjointSet<T>::findSetWithIndex(element1);
        int set2 = DisjointSet<T>::findSetWithIndex(element2);
        return enemies[set1].find(set2) != enemies[set1].end();
    }
    void setEnemies(int element1, int element2) {
        int set1 = DisjointSet<T>::findSetWithIndex(element1);
        int set2 = DisjointSet<T>::findSetWithIndex(element2);
        enemies[set1].insert(set2);
        enemies[set2].insert(set1);
        commonEnemyMakesFriend();
        updateEnemyList();
    }
    void updateEnemyList() {
        for (int i = 0; i < enemies.size(); i++) {
            unordered_set<int> removeList = unordered_set<int>();
            unordered_set<int> addedList = unordered_set<int>();
            for (int item1 : enemies[i]) {
                int representative = DisjointSet<T>::findSetWithIndex(item1);
                if (item1 != representative){
                    removeList.insert(item1);
                }
                addedList.insert(representative);
            }
            for (int element : removeList) {
                enemies[i].erase(enemies[i].find(element), enemies[i].end());
            }
            enemies[i].insert(addedList.begin(), addedList.end());
        }
    }
    void unionWithType(int element1, int element2) {
        int set1 = DisjointSet<T>::findSetWithIndex(element1);
        int set2 = DisjointSet<T>::findSetWithIndex(element2);
        DisjointSet<T>::unionWithIndex(element1, element2);
        int newSet = DisjointSet<T>::findSetWithIndex(element1);
        if (set1 == newSet) {
            enemies[newSet].insert(enemies[set2].begin(), enemies[set2].end());
            enemies[set2].clear();
        } else {
            enemies[newSet].insert(enemies[set1].begin(), enemies[set1].end());
            enemies[set1].clear();
        }
        commonEnemyMakesFriend();
        updateEnemyList();
    }
};

template<class T> unordered_set<int> Disjoint<T>::clone(int item) {
    unordered_set<int> set = unordered_set<int>();
    for (int element : enemies[item]) {
        set.insert(element);
    }
    return set;
}

#endif //PROGRAMMINGCHALLENGES_CPP_DISJOINT_H
