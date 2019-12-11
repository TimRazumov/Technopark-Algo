#include <iostream>
#include <vector>
#include <queue>
#include <bits/stdc++.h>

class list_graph {    
 public:
    explicit list_graph(size_t num_vertices);
    virtual ~list_graph() = default;
    void add_edge(size_t from, size_t to);
    size_t vertices_count() const;
    std::vector<size_t> get_next_vertices(size_t vertex) const;
 private:
    const size_t num_vertices;
    std::vector<std::vector<size_t>> list;
};

list_graph::list_graph(size_t num_vertices)
    : num_vertices{num_vertices}
    , list(num_vertices)
{}

void list_graph::add_edge(size_t from, size_t to) {
    list[from].emplace_back(to);
    list[to].emplace_back(from);
}

size_t list_graph::vertices_count() const {
    return num_vertices;
}

std::vector<size_t> list_graph::get_next_vertices(size_t vertex) const {
    return list[vertex];
}

/******************************************************************************/

size_t num_short_path(const list_graph& graph, size_t from, size_t to) {
    std::vector<int> dist(graph.vertices_count(), INT_MAX);
    dist[from] = 0;
    std::vector<size_t> path_count(graph.vertices_count(), 0);
    path_count[from] = 1;
    
    std::queue<size_t> q;
    q.push(from);
    
    while(!q.empty()) {
        size_t curr = q.front(); q.pop();
        std::vector<size_t> next_vert = graph.get_next_vertices(curr);
        for (size_t next : next_vert) {
            if (dist[next] == INT_MAX) {
                dist[next] = dist[curr] + 1;
                path_count[next] = path_count[curr];
                q.push(next);
            } else if (dist[next] == dist[curr] + 1) {
                path_count[next] += path_count[curr];
            }
        }
    }
    return path_count[to];
}

int main() {
    size_t num_vert = 0;
    std::cin >> num_vert;
    list_graph graph(num_vert);

    size_t num_edge = 0;
    std::cin >> num_edge;
    
    size_t from = 0, to = 0;
    for (size_t idx = 0; idx < num_edge; ++idx){
        std::cin >> from >> to;
        graph.add_edge(from, to);
    }
    std::cin >> from >> to;
    std::cout << num_short_path(graph, from, to);
    return 0;
}
