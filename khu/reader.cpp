#include "reader.h"
#include <fstream>
#include <sstream>
#include <algorithm>

static TokenType peekLineType(std::istream& in) {
    int c = in.peek();
    if (c == EOF) return TokenType::EOF_TOKEN;
    if (c == '#') return TokenType::COMMENT;
    if (c == 'M') return TokenType::METADATA;
    return TokenType::EDGE;
}

// Helper to trim leading/trailing whitespace
static std::string trim(const std::string& s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    size_t end   = s.find_last_not_of(" \t\r\n");
    return (start == std::string::npos) ? std::string() : s.substr(start, end - start + 1);
}

GraphData loadGraph(const std::string& filename) {
    std::ifstream in(filename);
    VertexList vertices;
    EdgeList edges;

    while (true) {
        switch (peekLineType(in)) {
            case TokenType::METADATA: {
                char M;
                VertexID vid;
                in >> M >> vid;
                std::string lbl;
                std::getline(in, lbl);
                lbl = trim(lbl);
                vertices.push_back({vid, lbl});
                break;
            }
            case TokenType::EDGE: {
                EdgeInfo e;
                in >> e.from >> e.to >> e.cost;
                std::string desc;
                std::getline(in, desc);
                e.info = trim(desc);
                edges.push_back(e);
                break;
            }
            case TokenType::COMMENT: {
                std::string skip;
                std::getline(in, skip);
                break;
            }
            case TokenType::EOF_TOKEN:
            default:
                return {vertices, edges};
        }
    }
}