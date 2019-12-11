#include "matrix_graph.h"

matrix_graph::matrix_graph(const graph& g)
    : num_vertices{g.vertices_count()}
    , matrix(num_vertices, std::vector<bool>(num_vertices, false))
{
    for (size_t idx = 0; idx < num_vertices; ++idx) {
        std::vector<size_t> next_vertices = g.get_next_vertices(idx);
        for (const size_t& vert : next_vertices) {
            add_edge(idx, vert);
        }
    }
}

matrix_graph::matrix_graph(size_t num_vertices)
    : num_vertices{num_vertices}
    , matrix(num_vertices, std::vector<bool>(num_vertices, false))
{}

void matrix_graph::add_edge(size_t from, size_t to) {
    matrix[from][to] = true;
}

size_t matrix_graph::vertices_count() const {
    return num_vertices;
}

std::vector<size_t> matrix_graph::get_next_vertices(size_t vertex) const {
    std::vector<size_t> next_vertices;
    const std::vector<bool>& line = matrix[vertex];
    for (size_t idx = 0; idx < num_vertices; ++idx) {
        if (line[idx]) {
            next_vertices.emplace_back(idx);
        }
    }
    return next_vertices;
}
    
std::vector<size_t> matrix_graph::get_prev_vertices(size_t vertex) const {
    std::vector<size_t> prev_vertices;
    for (size_t idx = 0; idx < num_vertices; ++idx) {
        if (matrix[idx][vertex]) {
            prev_vertices.emplace_back(idx);
        }
    }
    return prev_vertices;
}
