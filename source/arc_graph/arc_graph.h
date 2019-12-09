#ifndef ARC_GRAPH_H
#define ARC_GRAPH_H

#include "graph.h"

class arc_graph : public graph {
    struct edge {
        size_t from;
        size_t to;
        edge(size_t from, size_t to);
    };
    
 public:
    arc_graph(const graph& g); 
    explicit arc_graph(size_t num_vertices);
    virtual ~arc_graph() = default;
    void add_edge(size_t from, size_t to) override;
    size_t vertices_count() const override;
    std::vector<size_t> get_next_vertices(size_t vertex) const override;
    std::vector<size_t> get_prev_vertices(size_t vertex) const override;
 private:
    const size_t num_vertices;
    std::vector<edge> edges;
};

#endif  // ARC_GRAPH_H
