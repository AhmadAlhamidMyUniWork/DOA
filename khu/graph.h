#ifndef GRAPH_H
#define GRAPH_H

#include "reader.h"
#include <vector>
#include <queue>
#include <stack>

class Graph {
public:
    Graph(const GraphData& data);

    // Checks if all nodes are reachable from a start node
    bool isConnectedDFS(VertexID start);
    bool isConnectedBFS(VertexID start);
    std::vector<VertexID> unreachableNodes() const;

protected:
    int nVertices;
    std::vector<std::vector<std::pair<VertexID, Weight>>> adj;
    std::vector<bool> visited;
};

#endif // GRAPH_H
