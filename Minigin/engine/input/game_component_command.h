#pragma once

// Project includes
#include "base_command.h"

namespace dae
{
    // Forward declarations
    class game_component;
    
    class game_component_command : public base_command
    {
    public:
        explicit game_component_command(game_component *component_ptr) : component_ptr_(component_ptr)
        {
        }

        ~game_component_command() override = default;

        game_component_command(game_component_command const &other)            = default;
        game_component_command(game_component_command &&other)                 = default;
        game_component_command &operator=(game_component_command const &other) = default;
        game_component_command &operator=(game_component_command &&other)      = default;

    protected:
        [[nodiscard]] auto get_game_component() const -> game_component * { return component_ptr_; }

    private:
        game_component *component_ptr_;
        
    };
    
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
