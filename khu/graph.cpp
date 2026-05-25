#include "graph.h"

Graph::Graph(const GraphData& data)
    : nVertices(static_cast<int>(data.first.size())),
      adj(nVertices), visited(nVertices, false)
{
    // Undirected graph: add both directions
    for (const auto& e : data.second) {
        if (e.from < nVertices && e.to < nVertices) {
            adj[e.from].push_back({e.to, e.cost});
            adj[e.to].push_back({e.from, e.cost});
        }
    }
}

bool Graph::isConnectedDFS(VertexID start) {
    std::fill(visited.begin(), visited.end(), false);
    std::stack<VertexID> stk;
    stk.push(start);
    visited[start] = true;
    int count = 1;

    while (!stk.empty()) {
        VertexID u = stk.top(); stk.pop();
        for (auto [v, w] : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                stk.push(v);
                ++count;
            }
        }
    }
    return count == nVertices;
}

bool Graph::isConnectedBFS(VertexID start) {
    std::fill(visited.begin(), visited.end(), false);
    std::queue<VertexID> q;
    q.push(start);
    visited[start] = true;
    int count = 1;

    while (!q.empty()) {
        VertexID u = q.front(); q.pop();
        for (auto [v, w] : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
                ++count;
            }
        }
    }
    return count == nVertices;
}

std::vector<VertexID> Graph::unreachableNodes() const {
    std::vector<VertexID> list;
    for (int i = 0; i < nVertices; ++i) {
        if (!visited[i]) list.push_back(i);
    }
    return list;
}
