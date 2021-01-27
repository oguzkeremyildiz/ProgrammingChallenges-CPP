//
// Created by Oğuz Kerem Yıldız on 27.01.2021.
//

#include "Roads.h"

Roads::Roads() {
    roads = vector<Road>();
}

void Roads::add(Road road) {
    roads.push_back(road);
}

Road Roads::getFirst() {
    return roads.at(0);
}

Road Roads::getLast() {
    return roads.at(roads.size() - 1);
}

Road Roads::get(int index) {
    return roads.at(index);
}

int Roads::size() {
    return roads.size();
}

void Roads::clear() {
    roads.clear();
}
