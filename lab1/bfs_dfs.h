#ifndef GRAPH_H
#define GRAPH_H

#include "reader.h"
#include <limits>
#include <vector>
#include <stack>
#include <queue>

const int    GRAPH_SIZE = 48;
const double NO_EDGE = std::numeric_limits<double>::infinity();

using adjacency_matrix_t = double[GRAPH_SIZE][GRAPH_SIZE];
using node_t = int;

struct stack{
    std::stack<node_t> data;

    node_t pop(){
        node_t node = data.top();
        data.pop();
        return node;
    }
    void push(node_t node_id){
        data.push(node_id);
    }
    size_t size(){
        return data.size();
    }
};

struct queue{
    std::queue<node_t> data;

    node_t pop(){
        node_t node = data.front();
        data.pop();
        return node;
    }
    void push(node_t node_id){
        data.push(node_id);
    }
    size_t size(){
        return data.size();
    }
};

struct dijkstra_edge{
    node_t from;
    node_t to;
    double weight;
};

//Överlagring av operator< för dijkstra_edge så att vi kan använda den i egeb struct jämför med standardbibliotekets
// Eftersom det mallspecialicering så behöver vi inte skriva nåt i template 
template<>
struct std::less<dijkstra_edge>{ 
    bool operator() (const dijkstra_edge& e1, const dijkstra_edge& e2) {
        return e1.weight > e2.weight; // Om e1 har högre vikt än e2 så kommer den att ha lägre prioritet i priority_queue
    }
};


// Funktionsdeklarationer
void build_matrix(const edge_list_t& edges, adjacency_matrix_t& matrix);

void dfs(const adjacency_matrix_t& graph, node_t start_node, bool visited[]);

void bfs(const adjacency_matrix_t& graph, node_t start_node, bool visited[]);

bool is_connected(const adjacency_matrix_t& graph, bool use_dfs);

void dijkstra(const adjacency_matrix_t& graph, node_t start_node, 
              double distances[], node_t previous[]);

void print_path(const meta_t& meta, node_t previous[], node_t end_node);

#endif // GRAPH_H