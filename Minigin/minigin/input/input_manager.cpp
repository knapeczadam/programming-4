#include "input_manager.h"

// Project includes
#include "base_command.h"
#include "i_input.h"
#include "sdl_input.h"
#include "x_input.h"

// Standard includes
#include <algorithm>
#include <iostream>

namespace mngn
{
    class input_manager::input_manager_impl
    {
    public:
        input_manager_impl()
        {
            input_impls.push_back(std::make_unique<sdl_input>());
            input_impls.push_back(std::make_unique<x_input>());
        }

        [[nodiscard]] auto do_process_input(std::vector<input_config_info> commands) const -> bool
        {
            return std::ranges::all_of(input_impls, [&commands](auto const &input_impl) { return input_impl->do_process_input(commands); });
        }
        
    public:
        std::vector<std::unique_ptr<i_input>> input_impls;
        
        std::vector<input_config_info> commands_;
        std::vector<std::unique_ptr<base_command>> game_actor_commands;
    };

    input_manager::input_manager()
        : impl_{std::make_unique<input_manager_impl>()}
    {
    }

    input_manager::~input_manager() = default;

    auto input_manager::process_input() const -> bool
    {
        return impl_->do_process_input(impl_->commands_);
    }

    void input_manager::bind_command(input_config_info const &config, std::unique_ptr<base_command> command) const
    {
        impl_->game_actor_commands.emplace_back(std::move(command));
        impl_->commands_.push_back({config.input_type, config.input_state, config.input, config.controller_idx, impl_->game_actor_commands.back().get()});   
    }

    auto input_manager::unbind_command(input_type input_type, input_state input_state, int input) const -> bool
    {
        for (auto it = impl_->commands_.begin(); it != impl_->commands_.end(); ++it)
        {
            if (it->input_type == input_type and it->input_state == input_state and it->input == input)
            {
                impl_->commands_.erase(it);
                return true;
            }
        }
        return false;
    }
}
