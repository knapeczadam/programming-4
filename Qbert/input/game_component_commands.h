#pragma once

// Project includes
#include "minigin/input/game_component_command.h"

// Standard includes
#include <string>

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

    class game_mode_select_command final : public mngn::game_component_command
    {
    public:
        explicit game_mode_select_command(mngn::game_component *component_ptr, int dir);

        void execute() override;

        [[nodiscard]] auto clone() const -> std::unique_ptr<base_command> override
        {
            return std::make_unique<game_mode_select_command>(*this);
        }

    private:
        void update_underline(std::string const &scene_name);

    private:
        int dir_ = 0;
    };
    
    class game_mode_accept_command final : public mngn::game_component_command
    {
    public:
        explicit game_mode_accept_command(mngn::game_component *component_ptr);

        void execute() override;

        [[nodiscard]] auto clone() const -> std::unique_ptr<base_command> override
        {
            return std::make_unique<game_mode_accept_command>(*this);
        }
    };

    class input_select_command final : public mngn::game_component_command
    {
    public:
        explicit input_select_command(mngn::game_component *component_ptr, int dir);
        void execute() override;
        
        [[nodiscard]] auto clone() const -> std::unique_ptr<base_command> override
        {
            return std::make_unique<input_select_command>(*this);
        }

    private:
        int dir_;
    };

    class input_accept_command final : public mngn::game_component_command
    {
    public:
        explicit input_accept_command(mngn::game_component *component_ptr);
        void execute() override;

        [[nodiscard]] auto clone() const -> std::unique_ptr<base_command> override
        {
            return std::make_unique<input_accept_command>(*this);
        }
    };
}
