#include <gtest/gtest.h>
#include <memory>

#include "list_graph.h"
#include "matrix_graph.h"
#include "arc_graph.h"

TEST(graph, list_graph) {
    std::unique_ptr<graph> g = std::make_unique<list_graph>(5);
    g->add_edge(1, 0);
    g->add_edge(0, 2);
    g->add_edge(2, 3);
    g->add_edge(3, 4);
    g->add_edge(4, 3);
    g->add_edge(4, 2);
    
    // vertices_count
    EXPECT_EQ(g->vertices_count(), 5);
    
    // get next and prev vertices
    {
        std::vector<size_t> next_vert = g->get_next_vertices(0);
        EXPECT_EQ(next_vert.size(), 1);
        EXPECT_EQ(next_vert[0], 2);
        
        std::vector<size_t> prev_vert = g->get_prev_vertices(0);
        EXPECT_EQ(prev_vert.size(), 1);
        EXPECT_EQ(prev_vert[0], 1);
    }
    
    {
        std::vector<size_t> next_vert = g->get_next_vertices(1);
        EXPECT_EQ(next_vert.size(), 1);
        EXPECT_EQ(next_vert[0], 0);
        
        std::vector<size_t> prev_vert = g->get_prev_vertices(1);
        EXPECT_EQ(prev_vert.size(), 0);
    }
    
    {
        std::vector<size_t> next_vert = g->get_next_vertices(2);
        EXPECT_EQ(next_vert.size(), 1);
        EXPECT_EQ(next_vert[0], 3);
        
        std::vector<size_t> prev_vert = g->get_prev_vertices(2);
        EXPECT_EQ(prev_vert.size(), 2);
        std::sort(prev_vert.begin(), prev_vert.end());
        EXPECT_EQ(prev_vert[0], 0);
        EXPECT_EQ(prev_vert[1], 4);
    }
    
    {
        std::vector<size_t> next_vert = g->get_next_vertices(3);
        EXPECT_EQ(next_vert.size(), 1);
        EXPECT_EQ(next_vert[0], 4);
        
        std::vector<size_t> prev_vert = g->get_prev_vertices(3);
        EXPECT_EQ(prev_vert.size(), 2);
        std::sort(prev_vert.begin(), prev_vert.end());
        EXPECT_EQ(prev_vert[0], 2);
        EXPECT_EQ(prev_vert[1], 4);
    }
    
    {
        std::vector<size_t> next_vert = g->get_next_vertices(4);
        EXPECT_EQ(next_vert.size(), 2);
        std::sort(next_vert.begin(), next_vert.end());
        EXPECT_EQ(next_vert[0], 2);
        EXPECT_EQ(next_vert[1], 3);
        
        std::vector<size_t> prev_vert = g->get_prev_vertices(4);
        EXPECT_EQ(prev_vert.size(), 1);
        EXPECT_EQ(prev_vert[0], 3);
    }
}

