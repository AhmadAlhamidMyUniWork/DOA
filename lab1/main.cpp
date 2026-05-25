#include <iostream>
#include "reader.h"
#include "bfs_dfs.h"

const int NODE_NACKSTAVAGEN = 24;
const int NODE_FORRADET     = 37;
const int NODE_L319         = 46;
const int NODE_D025         = 47;
const int NODE_RondellCampus = 30;
const int NODE_BITE_LINE    = 19;
const int NODE_UNIVERSITETET = 20;



int main() {
    auto [meta, edges] = parse_file("graph.txt");

    adjacency_matrix_t matrix;
    build_matrix(edges, matrix);

    // Kolla om grafen är strongly connected (alla noder når alla)
    std::cout << "Sammanhängande (DFS): "
              << (is_connected(matrix, true) ? "Ja" : "Nej") << "\n";
    std::cout << "Sammanhängande (BFS): "
              << (is_connected(matrix, false) ? "Ja" : "Nej") << "\n";

    double distances[GRAPH_SIZE];
    node_t previous[GRAPH_SIZE];

    // Fråga 1: Nackstavägen -> Förrådet
    dijkstra(matrix, NODE_NACKSTAVAGEN, distances, previous);
    std::cout << "\nFråga 1: Nackstavägen -> Förrådet\n";
    if(distances[NODE_FORRADET] == NO_EDGE){
        std::cout << "Ingen väg hittades\n";
    } else {
        std::cout << "Avstånd: " << distances[NODE_FORRADET] << "m\n";
        std::cout << "Väg: ";
        print_path(meta, previous, NODE_FORRADET);
    }

    // Fråga 2: L319 -> D025
    dijkstra(matrix, NODE_L319, distances, previous);
    std::cout << "\nFråga 2: L319 -> D025\n";
    if(distances[NODE_D025] == NO_EDGE){
        std::cout << "Ingen väg hittades\n";
    } else {
        std::cout << "Avstånd: " << distances[NODE_D025] << "m\n";
        std::cout << "Väg: ";
        print_path(meta, previous, NODE_D025);
    }

    // Fråga 3: Universitetet -> Bite Line West
    dijkstra(matrix, NODE_UNIVERSITETET, distances, previous);
    std::cout << "\nFråga 3: Universitetet -> Bite Line West\n";
    if(distances[NODE_BITE_LINE] == NO_EDGE){
        std::cout << "Ingen väg hittades\n";
    } else {
        std::cout << "Avstånd: " << distances[NODE_BITE_LINE] << "m\n";
        std::cout << "Väg: ";
        print_path(meta, previous, NODE_BITE_LINE);
    }

    return 0;
}