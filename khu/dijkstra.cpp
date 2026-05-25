#include "dijkstra.h"
#include <queue>
#include <algorithm>

Dijkstra::Dijkstra(const GraphData& data)
    : Graph(data),
      dist(nVertices, std::numeric_limits<Weight>::infinity()),
      prev(nVertices, -1)
{}

void Dijkstra::compute(VertexID source) {
    using Pair = std::pair<Weight, VertexID>;
    std::priority_queue<Pair, std::vector<Pair>, std::greater<>> pq;

    std::fill(dist.begin(), dist.end(), std::numeric_limits<Weight>::infinity());
    std::fill(prev.begin(), prev.end(), -1);

    dist[source] = 0;
    pq.push({0, source});

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;
        for (auto [v, w] : adj[u]) {
            Weight alt = dist[u] + w;
            if (alt < dist[v]) {
                dist[v] = alt;
                prev[v] = u;
                pq.push({alt, v});
            }
        }
    }
}

Weight Dijkstra::distanceTo(VertexID target) const {
    return dist[target];
}

std::vector<VertexID> Dijkstra::pathTo(VertexID target) const {
    std::vector<VertexID> path;
    for (VertexID at = target; at != -1; at = prev[at]) {
        path.push_back(at);
    }
    std::reverse(path.begin(), path.end());
    return path;
}