#include "score_manager.h"

// Standard includes
#include <fstream>
#include <sstream>
#include <stdexcept>

namespace qbert
{
    void score_manager::set_score(int score, std::string const &name)
    {
        scores_.erase(std::prev(scores_.end()));
        scores_.emplace(score, name);
    }

    auto score_manager::top_score() const -> int
    {
        return scores_.begin()->first;
    }

    auto score_manager::lowest_score() const -> int
    {
        return scores_.rbegin()->first;
    }

    auto score_manager::is_top_score(int score) const -> bool
    {
        return score >= scores_.begin()->first;
    }

    auto score_manager::is_below_lowest_score(int score) const -> bool
    {
        return score < scores_.rbegin()->first;
    }

    auto score_manager::calculate_ranking(int score) const -> int
    {
        int rank = 1;
        for (auto const &[s, _] : scores_)
        {
            if (score > s)
            {
                return rank;
            }
            ++rank;
        }
        return rank;
    }

    void score_manager::load_scoreboard(std::string const &file_path)
    {
        file_path_ = file_path;
        std::ifstream file(file_path_);
        if (file)
        {
            std::string line;
            while (std::getline(file, line))
            {
                std::string name;
                int score;
                std::istringstream iss(line);
                iss >> name >> score;
                scores_.emplace(score, name);
            }
        }
        else
        {
            throw std::runtime_error("Failed to open file: " + file_path_);
        }
    }

    void score_manager::save_scoreboard()
    {
        std::ofstream file(file_path_);
        if (file)
        {
            for (auto const &[score, initial] : scores_)
            {
                file << initial << " " << score << '\n';
            }
        }
        else
        {
            throw std::runtime_error("Failed to open file: " + file_path_);
        }
    }
}
