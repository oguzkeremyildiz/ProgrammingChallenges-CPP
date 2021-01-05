//
// Created by Oğuz Kerem Yıldız on 5.01.2021.
//
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include "Graph/Graph.h"
#include <vector>
#include <sstream>

using namespace std;

void print(vector<string> &outputs, unordered_map<int, unordered_set<string>> listOfNames, int scenario) {
    for (const string& output : outputs) {
        if (listOfNames[100000].find(output) != listOfNames[100000].end()) {
            cout << output + " infinity" << endl;
        } else {
            for (auto &key : listOfNames) {
                if (listOfNames[key.first].find(output) != listOfNames[key.first].end()) {
                    cout << output + " " + to_string(key.first) << endl;
                }
            }
        }
    }
}

void addEdges(vector<string> &persons, Graph<string> &graphEdges) {
    vector<string> connectedList;
    for (int j = 0; j < persons.size(); j++) {
        string fromPerson = persons.at(j);
        for (int i = 0; i < persons.size(); i++) {
            string toPerson = persons.at(i);
            if (i != j) {
                if (graphEdges.containsKey(fromPerson)) {
                    connectedList = graphEdges.get(fromPerson);
                } else {
                    connectedList = vector<string>();
                }
                connectedList.push_back(toPerson);
                graphEdges.put(fromPerson, connectedList);
            }
        }
    }
}

void setListForOnes(unordered_map<int, unordered_set<string>> &listOfNames, vector<string> &persons, unordered_set<string> &allPersons, Graph<string> &graphEdges) {
    unordered_set<string> personsHash = unordered_set<string>(persons.begin(), persons.end());
    for (const string& key : personsHash) {
        allPersons.insert(key);
    }
    if (personsHash.find("Erdos") != personsHash.end()) {
        personsHash.erase("Erdos");
        vector<string> personsHashContain = vector<string>(personsHash.begin(), personsHash.end());
        for (int i = 0; i < personsHash.size(); i++){
            listOfNames[1].insert(personsHashContain.at(i));
        }
    } else {
        addEdges(persons, graphEdges);
    }
}

void setListsForInfinities(unordered_set<string> &allPersons, unordered_map<int, unordered_set<string>> &listOfNames) {
    vector<string> persons = vector<string>(allPersons.begin(), allPersons.end());
    for (const string& person : persons) {
        if (listOfNames[1].find(person)  == listOfNames[1].end() && person != "Erdos") {
            listOfNames[100000].insert(person);
        }
    }
}

bool listOfNamesForOne(Graph<string> &graphEdges, unordered_map<int, unordered_set<string>> &listOfNames) {
    vector<string> listOne = vector<string>(listOfNames[1].begin(), listOfNames[1].end());
    for (const string& onePerson : listOne) {
        if (graphEdges.containsKey(onePerson)) {
            for (const string& second : graphEdges.get(onePerson))
                if (find(graphEdges.get(onePerson).begin(), graphEdges.get(onePerson).end(), second) != graphEdges.get(onePerson).end()) {
                    return true;
                }
        }
    }
    return false;
}

bool contains(vector<string> vector, const string& str) {
    for (auto & i : vector) {
        if (i == str) {
            return true;
        }
    }
    return false;
}

bool setList(int index, Graph<string> &graphEdges,  unordered_map<int, unordered_set<string>> &listOfNames) {
    bool added = false;
    listOfNames[index + 1];
    vector<string> listOne = vector<string>(listOfNames[index].begin(), listOfNames[index].end());
    unordered_set<string> listInfinity = listOfNames[100000];
    vector<string> removed = vector<string>();
    for (const string& onePerson : listOne) {
        if (listOfNamesForOne(graphEdges, listOfNames)) {
            for (const string& person : listInfinity) {
                if (graphEdges.containsKey(onePerson)) {
                    if (contains(graphEdges.get(onePerson), person)) {
                        listOfNames[index + 1].insert(person);
                        removed.push_back(person);
                        added = true;
                    }
                }
            }
        }
    }
    listInfinity = listOfNames[100000];
    for (auto & i : removed) {
        listInfinity.erase(i);
    }
    listOfNames[100000] = listInfinity;
    return added;
}

int main() {
    fstream file;
    file.open("Erdös.txt", ios::in);
    if (file.fail()) {
        cout << "file not reading" << endl;
    } else {
        string readNext, readOutput;
        int scenario, t = 0, worksNumber, output;
        vector<string> outputs = vector<string>();
        vector<string> persons = vector<string>();
        file >> scenario;
        for (int i = 0; i < scenario; i++) {
            cout << "Scenario " + to_string(i + 1) << endl;
            file >> worksNumber;
            file >> output;
            t++;
            unordered_set<string> allPersons = unordered_set<string>();
            unordered_map<int, unordered_set<string>> listOfNames = unordered_map<int, unordered_set<string>>();
            listOfNames[1];
            listOfNames[100000];
            Graph<string> graphEdges = Graph<string>();
            getline(file, readNext);
            for (int j = 0; j < worksNumber; j++) {
                getline(file, readNext);
                stringstream check(readNext);
                string intermediate;
                while (getline(check, intermediate, ' ')) {
                    persons.push_back(intermediate);
                }
                setListForOnes(listOfNames, persons, allPersons, graphEdges);
                persons.clear();
            }
            setListsForInfinities(allPersons,listOfNames);
            int index = 1;
            while (setList(index, graphEdges,listOfNames)) {
                index++;
            }
            for (int k = 0; k < output; k++) {
                file >> readOutput;
                outputs.push_back(readOutput);
            }
            print(outputs, listOfNames, scenario);
        }
    }
}