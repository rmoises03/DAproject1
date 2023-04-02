#ifndef PROJECT_DA_GRAPH_H
#define PROJECT_DA_GRAPH_H

#include <string>
#include <set>
#include <map>
#include "Station.h"
#include "NodeEdge.h"
#include "ServiceType.h"
using namespace std;

class Graph {
    public:
        bool addNode(Station& station);
        bool addEdge(Station& source, Station& dest, int capacity, ServiceType service);

        Node* getNode(string stationName);
        int getNumNodes();
        map<string, Node*> & getNodeMap();

        //Algorithms
        /*Edmond's karp*/
        int maxFlow(Station& source, Station& dest);


    private:
        map<string, Node*> nodes;
};

#endif //PROJECT_DA_GRAPH_H
