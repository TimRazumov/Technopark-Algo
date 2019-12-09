#ifndef LIST_GRAPH_H
#define LIST_GRAPH_H

#include "graph.h"

class list_graph : public graph {    
 public:
    list_graph(const graph& g); 
    explicit list_graph(size_t num_vertices);
    virtual ~list_graph() = default;
    void add_edge(size_t from, size_t to) override;
    size_t vertices_count() const override;
    std::vector<size_t> get_next_vertices(size_t vertex) const override;
    std::vector<size_t> get_prev_vertices(size_t vertex) const override;
 private:
    const size_t num_vertices;
    std::vector<std::vector<size_t>> list;
};

#endif  // LIST_GRAPH_H
