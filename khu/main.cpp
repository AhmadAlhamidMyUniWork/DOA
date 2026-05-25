#include <iostream>
#include <unordered_map>
#include "reader.h"
#include "graph.h"
#include "dijkstra.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <data-file>\n";
        return 1;
    }

    auto [vertices, edges] = loadGraph(argv[1]);
    Graph g({vertices, edges});

    // Kontrollera sammanhang
    if (g.isConnectedDFS(0)) {
        std::cout << "DFS: Grafen är sammanhängande\n";
    } else {
        g.isConnectedDFS(0); // populate visited
        auto missing = g.unreachableNodes();
        std::cout << "DFS: Ej sammankopplade noder:";
        for (auto id : missing) std::cout << " " << id;
        std::cout << "\n";
    }

    if (g.isConnectedBFS(0)) {
        std::cout << "BFS: Grafen är sammanhängande\n";
    } else {
        g.isConnectedBFS(0);
        auto missing = g.unreachableNodes();
        std::cout << "BFS: Ej sammankopplade noder:";
        for (auto id : missing) std::cout << " " << id;
        std::cout << "\n";
    }

    // Kortaste vägar med Dijkstra
    Dijkstra dj({vertices, edges});
    struct Query { std::string a, b; } queries[] = {
        {"Nackstavägen", "Förrådet"},
        {"L319", "D025"},
        {"Storgatan Rondell Universitetet", "Bite Line West"}
    };

    // Mappa namn till id
    std::unordered_map<std::string, VertexID> nameToId;
    for (auto& v : vertices) nameToId[v.label] = v.id;

    for (auto& q : queries) {
        VertexID u = nameToId[q.a];
        VertexID v = nameToId[q.b];
        dj.compute(u);
        auto path = dj.pathTo(v);
        std::cout << q.a << " -> " << q.b << ": "
                  << dj.distanceTo(v) << " meter\n";
        std::cout << "Rutt: ";
        for (size_t i = 0; i < path.size(); ++i) {
            std::cout << vertices[path[i]].label;
            if (i + 1 < path.size()) std::cout << " -> ";
        }
        std::cout << "\n";
    }

    return 0;
}
