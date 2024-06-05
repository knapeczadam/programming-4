#pragma once

// Standard includes
#include <vector>

namespace mngn
{
    // Forward declarations
    enum class input;
    
    // Forward declarations
    struct input_config_info;
    
    class i_input
    {
    public:
        i_input()          = default;
        virtual ~i_input() = default;

        i_input(i_input const &other)            = delete;
        i_input(i_input &&other)                 = delete;
        i_input &operator=(i_input const &other) = delete;
        i_input &operator=(i_input &&other)      = delete;
        
        virtual auto do_process_input(std::vector<input_config_info> input_configs) -> bool = 0;

    protected:
        virtual int remap(input input) = 0;
    };
}