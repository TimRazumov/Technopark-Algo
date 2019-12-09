#ifndef MATRIX_GRAPH_H
#define MATRIX_GRAPH_H

#include "graph.h"

class matrix_graph : public graph {
 public:
    matrix_graph(const graph& g); 
    explicit matrix_graph(size_t num_vertices);
    virtual ~matrix_graph() = default;
    void add_edge(size_t from, size_t to) override; // Добавление ребра от from к to
    size_t vertices_count() const override;
    std::vector<size_t> get_next_vertices(size_t vertex) const override;
    std::vector<size_t> get_prev_vertices(size_t vertex) const override;
 private:
    const size_t num_vertices;
    std::vector<std::vector<bool>> matrix;
};

#endif  // MATRIX_GRAPH_H
