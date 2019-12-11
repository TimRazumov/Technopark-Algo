#include <iostream>
#include <vector>
#include <set>
#include <bits/stdc++.h>

class list_graph {
 public:
    explicit list_graph(size_t num_vertices);
    virtual ~list_graph() = default;
    void add_edge(size_t from, size_t to, size_t weight);
    size_t vertices_count() const;
    std::vector<std::pair<size_t, size_t>> get_next_vertices(size_t vertex) const;
 private:
    const size_t num_vertices;
    std::vector<std::vector<std::pair<size_t, size_t>>> list;
};

list_graph::list_graph(size_t num_vertices)
    : num_vertices{num_vertices}
    , list(num_vertices)
{}

void list_graph::add_edge(size_t from, size_t to, size_t weight) {
    list[from].emplace_back(to, weight);
    list[to].emplace_back(from, weight);
}

size_t list_graph::vertices_count() const {
    return num_vertices;
}

std::vector<std::pair<size_t, size_t>> list_graph::get_next_vertices(size_t vertex) const {
    return list[vertex];
}

/******************************************************************************/

int get_opt_len(const list_graph& graph, size_t from, size_t to) {
    std::vector<int> dist(graph.vertices_count(), INT_MAX);
    dist[from] = 0;
    
    std::set<std::pair<int, size_t>> queue;
    queue.emplace(dist[from], from);

    while(!queue.empty()) {
        size_t curr = (queue.begin())->second;
        queue.erase(queue.begin());
        std::vector<std::pair<size_t, size_t>> next_vert = graph.get_next_vertices(curr);
        for (const auto& next_pair : next_vert) {
            size_t next = next_pair.first;
            size_t weight = next_pair.second;
            if (dist[next] > dist[curr] + weight) {
                if (dist[next] != INT_MAX) {
                    queue.erase(std::make_pair(dist[next], next));
                }
                dist[next] = dist[curr] + weight;
                queue.emplace(dist[next], next);
            }
        }
    }
    return dist[to];
}

int main() {
    size_t num_vert = 0;
    std::cin >> num_vert;
    list_graph graph(num_vert);

    size_t num_edge = 0;
    std::cin >> num_edge;
    
    size_t from = 0, to = 0;
    for (size_t idx = 0; idx < num_edge; ++idx) {
        size_t weight = 0;
        std::cin >> from >> to >> weight;
        graph.add_edge(from, to, weight);
    }
    std::cin >> from >> to;
    std::cout << get_opt_len(graph, from, to);
    return 0;
}
