#pragma once

// Project includes
#include "state/game/game_state.h"

// Standard includes
#include <string>

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
        void animate_qbert();

    private:
        float switch_time_ = 10.0f;
        float accu_time_   = 0.0f;
        int menu_idx_ = 0;
        mngn::game_object *disk_ptr_ = nullptr;
        glm::vec2 const start_pos_ = {-36.0f, 374.0f};
        glm::vec2 const end_pos_ = {480, 374.0f};
    };
}
