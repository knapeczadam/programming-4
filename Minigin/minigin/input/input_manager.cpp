#include "input_manager.h"

// Project includes
#include "base_command.h"
#include "i_input.h"
#include "sdl_input.h"
#include "x_input.h"

// Standard includes
#include <algorithm>

namespace mngn
{
    struct input_manager::input_manager_impl
    {
        input_manager_impl()
        {
            input_impls.push_back(std::make_unique<sdl_input>());
            input_impls.push_back(std::make_unique<x_input>(0));
            input_impls.push_back(std::make_unique<x_input>(1));
        }

        [[nodiscard]] auto do_process_input(std::vector<input_config_info> input_configs) const -> bool
        {
            return std::ranges::all_of(input_impls, [&input_configs](auto const &input_impl) { return input_impl->do_process_input(input_configs); });
        }
        
        std::vector<std::unique_ptr<i_input>> input_impls;
        
        std::vector<input_config_info> input_configs;
        std::vector<std::unique_ptr<base_command>> commands;
    };

    input_manager::input_manager()
        : impl_{std::make_unique<input_manager_impl>()}
    {
    }

    input_manager::~input_manager() = default;

    auto input_manager::process_input() const -> bool
    {
        return impl_->do_process_input(impl_->input_configs);
    }

    void input_manager::bind_command(input_config_info const &config, std::unique_ptr<base_command> command) const
    {
        impl_->commands.emplace_back(std::move(command));
        impl_->input_configs.push_back({config.input_type, config.input_state, config.input, config.controller_idx, impl_->commands.back().get()});   
    }

    auto input_manager::unbind_command(input_type input_type, input_state input_state, input input) const -> bool
    {
        for (auto it = impl_->input_configs.begin(); it != impl_->input_configs.end(); ++it)
        {
            if (it->input_type == input_type and it->input_state == input_state and it->input == input)
            {
                impl_->input_configs.erase(it);
                return true;
            }
        }
        return false;
    }
}
