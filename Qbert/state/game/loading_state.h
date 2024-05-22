#pragma once

// Project includes
#include "state/game/game_state.h"

// Standard includes
#include <queue>
#include <functional>

// Forward declarations
namespace mngn
{
    class game_object;
}

namespace qbert
{
    class loading_state final : public game_state
    {
    public:
        loading_state(game_state_component *game_state_comp_ptr);
        ~loading_state() override = default;

        loading_state(loading_state const &other)            = delete;
        loading_state(loading_state &&other)                 = delete;
        loading_state &operator=(loading_state const &other) = delete;
        loading_state &operator=(loading_state &&other)      = delete;

        void on_enter() override;
        void update() override;
        void on_exit() override;

    private:
        void load_sprites();
        void load_cubes();
        void load_qbert();
        void clean_up();

        void init_events();
        void push_left_event();
        void push_right_event();
        void push_up_event();
        void push_down_event();
        
    private:
        float const intro_time_ = 1.0f;
        float const outro_time_ = 1.0f;
        float total_time_    = 0.0f;
        float const jump_time_ = 0.6f;
        
        float accu_time_intro_ = 0.0f;
        float accu_time_total_ = 0.0f;
        float accu_time_jump_  = 0.0f;
        
        std::queue<std::function<void()>> events_;
        mngn::game_object *qbert_ptr_ = nullptr;
    };
}
