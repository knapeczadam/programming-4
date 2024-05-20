#pragma once

// Project includes
#include "minigin/utility/singleton.h"

namespace qbert
{
    class progress_manager final : public mngn::singleton<progress_manager>
    {
    public:
        ~progress_manager() override = default;

        progress_manager(progress_manager const& other)            = delete;
        progress_manager(progress_manager &&other)                 = delete;
        progress_manager &operator=(progress_manager const &other) = delete;
        progress_manager &operator=(progress_manager &&other)      = delete;

        void set_level(int level) { level_ = level; }
        [[nodiscard]] auto level() const -> int { return level_; }

        void set_round(int round) { round_ = round; }
        [[nodiscard]] auto round() const -> int { return round_; }

        void add_score(int score) { score_ += score; }
        [[nodiscard]] auto score() const -> int { return score_; }

        void reset() { level_ = 1; round_ = 1; score_ = 0; }

    private:
        friend class mngn::singleton<progress_manager>;
        progress_manager() = default;

    private:
        int level_ = 1;
        int round_ = 1;
        int score_ = 0;
    };
}
