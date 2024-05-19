#pragma once

// Project includes
#include "game_state.h"

// Standard includes
#include <vector>

// Forward declarations
namespace mngn
{
    class game_object;
    class sprite_component;
    class sprite_ui_component;
}

namespace qbert
{
    // Forward declarations
    class jump_component;
    class spawn_component;
    class fall_component;
    class flicker_component;
    
    class game_over_state final : public game_state
    {
    public:
        explicit game_over_state(game_state_component *game_state_comp_ptr);
        ~game_over_state() override = default;

        game_over_state(game_over_state const &other)            = delete;
        game_over_state(game_over_state &&other)                 = delete;
        game_over_state &operator=(game_over_state const &other) = delete;
        game_over_state &operator=(game_over_state &&other)      = delete;

        void on_enter() override;
        void update() override;
        void on_exit() override;

    private:
        float game_over_time_ = 5.0f;
        float accu_time_      = 0.0f;
        
        struct current_scene
        {
            mngn::scene                             *scene_ptr;
            mngn::game_object                       *root_ptr;
            std::vector<jump_component*>            jump_comp_ptrs;
            std::vector<spawn_component*>           spawn_comp_ptrs;
            std::vector<fall_component*>            fall_comp_ptrs;
            std::vector<flicker_component*>         flicker_comp_ptrs;
            std::vector<mngn::sprite_component*>    sprite_comp_ptrs;
            std::vector<mngn::sprite_ui_component*> sprite_ui_comp_ptrs;
        } current_scene_{};
    };
}
