//
// Created by Oğuz Kerem Yıldız on 5.02.2021.
//

#ifndef PROGRAMMINGCHALLENGES_CPP_PROBLEM_H
#define PROGRAMMINGCHALLENGES_CPP_PROBLEM_H
#include <vector>

using namespace std;

class Problem {
private:
    int no;
    int categories;
    vector<int> categoryList;
public:
    Problem();
    Problem(int no, int categories);
    Problem(const Problem &p2);
    void addCategory(int category);
    int getCategory(int index);
    int getCategories() const;
    bool contains(int category);
    int findTotal(int category);
    int getNo() const;
    bool operator ==(const Problem& p) const {
        return this->no == p.no && this->categories == p.categories && this->categoryList == p.categoryList;
    }
    bool operator !=(const Problem& p) const {
        return !this->operator==(p);
    }
};

Problem::Problem() = default;

Problem::Problem(int no, int categories) {
    this->no = no;
    this->categories = categories;
    categoryList = vector<int>();
}

void Problem::addCategory(int category) {
    categoryList.push_back(category);
}

int Problem::getCategory(int index) {
    return categoryList.at(index);
}

bool Problem::contains(int category) {
    return find(categoryList.begin(), categoryList.end(), category) != categoryList.end();
}

int Problem::findTotal(int category) {
    int total = 0;
    for (int i : categoryList) {
        if (i == category) {
            total++;
        }
    }
    return total;
}

int Problem::getNo() const {
    return no;
}

int Problem::getCategories() const {
    return categories;
}

Problem::Problem(const Problem &p2) {
    this->no = p2.no;
    this->categories = p2.categories;
    this->categoryList = p2.categoryList;
}

#endif //PROGRAMMINGCHALLENGES_CPP_PROBLEM_H
