#pragma once

// Project includes
#include "component/state/state_component.h"

namespace qbert
{
    class character_state_component final : public state_component
    {
    public:
        character_state_component() = default;
        ~character_state_component() override = default;

        character_state_component(character_state_component const &other)            = delete;
        character_state_component(character_state_component &&other)                 = delete;
        character_state_component &operator=(character_state_component const &other) = delete;
        character_state_component &operator=(character_state_component &&other)      = delete;

        void start() override;
        void on_enable() override;

    private:
        void init_state();
    };
}
