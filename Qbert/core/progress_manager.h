#pragma once

// Project includes
#include "minigin/utility/singleton.h"

// Standard includes
#include <algorithm>
# include <string>
#include <unordered_map>

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

        void increase_level() { ++level_; }
        [[nodiscard]] auto level() const -> int { return level_; }

        void increase_round() { ++round_; }
        [[nodiscard]] auto round() const -> int { return round_; }
        void set_round(int round) { round_ = round; }

        void add_score(int score) { score_ += score; }
        [[nodiscard]] auto score() const -> int { return score_; }

        [[nodiscard]] auto health() const -> int { return health_; }
        void take_damage(int damage) { health_ -= damage; }
        void heal(int health) { health_ += health; }

        void set_cube(std::string const& name, bool has_final_color);
        [[nodiscard]] auto round_completed() const -> bool;

        [[nodiscard]] auto coins() const -> int { return coins_; }
        void add_coin();
        void use_coin();

        void reset();

    private:
        friend class mngn::singleton<progress_manager>;
        progress_manager() = default;

    private:
        int level_           = 1;
        int round_           = 1;
        int score_           = 0;
        int health_          = 3;
        int coins_           = 0;
        std::unordered_map<std::string, std::unordered_map<std::string, bool>> cubes_;
        size_t const num_of_cubes_ = 28;
    };
}
