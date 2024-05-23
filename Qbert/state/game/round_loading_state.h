#pragma once

// Project includes
#include "state/game/game_state.h"

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
    
    class round_loading_state final : public game_state
    {
    public:
        explicit round_loading_state(game_state_component *game_state_comp_ptr);
        ~round_loading_state() override = default;

        round_loading_state(round_loading_state const &other)            = delete;
        round_loading_state(round_loading_state &&other)                 = delete;
        round_loading_state &operator=(round_loading_state const &other) = delete;
        round_loading_state &operator=(round_loading_state &&other)      = delete;

        void on_enter() override;
        void update() override;
        void on_exit() override;

    private:
        float loading_time_ = 5.0f;
        float accu_time_    = 0.0f;

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
