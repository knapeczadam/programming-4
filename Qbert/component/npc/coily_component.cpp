#include "coily_component.h"

// Project includes
#include "component/character/position_component.h"
#include "component/character/direction_component.h"
#include "core/scene_utility.h"
#include "minigin/component/rendering/sprite_component.h"
#include "minigin/core/game_object.h"
#include "minigin/core/scene.h"
#include "minigin/utility/random.h"
#include "minigin/utility/sprite.h"

// Standard includes
#include <limits>
#include <queue>
#include <iostream>

namespace qbert
{
    coily_component::path_finder::path_finder()
    {
        edges_ = {
            {0, 2}, {0, 3}, {1, 3}, {1, 4},
            {2, 5}, {2, 6}, {3, 6}, {3, 7}, {4, 7}, {4, 8},
            {5, 9}, {5, 10}, {6, 10}, {6, 11}, {7, 11}, {7, 12}, {8, 12}, {8, 13},
            {9, 14}, {9, 15}, {10, 15}, {10, 16}, {11, 16}, {11, 17}, {12, 17}, {12, 18}, {13, 18}, {13, 19},
            {14, 20}, {14, 21}, {15, 21}, {15, 22}, {16, 22}, {16, 23}, {17, 23}, {17, 24}, {18, 24}, {18, 25}, {19, 25}, {19, 26},
            {20, 27}, {20, 28}, {21, 28}, {21, 29}, {22, 29}, {22, 30}, {23, 30}, {23, 31}, {24, 31}, {24, 32}, {25, 32}, {25, 33}, {26, 33},{26, 34},
            {27, 35}, {27, 36}, {28, 36}, {28, 37}, {29, 37}, {29, 38}, {30, 38}, {30, 39}, {31, 39}, {31, 40}, {32, 40}, {32, 41}, {33, 41}, {33, 42}, {34, 42}, {34, 43}
        };

        graph_.resize(v_);

        for (auto edge: edges_)
        {
            graph_[edge[0]].push_back(edge[1]);
            graph_[edge[1]].push_back(edge[0]);
        }
    }

    // https://www.geeksforgeeks.org/shortest-path-unweighted-graph/
    // Modified bfs to store the parent of nodes along with the
    // distance from source node
    void coily_component::path_finder::bfs(int S, std::vector<int> &par, std::vector<int> &dist)
    {
        // queue to store the nodes in the order they are
        // visited
        std::queue<int> q;
        // Mark the distance of the source node as 0
        dist[S] = 0;
        // Push the source node to the queue
        q.push(S);

        // Iterate till the queue is not empty
        while (!q.empty())
        {
            // Pop the node at the front of the queue
            int node = q.front();
            q.pop();

            // Explore all the neighbours of the current node
            for (int neighbour: graph_[node])
            {
                // Check if the neighbouring node is not visited
                if (dist[neighbour] == std::numeric_limits<int>::max())
                {
                    // Mark the current node as the parent of
                    // the neighbouring node
                    par[neighbour] = node;
                    // Mark the distance of the neighbouring
                    // node as distance of the current node + 1
                    dist[neighbour] = dist[node] + 1;
                    // Insert the neighbouring node to the queue
                    q.push(neighbour);
                }
            }
        }
    }

    
    // Function to print the shortest distance between source
    // vertex and destination vertex
    auto coily_component::path_finder::get_next_position(int S, int D) -> glm::ivec2
    {
        
        // par[] array stores the parent of nodes
        std::vector<int> par(v_, -1);

        // dist[] array stores distance of nodes from S
        std::vector<int> dist(v_, std::numeric_limits<int>::max());

        // function call to find the distance of all nodes and
        // their parent nodes
        bfs(S, par, dist);

        if (dist[D] == std::numeric_limits<int>::max())
        {
            std::cout << "Source and Destination are not connected";
            return {};
        }

        // vector path stores the shortest path
        std::vector<int> path;
        int currentNode = D;
        path.push_back(D);
        while (par[currentNode] != -1)
        {
            path.push_back(par[currentNode]);
            currentNode = par[currentNode];
        }
        
        // printing path from source to destination
        for (int i = (int) path.size() - 1; i >= 0; i--)
            std::cout << path[i] << " ";
        std::cout << '\n';

        if (path.size() > 1)
        {
            auto second_node = path[path.size() - 2];
            return to_pyramid_index(second_node);
        }
        return {};
    }

