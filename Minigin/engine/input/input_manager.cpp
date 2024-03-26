#include "input_manager.h"

// Project includes
#include "game_command.h"
#include "i_input_impl.h"
#include "sdl_input_impl.h"
#include "x_input_impl.h"

// Standard includes
#include <iostream>

namespace dae
{
    class input_manager::input_manager_impl
    {
    public:
        input_manager_impl()
        {
            input_impls.push_back(std::make_unique<sdl_input_impl>());
            input_impls.push_back(std::make_unique<x_input_impl>());
        }
        
        bool do_process_input(std::vector<game_input_command> commands) const
        {
            for (auto& input_impl : input_impls)
            {
                if (not input_impl->do_process_input(commands))
                {
                    return false;
                }
            }
            return true;
        }
        
    public:
        std::vector<std::unique_ptr<i_input_impl>> input_impls;
        
        std::vector<game_input_command> commands_;
        std::vector<std::unique_ptr<game_command>> game_actor_commands_;
    };

    input_manager::input_manager()
        : impl_ptr_(std::make_unique<input_manager_impl>())
    {
    }

    input_manager::~input_manager() = default;

    auto input_manager::process_input() const -> bool
    {
        return impl_ptr_->do_process_input(impl_ptr_->commands_);
    }

    void input_manager::bind_command(input_type input_type, input_state input_state, int input, std::unique_ptr<game_command> command) const
    {
        impl_ptr_->game_actor_commands_.emplace_back(std::move(command));
        impl_ptr_->commands_.push_back({input_type, input_state, input, impl_ptr_->game_actor_commands_.back().get()});   
    }

    auto input_manager::unbind_command(input_type input_type, input_state input_state, int input) const -> bool
    {
        for (auto it = impl_ptr_->commands_.begin(); it != impl_ptr_->commands_.end(); ++it)
        {
            if (it->input_type == input_type and it->input_state == input_state and it->input == input)
            {
                impl_ptr_->commands_.erase(it);
                return true;
            }
        }
        return false;
    }
        
}
