#ifndef SET_GRAPH_H
#define SET_GRAPH_H

#include <set>
#include "graph.h"

class set_graph : public graph {
 public:
    set_graph(const graph& g); 
    explicit set_graph(size_t num_vertices);
    virtual ~set_graph() = default;
    void add_edge(size_t from, size_t to) override;
    size_t vertices_count() const override;
    std::vector<size_t> get_next_vertices(size_t vertex) const override;
    std::vector<size_t> get_prev_vertices(size_t vertex) const override;
 private:
    const size_t num_vertices;
    std::vector<std::set<size_t>> set;
};

#endif  // SET_GRAPH_H
