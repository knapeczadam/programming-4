#pragma once

// Project includes
#include "minigin/utility/singleton.h"

// Standard includes
#include <map>
#include <string>

namespace qbert
{
    class score_manager final : public mngn::singleton<score_manager>
    {
    public:
        ~score_manager() override = default;

        score_manager(score_manager const& other)            = delete;
        score_manager(score_manager &&other)                 = delete;
        score_manager &operator=(score_manager const &other) = delete;
        score_manager &operator=(score_manager &&other)      = delete;

        [[nodiscard]] auto scores() const -> std::multimap<int, std::string, std::greater<>> const & { return scores_; }
        void set_score(int score, std::string const &initial);
        
        [[nodiscard]] auto top_score() const -> int;
        [[nodiscard]] auto lowest_score() const -> int;
        [[nodiscard]] auto is_top_score(int score) const -> bool;
        [[nodiscard]] auto is_below_lowest_score(int score) const -> bool;
        [[nodiscard]] auto calculate_ranking(int score) const -> int;

        void load_scoreboard(std::string const &file_path);
        void save_scoreboard();

    private:
        friend class mngn::singleton<score_manager>;
        score_manager() = default;

    private:
        std::multimap<int, std::string, std::greater<>> scores_;
        std::string file_path_;
    };
}
