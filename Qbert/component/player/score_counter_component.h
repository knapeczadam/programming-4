#pragma once

// Project includes
#include "minigin/component/family/custom_component.h"
#include "minigin/core/i_observer.h"

namespace qbert
{
    class score_counter_component final : public mngn::custom_component, public mngn::subject
    {
    public:
        score_counter_component()           = default;
        ~score_counter_component() override = default;

        score_counter_component(score_counter_component const &other)            = delete;
        score_counter_component(score_counter_component &&other)                 = delete;
        score_counter_component &operator=(score_counter_component const &other) = delete;
        score_counter_component &operator=(score_counter_component &&other)      = delete;

        void awake() override;

        void add_score(int score);
        [[nodiscard]] auto get_score() const -> int { return score_; }

    private:
        int score_ = 0;
    };
}
