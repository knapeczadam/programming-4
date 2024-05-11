#pragma once

// Project includes
#include "minigin/component/family/custom_component.h"
#include "minigin/core/i_observer.h"

namespace qbert
{
    class round_component final : public mngn::custom_component, public mngn::subject
    {
    public:
        round_component()           = default;
        ~round_component() override = default;

        round_component(round_component const &other)            = delete;
        round_component(round_component &&other)                 = delete;
        round_component &operator=(round_component const &other) = delete;
        round_component &operator=(round_component &&other)      = delete;

        void awake() override;
        
        [[nodiscard]] auto get_round() const -> int { return round_; }
        void set_round(int round);
        void increase_round();

    private:
        int round_ = 1;
    };
}
