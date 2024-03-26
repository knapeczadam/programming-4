#pragma once

// Project includes
#include "game_command.h"

namespace dae
{
    // Forward declarations
    class base_component;
    
    class game_component_command : public game_command
    {
    public:
        game_component_command(base_component* component_ptr) : component_ptr_(component_ptr)
        {
        }

        ~game_component_command() override = default;

        game_component_command(const game_component_command& other) = delete;
        game_component_command(game_component_command&& other) = delete;
        game_component_command& operator=(const game_component_command& other) = delete;
        game_component_command& operator=(game_component_command&& other) = delete;

    protected:
        auto get_game_component() const -> base_component* { return component_ptr_; }

    private:
        base_component* component_ptr_;
        
    };
    
    // HealthCommand
    class damage_command final : public game_component_command
    {
    public:
        damage_command(base_component* component_ptr, int damage = 1)
            : game_component_command(component_ptr)
            , damage_(damage)
        {
        }
        void execute() override;

    private:
        int damage_ = 1;
    };

    // ScoreCommand
    class score_command final : public game_component_command
    {
    public:
        score_command(base_component* component_ptr, int score)
            : game_component_command(component_ptr)
            , score_(score)
        {
        }

        void execute() override;

    private:
        int score_ = 0;
    };
}
