#include "Graph.h"
#include "Station.h"
#include <iostream>

using namespace std;

Node* Graph::getNode(string stationName) {
    return nodes.at(stationName);
}

bool Graph::addNode(Station& station) {
    if (nodes.find(station.getName()) != nodes.end()){
        cout << "Station " << station.getName() << " already exists." << endl;
        return false;
    }

    nodes[station.getName()] = new Node(station);
    return true;
}

bool Graph::addEdge(Station& source, Station& dest, int capacity, ServiceType service) {
    Node* sourceNode = nodes[source.getName()];
    Node* destNode = nodes[dest.getName()];

    if (sourceNode== nullptr){
        cout << "Station " << source.getName() << " does not exist." << endl;
        return false;
    }

    if (destNode== nullptr){
        cout << "Station " << dest.getName() << " does not exist." << endl;
        return false;
    }

    Edge* e1 = sourceNode->addEdge(destNode, capacity, service);
    Edge* e2 = destNode->addEdge(sourceNode, capacity, service);

    e1->setReverse(e2);
    e2->setReverse(e1);

    return true;
}

int Graph::getNumNodes() {
    return nodes.size();
}