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
    
    class i_input
    {
    public:
        i_input()          = default;
        virtual ~i_input() = default;

        i_input(i_input const &other)            = delete;
        i_input(i_input &&other)                 = delete;
        i_input &operator=(i_input const &other) = delete;
        i_input &operator=(i_input &&other)      = delete;
        
        virtual auto do_process_input(std::vector<game_input_command> commands) -> bool = 0;
    };
}