    auto coily_component::path_finder::to_graph_index(int row, int col) -> int
    {
        for (int i = -1, idx = 0; i < 7; ++i)
        {
            for (int j = -1; j < i + 2; ++j, ++idx)
            {
                if (i == row and j == col)
                {
                    return idx;
                }
            }
        }
        return -1;
    }

    auto coily_component::path_finder::to_pyramid_index(int graph_idx) -> glm::ivec2
    {
        for (int i = -1, idx = 0; i < 7; ++i)
        {
            for (int j = -1; j < i + 2; ++j, ++idx)
            {
                if (graph_idx == idx)
                {
                    return {i, j};
                }
            }
        }
        return {-1, 1};
    }

    coily_component::coily_component(mngn::sprite *coily_sprite_ptr)
        : coily_sprite_ptr_{coily_sprite_ptr}
    {
    }

    void coily_component::on_enable()
    {
        sprite_comp_ptr_ = owner()->component<mngn::sprite_component>();
        egg_sprite_ptr_ = sprite_comp_ptr_->sprite();
    }

    void coily_component::on_disable()
    {
        transform_back();
    }

    void coily_component::transform()
    {
        owner()->remove_tag("coily_egg");
        owner()->remove_tag("ball");
        owner()->add_tag("coily");
        sprite_comp_ptr_->set_sprite(coily_sprite_ptr_);
        auto pos = owner()->local_position();
        auto new_pos = glm::vec2{pos} + glm::vec2{0.0f, -32.0f};
        owner()->set_local_position(new_pos);

        owner()->component<mngn::collider_component>()->set_collider(
            coily_sprite_ptr_->collider_width(),
            coily_sprite_ptr_->collider_height(),
            coily_sprite_ptr_->collider_offset_x(),
            coily_sprite_ptr_->collider_offset_y());
    }

    void coily_component::transform_back()
    {
        owner()->remove_tag("coily");
        owner()->add_tag("coily_egg");
        owner()->add_tag("ball");
        sprite_comp_ptr_->set_sprite(egg_sprite_ptr_);
        auto pos = owner()->local_position();
        auto new_pos = glm::vec2{pos} + glm::vec2{0.0f, 32.0f};
        owner()->set_local_position(new_pos);

        owner()->component<mngn::collider_component>()->set_collider(
            egg_sprite_ptr_->collider_width(),
            egg_sprite_ptr_->collider_height(),
            egg_sprite_ptr_->collider_offset_x(),
            egg_sprite_ptr_->collider_offset_y());
    }

    void coily_component::calculate_next_move()
    {
        auto scene_ptr = scene_utility::instance().current_scene();
        auto player_go_ptrs = scene_ptr->find_game_objects_with_tag("player");
        mngn::game_object *player_go_ptr = nullptr;
        float min_distance = std::numeric_limits<float>::max();
        for (auto go_ptr : player_go_ptrs)
        {
            auto distance = glm::distance(go_ptr->local_position(), owner()->local_position());
            if (distance < min_distance)
            {
                player_go_ptr = go_ptr;
                min_distance = distance;
            }
        }

        auto player_row_idx = player_go_ptr->component<position_component>()->row();
        auto player_col_idx = player_go_ptr->component<position_component>()->col();
        auto coily_row_idx = owner()->component<position_component>()->row();
        auto coily_col_idx = owner()->component<position_component>()->col();

        auto start_idx = path_finder_.to_graph_index(coily_row_idx, coily_col_idx);
        auto end_idx = path_finder_.to_graph_index(player_row_idx, player_col_idx);
        auto next_pos = path_finder_.get_next_position(start_idx, end_idx);
        auto next_dir = next_pos - glm::ivec2{coily_row_idx, coily_col_idx};


        owner()->component<direction_component>()->set_direction(next_dir.x, next_dir.y);
    }
}
