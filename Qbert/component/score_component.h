#pragma once

// Project includes
#include "component/family/custom_component.h"
#include "core/i_observer.h"

namespace dae
{
    class score_component final : public custom_component, public subject
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
