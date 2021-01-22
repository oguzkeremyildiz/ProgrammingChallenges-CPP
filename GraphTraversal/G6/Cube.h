//
// Created by Oğuz Kerem Yıldız on 22.01.2021.
//

#ifndef PROGRAMMINGCHALLENGES_CPP_CUBE_H
#define PROGRAMMINGCHALLENGES_CPP_CUBE_H
#include <vector>
#include <utility>

using namespace std;

class Cube {
private:
    int front;
    int back;
    int left;
    int right;
    int top;
    int bottom;
    int weight;
    vector<int> list;
public:
    Cube();
    Cube(int front, int back, int left, int right, int top, int bottom, int weight);
    int getWeight() const;
    void setWeight(int weight);
    int getBottom() const;
    void setBottom(int bottom);
    int getFront() const;
    void setFront(int front);
    int getBack() const;
    void setBack(int back);
    int getLeft() const;
    void setLeft(int left);
    int getRight() const;
    void setRight(int right);
    void setTop(int top);
    int getTop() const;
    bool containsElement(int element);
    int get(int index);
    pair<int, int> getReverse(int index);
    void add(int index, int element);
    bool operator ==(Cube c) const {
        return this->top == c.getTop() && this->front == c.front && this->left == c.left && this->right == c.right && this->bottom == c.bottom && this->weight == c.weight && this->list == c.list;
    }
};


#endif //PROGRAMMINGCHALLENGES_CPP_CUBE_H
