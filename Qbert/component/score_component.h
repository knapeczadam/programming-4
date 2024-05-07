#pragma once

// Project includes
#include "minigin/component/family/custom_component.h"
#include "minigin/core/i_observer.h"

namespace qbert
{
    class score_component final : public mngn::custom_component, public mngn::subject
    {
    public:
        score_component()           = default;
        ~score_component() override = default;

        score_component(score_component const &other)            = delete;
        score_component(score_component &&other)                 = delete;
        score_component &operator=(score_component const &other) = delete;
        score_component &operator=(score_component &&other)      = delete;

        void add_score(int const score);
        [[nodiscard]] auto get_score() const -> int { return score_; }

        static auto get_initial_score() -> int { return 0; }

    private:
        int score_ = get_initial_score();
        bool achievement_unlocked_ = false;
    };
}
