#ifndef READER_H
#define READER_H

#include <string>
#include <vector>
#include <utility>
#include <istream>

using VertexID = int;
using Weight = double;
using Description = std::string;

enum class TokenType { COMMENT, METADATA, EDGE, EOF_TOKEN };

struct VertexInfo {
    VertexID id;
    Description label;
};

struct EdgeInfo {
    VertexID from;
    VertexID to;
    Weight cost;
    Description info;
};

using VertexList = std::vector<VertexInfo>;
using EdgeList   = std::vector<EdgeInfo>;
using GraphData  = std::pair<VertexList, EdgeList>;

// Reads the input file and returns vertex metadata plus list of edges
GraphData loadGraph(const std::string& filename);

#endif // READER_H