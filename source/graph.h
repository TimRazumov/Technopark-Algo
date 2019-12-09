#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

class graph {
 public:
    virtual ~graph() = default;
    virtual void add_edge(size_t from, size_t to) = 0; // Добавление ребра от from к to
    virtual size_t vertices_count() const = 0;
    virtual std::vector<size_t> get_next_vertices(size_t vertex) const = 0;
    virtual std::vector<size_t> get_prev_vertices(size_t vertex) const = 0;
};

#endif  // GRAPH_H
