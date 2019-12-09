#include <gtest/gtest.h>
#include <memory>

#include "list_graph.h"
#include "matrix_graph.h"
#include "set_graph.h"
#include "arc_graph.h"

bool test(const graph& g) {
    
    // vertices_count
    if (g.vertices_count() != 5) {
        return false;
    }
    
    // get next and prev vertices
    {
        std::vector<size_t> next_vert = g.get_next_vertices(0);
        if (next_vert.size() != 1 || next_vert[0] != 2) {
            return false;
        }
        
        std::vector<size_t> prev_vert = g.get_prev_vertices(0);
        if (prev_vert.size() != 1 || prev_vert[0] != 1) {
            return false;
        }
    }
    
    {
        std::vector<size_t> next_vert = g.get_next_vertices(1);
        if (next_vert.size() != 1 || next_vert[0] != 0) {
            return false;
        }
        
        std::vector<size_t> prev_vert = g.get_prev_vertices(1);
        if (prev_vert.size() != 0) {
            return false;
        }
    }
    
    {
        std::vector<size_t> next_vert = g.get_next_vertices(2);
        if (next_vert.size() != 1 || next_vert[0] != 3) {
            return false;
        }
        
        std::vector<size_t> prev_vert = g.get_prev_vertices(2);
        std::sort(prev_vert.begin(), prev_vert.end());
        if (prev_vert.size() != 2 || prev_vert[0] != 0 || prev_vert[1] != 4) {
            return false;
        }
    }
    
    {
        std::vector<size_t> next_vert = g.get_next_vertices(3);
        if (next_vert.size() != 1 || next_vert[0] != 4) {
            return false;
        }
        
        std::vector<size_t> prev_vert = g.get_prev_vertices(3);
        std::sort(prev_vert.begin(), prev_vert.end());
        if (prev_vert.size() != 2 || prev_vert[0] != 2 || prev_vert[1] != 4) {
            return false;
        }
    }
    
    {
        std::vector<size_t> next_vert = g.get_next_vertices(4);
        std::sort(next_vert.begin(), next_vert.end());
        if (next_vert.size() != 2 || next_vert[0] != 2 || next_vert[1] != 3) {
            return false;
        }
        
        std::vector<size_t> prev_vert = g.get_prev_vertices(4);
        if (prev_vert.size() != 1 || prev_vert[0] != 3) {
            return false;
        }
    }
    
    return true;
}

TEST(graph, all) {
    
    std::unique_ptr<graph> g = std::make_unique<list_graph>(5);
    g->add_edge(1, 0);
    g->add_edge(0, 2);
    g->add_edge(2, 3);
    g->add_edge(3, 4);
    g->add_edge(4, 3);
    g->add_edge(4, 2);
    
    EXPECT_EQ(test(*g), true);
    
    // test constructor
    {
        std::unique_ptr<graph> list = std::make_unique<list_graph>(*g);
        EXPECT_EQ(test(*list), true);
    }
    
    {
        std::unique_ptr<graph> matrix = std::make_unique<matrix_graph>(*g);
        EXPECT_EQ(test(*matrix), true);
    }
    
    {
        std::unique_ptr<graph> set = std::make_unique<set_graph>(*g);
        EXPECT_EQ(test(*set), true);
    }
    
    {
        std::unique_ptr<graph> arc = std::make_unique<arc_graph>(*g);
        EXPECT_EQ(test(*arc), true);
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
