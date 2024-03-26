#pragma once

// Project includes
#include "base_command.h"

namespace dae
{
    // Forward declarations
    class base_component;
    
    class component_command : public base_command
    {
    public:
        component_command(base_component* component_ptr) : component_ptr_(component_ptr)
        {
        }

        ~component_command() override = default;

        component_command(const component_command& other) = delete;
        component_command(component_command&& other) = delete;
        component_command& operator=(const component_command& other) = delete;
        component_command& operator=(component_command&& other) = delete;

    protected:
        auto get_game_component() const -> base_component* { return component_ptr_; }

    private:
        base_component* component_ptr_;
        
    };
    
    // HealthCommand
    class damage_command final : public component_command
    {
    public:
        damage_command(base_component* component_ptr, int damage = 1)
            : component_command(component_ptr)
            , damage_(damage)
        {
        }
        void execute() override;

    private:
        int damage_ = 1;
    };

    // ScoreCommand
    class score_command final : public component_command
    {
    public:
        score_command(base_component* component_ptr, int score)
            : component_command(component_ptr)
            , score_(score)
        {
        }

        void execute() override;

    private:
        int score_ = 0;
    };
}
