#pragma once

// Project includes
#include "minigin/component/family/custom_component.h"

// Standard includes
#include <vector>

// GLM includes
#include <glm/glm.hpp>

// Forward declarations
namespace mngn
{
    class sprite;
    class sprite_component;
}

namespace qbert
{
    class coily_component final : public mngn::custom_component
    {
        struct path_finder
        {
            path_finder();
            void bfs(int S, std::vector<int> &par, std::vector<int> &dist);
            auto get_next_position(int S, int D) -> glm::ivec2;
            auto to_graph_index(int row, int col) -> int;

        private:
            auto to_pyramid_index(int graph_idx) -> glm::ivec2;
            
        private:
            size_t v_ = 44; // number of vertices
            size_t e_ = 54; // number of edges
            std::vector<std::vector<int> > edges_;
            std::vector<std::vector<int> > graph_;
        } path_finder_;
        
    public:
        coily_component()          = default;
        explicit coily_component(mngn::sprite *coily_sprite_ptr);
        ~coily_component() override = default;

        coily_component(coily_component const &other)            = delete;
        coily_component(coily_component &&other)                 = delete;
        coily_component &operator=(coily_component const &other) = delete;
        coily_component &operator=(coily_component &&other)      = delete;

        void on_enable() override;
        void on_disable() override;

        void transform();
        void transform_back();
        void calculate_next_move();

    private:
        mngn::sprite_component *sprite_comp_ptr_  = nullptr;
        mngn::sprite           *egg_sprite_ptr_   = nullptr;
        mngn::sprite           *coily_sprite_ptr_ = nullptr;
    };
}
