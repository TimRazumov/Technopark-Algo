#ifndef MATRIX_GRAPH_H
#define MATRIX_GRAPH_H

#include "graph.h"

class matrix_graph : public graph {
 public:
    virtual ~matrix_graph() {};
    /*virtual void add_edge(size_t from, size_t to) = 0; // Добавление ребра от from к to
    virtual size_t vertices_count() const = 0;
    virtual std::vector<size_t> get_next_vertices(size_t vertex) const = 0;
    virtual std::vector<size_t> get_prev_vertices(size_t vertex) const = 0;*/
};

#endif  // MATRIX_GRAPH_H
