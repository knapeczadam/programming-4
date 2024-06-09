#pragma once

// Project includes
#include "state/game/game_state.h"

// Standard includes
#include <functional>
#include <queue>

// Forward declarations
namespace mngn
{
    class game_object;
    class scene;
}

namespace qbert
{
    class level_loading_state final : public game_state
    {
    public:
        explicit level_loading_state(game_state_component *game_state_comp_ptr);
        ~level_loading_state() override = default;

        level_loading_state(level_loading_state const &other)            = delete;
        level_loading_state(level_loading_state &&other)                 = delete;
        level_loading_state &operator=(level_loading_state const &other) = delete;
        level_loading_state &operator=(level_loading_state &&other)      = delete;

        void on_enter() override;
        void update()   override;
        void on_exit()  override;

    private:
        void init_events();
        void push_left_event();
        void push_right_event();
        void push_up_event();
        void push_down_event();
        
    private:
        float const intro_time_ = 2.45f;
        float const outro_time_ = 1.0f;
        float total_time_       = 0.0f;
        float const jump_time_  = 0.6f;
        
        float accu_time_intro_ = 0.0f;
        float accu_time_total_ = 0.0f;
        float accu_time_jump_  = 0.0f;
        
        std::queue<std::function<void()>> events_;
        mngn::game_object *qbert_ptr_ = nullptr;
    };
}
