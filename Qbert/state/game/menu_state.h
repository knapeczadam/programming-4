#pragma once

// Project includes
#include "state/game/game_state.h"

// Standard includes
#include <functional>
#include <queue>

// GLM includes
#include <glm/glm.hpp>

// Forward declarations
namespace mngn
{
    class game_object;
}

namespace qbert
{
    class menu_state final : public game_state
    {
    public:
        explicit menu_state(game_state_component *game_state_comp_ptr);
        ~menu_state() override = default;

        menu_state(menu_state const &other)            = delete;
        menu_state(menu_state &&other)                 = delete;
        menu_state &operator=(menu_state const &other) = delete;
        menu_state &operator=(menu_state &&other)      = delete;

        void on_enter() override;
        void update() override;
        void on_exit() override;

    private:
        void switch_menu();
        void animate_flying_qbert();
        void animate_jumping_qbert();
        void init_events();
        void push_right_event();

    private:
        float switch_time_ = 0.0f;
        float const switch_times_[3] = {5.0f, 21.0f, 10.0f};
        
        float const jump_time_      = 3.0f;
        float const ball_time_      = 16.0f;
        float const ball_fall_time_ = 1.0f;
        float const bump_time_      = 1.0f;
        
        float accu_time_switch_ = 0.0f;
        float accu_time_jump_   = 0.0f;
        float accu_time_ball_   = 0.0f;
        float accu_time_fall_   = 0.0f;
        float accu_time_bump_   = 0.0f;
        
        int  jump_count_   = 0;
        int  menu_idx_     = 0;
        bool ball_falling_ = false;
        bool swearing_     = false;
        
        std::queue<std::function<void()>> events_;
        mngn::game_object *qbert_ptr_ = nullptr;
        mngn::game_object *ball_ptr_  = nullptr;
        mngn::game_object *disk_ptr_  = nullptr;
        
        glm::vec2 const qbert_start_pos_ = {-36.0f, 374.0f};
        glm::vec2 const qbert_end_pos_   = {480, 374.0f};
        
        glm::vec2 const ball_start_pos_ = {110.0f, 96.0f};
        glm::vec2 const ball_bump_pos_  = {110.0f, 362.0f};
        glm::vec2 const ball_pos_1_     = {130.0f, 322.0f};
        glm::vec2 const ball_pos_2_     = {150.0f, 440.0f};
        glm::vec2 const ball_end_pos_   = {150.0f, 512.0f};
        
    };
}
