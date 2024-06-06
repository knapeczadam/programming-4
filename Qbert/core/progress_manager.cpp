#include "progress_manager.h"

namespace qbert
{
    void progress_manager::add_score(int score)
    {
        score_ += score;
        if (not first_bonus_activated_ and score_ >= first_bonus_score_)
        {
            first_bonus_activated_ = true;
            bonus_activated_ = true;
        }
        else if (score_ >= second_bonus_score_)
        {
            second_bonus_score_ += bonus_step_;
            bonus_activated_ = true;
        }
    }

    auto progress_manager::health(std::string const &name) const -> int
    {
        if (healths_.contains(name))
        {
            return healths_.at(name);
        }
        return 0;
    }

    void progress_manager::set_health(std::string const &name, int health)
    {
        if (not healths_.contains(name))
        {
            healths_.emplace(name, health);
        }
    }

    void progress_manager::take_damage(std::string const &name, int damage)
    {
        if (healths_.contains(name))
        {
            healths_[name] -= damage;
        }
    }

    void progress_manager::heal(std::string const &name, int health)
    {
        if (healths_.contains(name))
        {
            healths_[name] += health;
        }
    }

    void progress_manager::set_cube(std::string const &name, bool has_final_color)
    {
        auto scene_key = std::to_string(level_) + '_' + std::to_string(round_);
        auto it = cubes_.find(scene_key);
        if (it != cubes_.end())
        {
            it->second[name] = has_final_color;
        }
        else
        {
            cubes_[scene_key].emplace(name, has_final_color);
        }
    }

    auto progress_manager::round_completed() const -> bool
    {
        auto it = cubes_.find(std::to_string(level_) + '_' + std::to_string(round_));
        if (it != cubes_.end())
        {
            auto current_map = it->second;
            return current_map.size() == num_of_cubes_ and std::ranges::all_of(current_map, [](auto const &pair) { return pair.second; });
        }
        return false;
    }

    void progress_manager::add_coin()
    {
        if (coins_ < 9)
        {
            ++coins_;
        }
    }

    void progress_manager::use_coin()
    {
        if (coins_ > 0)
        {
            --coins_;
        }
    }

    void progress_manager::reset()
    {
        level_  = 1;
        round_  = 1;
        score_  = 0;
        cubes_.clear();
        healths_.clear();

        first_bonus_activated_ = false;
        bonus_activated_       = false;
        second_bonus_score_    = bonus_step_;
    }
}
