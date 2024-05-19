#pragma once

// Project includes
#include "minigin/input/game_component_command.h"

namespace qbert
{
    class damage_command final : public mngn::game_component_command
    {
    public:
        explicit damage_command(mngn::game_component *component_ptr, int damage = 1);
        
        void execute() override;

        [[nodiscard]] auto clone() const -> std::unique_ptr<base_command> override
        {
            return std::make_unique<damage_command>(*this);
        }

    private:
        int damage_ = 1;
    };

    class game_mode_command final : public mngn::game_component_command
    {
    public:
        explicit game_mode_command(mngn::game_component *component_ptr, int game_mode = 0);

        void execute() override;

        [[nodiscard]] auto clone() const -> std::unique_ptr<base_command> override
        {
            return std::make_unique<game_mode_command>(*this);
        }

    private:
        int game_mode_ = 0;
    };
}
