#pragma once

namespace dae
{
    class base_command
    {
    public:
        base_command() = default;
        virtual ~base_command() = default;

        base_command(const base_command& other)            = delete;
        base_command(base_command&& other)                 = delete;
        base_command& operator=(const base_command& other) = delete;
        base_command& operator=(base_command&& other)      = delete;
        
        virtual void execute() = 0;
    };
}
