#include "progress_manager.h"

namespace qbert
{
    void progress_manager::set_cube(std::string const &name, bool has_final_color)
    {
        // cubes_[std::to_string(level_) + '_' + std::to_string(round_)].emplace(name, has_final_color);
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

    void progress_manager::reset()
    {
        level_ = 1;
        round_ = 1;
        score_ = 0;
        health_ = 3;
        cubes_.clear();
    }
}
