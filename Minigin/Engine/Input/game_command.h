#pragma once

namespace dae
{
    class game_command
    {
    public:
        game_command() = default;
        virtual ~game_command() = default;

        game_command(const game_command& other)            = delete;
        game_command(game_command&& other)                 = delete;
        game_command& operator=(const game_command& other) = delete;
        game_command& operator=(game_command&& other)      = delete;
        
        virtual void execute() = 0;
    };
}
