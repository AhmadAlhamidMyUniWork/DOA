#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "graph.h"
#include "reader.h"
#include <limits>

class Dijkstra : public Graph {
public:
    Dijkstra(const GraphData& data);

    // Computes shortest paths from source
    void compute(VertexID source);

    // Returns distance to target
    Weight distanceTo(VertexID target) const;

    // Reconstructs path from source to target
    std::vector<VertexID> pathTo(VertexID target) const;

private:
    std::vector<Weight> dist;
    std::vector<VertexID> prev;
};

#endif // DIJKSTRA_H

