#include "list_graph.h"

list_graph::list_graph(const graph& g)
    : num_vertices{g.vertices_count()}
    , list(num_vertices)
{
    for (size_t idx = 0; idx < num_vertices; ++idx) {
        std::vector<size_t> next_vertices = g.get_next_vertices(idx);
        for (const size_t& vert : next_vertices) {
            add_edge(idx, vert);
        }
    }
}

list_graph::list_graph(size_t num_vertices)
    : num_vertices{num_vertices}
    , list(num_vertices)
{}

void list_graph::add_edge(size_t from, size_t to) {
    list[from].emplace_back(to);
}

size_t list_graph::vertices_count() const {
    return num_vertices;
}

std::vector<size_t> list_graph::get_next_vertices(size_t vertex) const {
    return list[vertex];
}
    
std::vector<size_t> list_graph::get_prev_vertices(size_t vertex) const {
    std::vector<size_t> prev_vert;
    for (size_t idx = 0; idx < list.size(); ++idx) {
        const std::vector<size_t>& next_vert = list[idx];
        for (const size_t& vert : next_vert) {
            if (vert == vertex) {
                prev_vert.push_back(idx);
            }
        }
    }
    return prev_vert;
}
