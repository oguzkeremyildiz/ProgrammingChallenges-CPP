//
// Created by Oğuz Kerem Yıldız on 13.01.2021.
//

#ifndef PROGRAMMINGCHALLENGES_CPP_NODE_H
#define PROGRAMMINGCHALLENGES_CPP_NODE_H


class Node {
private:
    unsigned long long int value;
    int weight;
public:
    Node();
    Node(unsigned long long int value, int weight);
    unsigned long long int getValue();
    int getWeight();
};

bool operator ==(Node node1, Node node2);

#endif //PROGRAMMINGCHALLENGES_CPP_NODE_H
