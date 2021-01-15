//
// Created by Oğuz Kerem Yıldız on 13.01.2021.
//

#include "Node.h"

Node::Node() = default;

Node::Node(unsigned long long int value, int weight) {
    this->value = value;
    this->weight = weight;
}

unsigned long long int Node::getValue() {
    return value;
}

int Node::getWeight() {
    return weight;
}

bool operator ==(Node node1, Node node2) {
    return node1.getValue() == node2.getValue() && node1.getWeight() == node2.getWeight();
}
