#pragma once

// Project includes
#include "minigin/component/family/custom_component.h"
#include "minigin/core/i_observer.h"

namespace qbert
{
    class round_counter_component final : public mngn::custom_component, public mngn::subject
    {
    public:
        round_counter_component()           = default;
        ~round_counter_component() override = default;

        round_counter_component(round_counter_component const &other)            = delete;
        round_counter_component(round_counter_component &&other)                 = delete;
        round_counter_component &operator=(round_counter_component const &other) = delete;
        round_counter_component &operator=(round_counter_component &&other)      = delete;

        void on_enable() override;
        void start() override;
        void on_disable() override;
        
        [[nodiscard]] auto round() const -> int { return round_; }
        void increase_round();

    private:
        int round_ = 1;
    };
}
