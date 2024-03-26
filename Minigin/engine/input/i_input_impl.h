#pragma once

// Standard includes
#include <vector>

namespace dae
{
    // Forward declarations
    class game_object_command;
    enum class input_state;
    enum class input_type;
    
    // Forward declarations
    struct game_input_command;
    
    class i_input_impl
    {
    public:
        i_input_impl() = default;
        virtual ~i_input_impl() = default;

        i_input_impl(const i_input_impl& other)            = delete;
        i_input_impl(i_input_impl&& other)                 = delete;
        i_input_impl& operator=(const i_input_impl& other) = delete;
        i_input_impl& operator=(i_input_impl&& other)      = delete;
        
        virtual auto do_process_input(std::vector<game_input_command> commands) -> bool = 0;
    };
}