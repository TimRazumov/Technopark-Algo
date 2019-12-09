#include <gtest/gtest.h>
#include <memory>

#include "matrix_graph.h"

TEST(graph, matrix_graph) {
    std::unique_ptr<graph> g = std::make_unique<matrix_graph>(5);
    g->add_edge(1, 0);
    g->add_edge(0, 2);
    
    g->add_edge(2, 3);
    g->add_edge(3, 4);
    g->add_edge(0, 2);
    g->add_edge(0, 2);
    
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
