#include "arc_graph.h"

arc_graph::edge::edge(size_t from, size_t to) 
    : from{from}
    , to{to}
{}

arc_graph::arc_graph(const graph& g)
    : num_vertices{g.vertices_count()}
{
    for (size_t idx = 0; idx < num_vertices; ++idx) {
        std::vector<size_t> next_vertices = g.get_next_vertices(idx);
        for (const size_t& vert : next_vertices) {
            add_edge(idx, vert);
        }
    }
}

arc_graph::arc_graph(size_t num_vertices)
    : num_vertices{num_vertices}
{}

void arc_graph::add_edge(size_t from, size_t to) {
    edges.emplace_back(from, to);
}

size_t arc_graph::vertices_count() const {
    return num_vertices;
}

std::vector<size_t> arc_graph::get_next_vertices(size_t vertex) const {
    std::vector<size_t> next_vert;
    for (const edge& e : edges) {
        if (e.from == vertex) {
            next_vert.emplace_back(e.to);
        }
    }
    return next_vert;
}
    
std::vector<size_t> arc_graph::get_prev_vertices(size_t vertex) const {
    std::vector<size_t> prev_vert;
    for (const edge& e : edges) {
        if (e.to == vertex) {
            prev_vert.emplace_back(e.from);
        }
    }
    return prev_vert;
}
