//
// Created by Oğuz Kerem Yıldız on 23.01.2021.
//

#include "Node.h"

Node::Node() = default;

Node::Node(int index, std::pair<int, int> p) {
    this->index = index;
    this->pair = p;
}

std::pair<int, int> Node::getPair() const {
    return pair;
}

int Node::getIndex() const {
    return index;
}
