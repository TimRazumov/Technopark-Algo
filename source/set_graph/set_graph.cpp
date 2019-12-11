#include "set_graph.h"

set_graph::set_graph(const graph& g)
    : num_vertices{g.vertices_count()}
    , set(num_vertices)
{
    for (size_t idx = 0; idx < num_vertices; ++idx) {
        std::vector<size_t> next_vertices = g.get_next_vertices(idx);
        for (const size_t& vert : next_vertices) {
            add_edge(idx, vert);
        }
    }
}

set_graph::set_graph(size_t num_vertices)
    : num_vertices{num_vertices}
    , set(num_vertices)
{}

void set_graph::add_edge(size_t from, size_t to) {
    set[from].emplace(to);
}

size_t set_graph::vertices_count() const {
    return num_vertices;
}

std::vector<size_t> set_graph::get_next_vertices(size_t vertex) const {
    return {set[vertex].begin(), set[vertex].end()};
}
    
std::vector<size_t> set_graph::get_prev_vertices(size_t vertex) const {
    std::vector<size_t> prev_vertices;
    for (size_t idx = 0; idx < num_vertices; ++idx) {
        const std::set<size_t>& next_vert = set[idx];
        for (const size_t& vert : next_vert) {
            if (vert == vertex) {
                prev_vertices.push_back(idx);
            }
        }
    }
    return prev_vertices;
}
