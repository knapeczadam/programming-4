#pragma once

// Project includes
#include "state/character/character_state.h"

namespace qbert
{
    // Forward declarations
    class disk_component;
    
    class flying_state final : public character_state
    {
    public:
        explicit flying_state(mngn::game_object* character_ptr, disk_component* disk_comp_ptr);

        void on_enter() override;
        void update()   override;
        void on_exit()  override;

    private:
        disk_component *disk_comp_ptr_ = nullptr;
        float accu_time_ = 0.0f;
        float flash_time = 0.3f;
        float fly_time_  = 3.0f;
    };
}
