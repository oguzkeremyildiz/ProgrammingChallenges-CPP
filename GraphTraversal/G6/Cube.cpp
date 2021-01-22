//
// Created by Oğuz Kerem Yıldız on 22.01.2021.
//

#include "Cube.h"

Cube::Cube() = default;

Cube::Cube(int front, int back, int left, int right, int top, int bottom, int weight) {
    this->front = front;
    this->back = back;
    this->left = left;
    this->right = right;
    this->top = top;
    this->bottom = bottom;
    this->weight = weight;
    list = vector<int>();
    list.push_back(front);
    list.push_back(back);
    list.push_back(left);
    list.push_back(right);
    list.push_back(top);
    list.push_back(bottom);
}

int Cube::getWeight() const {
    return weight;
}

int Cube::getBottom() const {
    return bottom;
}

bool Cube::containsElement(int element) {
    return find(list.begin(), list.end(), element) != list.end();
}

int Cube::get(int index) {
    return list.at(index);
}

pair<int, int> Cube::getReverse(int index) {
    switch (index) {
        case 0:
            return pair<int, int>(getBack(), 1);
        case 1:
            return pair<int, int>(getFront(), 0);
        case 2:
            return pair<int, int>(getRight(), 3);
        case 3:
            return pair<int, int>(getLeft(), 2);
        case 4:
            return pair<int, int>(getBottom(), 5);
        case 5:
            return pair<int, int>(getTop(), 4);
        default:
            break;
    }
    return {INT_MAX, INT_MAX};
}

void Cube::add(int index, int element) {
    switch (index) {
        case 0:
            list.at(0) = element;
            setFront(element);
            break;
        case 1:
            list.at(1) = element;
            setBack(element);
            break;
        case 2:
            list.at(2) = element;
            setLeft(element);
            break;
        case 3:
            list.at(3) = element;
            setRight(element);
            break;
        case 4:
            list.at(4) = element;
            setTop(element);
            break;
        case 5:
            list.at(5) = element;
            setBottom(element);
            break;
        default:
            break;
    }
}

int Cube::getFront() const {
    return front;
}

void Cube::setFront(int front) {
    this->front = front;
}

int Cube::getBack() const {
    return back;
}

void Cube::setBack(int back) {
    this->back = back;
}

int Cube::getLeft() const {
    return left;
}

void Cube::setLeft(int left) {
    this->left = left;
}

int Cube::getRight() const {
    return right;
}

void Cube::setRight(int right) {
    this->right = right;
}

int Cube::getTop() const {
    return top;
}

void Cube::setTop(int top) {
    this->top = top;
}

void Cube::setBottom(int bottom) {
    this->bottom = bottom;
}

void Cube::setWeight(int weight) {
    this->weight = weight;
}
