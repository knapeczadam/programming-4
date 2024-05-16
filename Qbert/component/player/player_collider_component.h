﻿#pragma once

// Project includes
#include "minigin/component/family/collider_component.h"

namespace qbert
{
    // Forward declarations
    class direction_component;
    class position_component;
    
    class player_collider_component final : public mngn::collider_component
    {
    public:
        player_collider_component() = default;
        player_collider_component(float width, float height);
        ~player_collider_component() override = default;

        player_collider_component(player_collider_component const &other)            = delete;
        player_collider_component(player_collider_component &&other)                 = delete;
        player_collider_component &operator=(player_collider_component const &other) = delete;
        player_collider_component &operator=(player_collider_component &&other)      = delete;

        void awake() override;
        void on_trigger_enter(mngn::game_object *other_ptr) override;

    private:
        direction_component *direction_comp_ptr_ = nullptr;
        position_component  *position_comp_ptr_  = nullptr;
    };
}
