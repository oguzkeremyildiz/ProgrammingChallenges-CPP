//
// Created by Oğuz Kerem Yıldız on 23.01.2021.
//

#ifndef PROGRAMMINGCHALLENGES_CPP_NODE_H
#define PROGRAMMINGCHALLENGES_CPP_NODE_H
#include <utility>

using namespace std;

class Node {
private:
    int index;
    pair<int, int> pair;
public:
    Node();
    Node(int index, std::pair<int, int> p);
    int getIndex() const;
    std::pair<int, int> getPair() const;
    bool operator ==(Node n) const {
        return this->index == n.index && this->pair.first == n.pair.first && this->pair.second == n.getPair().second;
    }
    bool operator !=(Node n) const {
        return !this->operator==(n);
    }
};


#endif //PROGRAMMINGCHALLENGES_CPP_NODE_H
