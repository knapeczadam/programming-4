#pragma once

// Project includes
#include "engine/input/game_component_command.h"

namespace dae
{
    // HealthCommand
    class damage_command final : public game_component_command
    {
    public:
        damage_command(game_component *component_ptr, int damage = 1)
            : game_component_command(component_ptr)
            , damage_(damage)
        {
        }
        void execute() override;

        [[nodiscard]] auto clone() const -> std::unique_ptr<base_command> override
        {
            return std::make_unique<damage_command>(*this);
        }

    private:
        int damage_ = 1;
    };

    // ScoreCommand
    class score_command final : public game_component_command
    {
    public:
        score_command(game_component *component_ptr, int score)
            : game_component_command(component_ptr)
            , score_(score)
        {
        }

        [[nodiscard]] auto clone() const -> std::unique_ptr<base_command> override
        {
            return std::make_unique<score_command>(*this);
        }

        void execute() override;

    private:
        int score_ = 0;
    };
}
