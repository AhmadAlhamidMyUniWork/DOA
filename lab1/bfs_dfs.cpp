#include "bfs_dfs.h"
#include <queue>
#include <vector>
#include <algorithm>
#include <iostream>
#include <stack>
#include <limits>


bool is_all_visited(bool visited[]){
    for (int i = 0; i < GRAPH_SIZE; i++){
        if (!visited[i]){
            return false;
        }
    }
    return true;
}

void push_and_visit(stack& s, node_t node_id, bool visited[]){
    s.push(node_id); //Lägg till startnoden i stacken
    visited[node_id] = true;  // För att inte besöka samma nod igen
    std::cout << "Besöker nod " << (node_id + 1) << "\n";
}

void push_and_visit(queue& q, node_t node_id, bool visited[]){
    q.push(node_id);
    visited[node_id] = true;
    std::cout << "Besöker nod " << (node_id + 1) << "\n";
}


std::vector<node_t> unvisited_grannar(const adjacency_matrix_t& graph, node_t current, bool visited[]){
    std::vector<node_t> grannar;
    for(int granne_id = 0; granne_id < GRAPH_SIZE; granne_id++){ // Kolla alla noder i grafen som är grannar till current och inte är besökta
        if(graph[current][granne_id] != NO_EDGE && !visited[granne_id] && granne_id != current){
            grannar.push_back(granne_id);
        }
    }
    return grannar;
}

void build_matrix(const edge_list_t& edges, adjacency_matrix_t& matrix){
    // 1. Initiera hela matrisen med NO_EDGE (infinity)
    // 2. Sätt diagonalen till 0 (nod till sig själv)
    for(int row = 0; row < GRAPH_SIZE; row++){
        for(int col = 0; col < GRAPH_SIZE; col++){
        if(row == col){
            matrix[row][col] = 0;
        } else {
            matrix[row][col] = NO_EDGE;
        }
    }
}
    
    // 3. Fyll i kanterna från edge_list
    for(const auto& e : edges){
        matrix[e.n1][e.n2] = e.weight;  // riktad graf
    }
}

void dfs(const adjacency_matrix_t& graph, node_t start_node, bool visited[]){
    stack s; 
    push_and_visit(s, start_node, visited);
    while(s.size())                        // så länge stacken har storlek
    {
        node_t current = s.pop();
        auto grannar = unvisited_grannar(graph, current, visited); //Hitta grannar som inte är besökta (vilka grannar som finns)
        std::cout << "Grannar till nod " << (current + 1) << "\n";
        // Lägg till alla grannar i stacken och markera dem som besökta
        for(auto id: grannar){
            push_and_visit(s, id, visited);
        }
    }
}

void bfs(const adjacency_matrix_t& graph, node_t start_node, bool visited[]){
    queue s;
    push_and_visit(s, start_node, visited);
    while(s.size())
    {
        node_t current = s.pop();
        auto grannar = unvisited_grannar(graph, current, visited);
        std::cout << "Grannar till nod " << (current + 1) << "\n";
        for(auto id: grannar){
            push_and_visit(s, id, visited);
        }
    }
}

bool is_connected(const adjacency_matrix_t& graph, bool use_dfs){
    for(int start = 0; start < GRAPH_SIZE; start++){
        bool visited[GRAPH_SIZE] = {false};
        
        if(use_dfs){
            dfs(graph, start, visited);
        } else {
            bfs(graph, start, visited);
        }
        
        if(!is_all_visited(visited)){
            return false;
        }
    }
    return true;
}

void dijkstra(
    const adjacency_matrix_t& graph,
    node_t start_node,
    double distances[],
    node_t previous[]
)

{
    bool visited[GRAPH_SIZE] = {false};
    for(int i = 0; i < GRAPH_SIZE; i++){
        distances[i] = NO_EDGE;
        previous[i]  = -1;
}
    distances[start_node] = 0;

    std::priority_queue<dijkstra_edge> pq;
    pq.push({start_node, start_node, 0});
    while(pq.size())
    {
        auto current = pq.top(); 
        pq.pop();
        if(visited[current.to]){
            continue;
        }
    visited[current.to] = true;
    auto grannar = unvisited_grannar(graph, current.to, visited);
    for(auto granne_id: grannar){
        double new_distance = distances[current.to] + graph[current.to][granne_id];
        if(new_distance < distances[granne_id]){
            distances[granne_id] = new_distance;
            previous[granne_id]  = current.to;
            pq.push({current.to, granne_id, new_distance});
        }
    }
}}

void print_path(const meta_t& meta, node_t previous[], node_t end_node){
    std::vector<node_t> path;
    int current = end_node;
    
    // backa från slutnod till startnod
    while(current != -1){
        path.push_back(current);
        current = previous[current];
    }
    
    // vänd på vägen
    std::reverse(path.begin(), path.end());
    
    // skriv ut vägen
    for(auto node : path){
    std::cout << meta.at(node) << " -> " << "\n";;
}}

