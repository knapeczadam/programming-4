#pragma once

// Project includes
#include "minigin/component/family/custom_component.h"
#include "minigin/core/i_observer.h"

namespace qbert
{
    class level_counter_component final : public mngn::custom_component, public mngn::subject
    {
    public:
        level_counter_component()           = default;
        ~level_counter_component() override = default;

        level_counter_component(level_counter_component const &other)            = delete;
        level_counter_component(level_counter_component &&other)                 = delete;
        level_counter_component &operator=(level_counter_component const &other) = delete;
        level_counter_component &operator=(level_counter_component &&other)      = delete;

        void on_enable() override;
        void start() override;
        
        [[nodiscard]] auto level() const -> int;
        void increase_level();
    };
}