TEST(graph, matrix_graph) {
    std::unique_ptr<graph> g = std::make_unique<matrix_graph>(5);
    g->add_edge(1, 0);
    g->add_edge(0, 2);
    g->add_edge(2, 3);
    g->add_edge(3, 4);
    g->add_edge(4, 3);
    g->add_edge(4, 2);
    
    // vertices_count
    EXPECT_EQ(g->vertices_count(), 5);
    
    // get next and prev vertices
    {
        std::vector<size_t> next_vert = g->get_next_vertices(0);
        EXPECT_EQ(next_vert.size(), 1);
        EXPECT_EQ(next_vert[0], 2);
        
        std::vector<size_t> prev_vert = g->get_prev_vertices(0);
        EXPECT_EQ(prev_vert.size(), 1);
        EXPECT_EQ(prev_vert[0], 1);
    }
    
    {
        std::vector<size_t> next_vert = g->get_next_vertices(1);
        EXPECT_EQ(next_vert.size(), 1);
        EXPECT_EQ(next_vert[0], 0);
        
        std::vector<size_t> prev_vert = g->get_prev_vertices(1);
        EXPECT_EQ(prev_vert.size(), 0);
    }
    
    {
        std::vector<size_t> next_vert = g->get_next_vertices(2);
        EXPECT_EQ(next_vert.size(), 1);
        EXPECT_EQ(next_vert[0], 3);
        
        std::vector<size_t> prev_vert = g->get_prev_vertices(2);
        EXPECT_EQ(prev_vert.size(), 2);
        std::sort(prev_vert.begin(), prev_vert.end());
        EXPECT_EQ(prev_vert[0], 0);
        EXPECT_EQ(prev_vert[1], 4);
    }
    
    {
        std::vector<size_t> next_vert = g->get_next_vertices(3);
        EXPECT_EQ(next_vert.size(), 1);
        EXPECT_EQ(next_vert[0], 4);
        
        std::vector<size_t> prev_vert = g->get_prev_vertices(3);
        EXPECT_EQ(prev_vert.size(), 2);
        std::sort(prev_vert.begin(), prev_vert.end());
        EXPECT_EQ(prev_vert[0], 2);
        EXPECT_EQ(prev_vert[1], 4);
    }
    
    {
        std::vector<size_t> next_vert = g->get_next_vertices(4);
        EXPECT_EQ(next_vert.size(), 2);
        std::sort(next_vert.begin(), next_vert.end());
        EXPECT_EQ(next_vert[0], 2);
        EXPECT_EQ(next_vert[1], 3);
        
        std::vector<size_t> prev_vert = g->get_prev_vertices(4);
        EXPECT_EQ(prev_vert.size(), 1);
        EXPECT_EQ(prev_vert[0], 3);
    }
}

TEST(graph, arc_graph) {
    std::unique_ptr<graph> g = std::make_unique<arc_graph>(5);
    g->add_edge(1, 0);
    g->add_edge(0, 2);
    g->add_edge(2, 3);
    g->add_edge(3, 4);
    g->add_edge(4, 3);
    g->add_edge(4, 2);
    
    // vertices_count
    EXPECT_EQ(g->vertices_count(), 5);
    
    // get next and prev vertices
    {
        std::vector<size_t> next_vert = g->get_next_vertices(0);
        EXPECT_EQ(next_vert.size(), 1);
        EXPECT_EQ(next_vert[0], 2);
        
        std::vector<size_t> prev_vert = g->get_prev_vertices(0);
        EXPECT_EQ(prev_vert.size(), 1);
        EXPECT_EQ(prev_vert[0], 1);
    }
    
    {
        std::vector<size_t> next_vert = g->get_next_vertices(1);
        EXPECT_EQ(next_vert.size(), 1);
        EXPECT_EQ(next_vert[0], 0);
        
        std::vector<size_t> prev_vert = g->get_prev_vertices(1);
        EXPECT_EQ(prev_vert.size(), 0);
    }
    
    {
        std::vector<size_t> next_vert = g->get_next_vertices(2);
        EXPECT_EQ(next_vert.size(), 1);
        EXPECT_EQ(next_vert[0], 3);
        
        std::vector<size_t> prev_vert = g->get_prev_vertices(2);
        EXPECT_EQ(prev_vert.size(), 2);
        std::sort(prev_vert.begin(), prev_vert.end());
        EXPECT_EQ(prev_vert[0], 0);
        EXPECT_EQ(prev_vert[1], 4);
    }
    
    {
        std::vector<size_t> next_vert = g->get_next_vertices(3);
        EXPECT_EQ(next_vert.size(), 1);
        EXPECT_EQ(next_vert[0], 4);
        
        std::vector<size_t> prev_vert = g->get_prev_vertices(3);
        EXPECT_EQ(prev_vert.size(), 2);
        std::sort(prev_vert.begin(), prev_vert.end());
        EXPECT_EQ(prev_vert[0], 2);
        EXPECT_EQ(prev_vert[1], 4);
    }
    
    {
        std::vector<size_t> next_vert = g->get_next_vertices(4);
        EXPECT_EQ(next_vert.size(), 2);
        std::sort(next_vert.begin(), next_vert.end());
        EXPECT_EQ(next_vert[0], 2);
        EXPECT_EQ(next_vert[1], 3);
        
        std::vector<size_t> prev_vert = g->get_prev_vertices(4);
        EXPECT_EQ(prev_vert.size(), 1);
        EXPECT_EQ(prev_vert[0], 3);
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
