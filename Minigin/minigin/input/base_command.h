#pragma once
#include <memory>

namespace mngn
{
    class base_command
    {
    public:
        base_command()          = default;
        virtual ~base_command() = default;

        base_command(base_command const &other)            = default;
        base_command(base_command &&other)                 = default;
        base_command &operator=(base_command const &other) = default;
        base_command &operator=(base_command &&other)      = default;
        
        virtual void execute() = 0;

        [[nodiscard]] virtual auto clone() const -> std::unique_ptr<base_command> = 0;
    };
}
