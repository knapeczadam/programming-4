#pragma once

// Project includes
#include "minigin/input/game_object_command.h"
#include "minigin/core/i_observer.h"

// GLM includes
#include <glm/glm.hpp>


namespace qbert
{
    // Jump command
    class jump_command final : public mngn::game_object_command, public mngn::i_observer
    {
    public:
        jump_command(mngn::game_object *game_object_ptr, int row, int col)
            : game_object_command{game_object_ptr}
            , row_{row}
            , col_{col}
        {
        }
        
        void execute() override;
        void notify(std::string const &event, mngn::subject *subject_ptr) override;

        [[nodiscard]] auto clone() const -> std::unique_ptr<base_command> override
        {
            return nullptr;
        }

    private:
        int row_ = 0;
        int col_ = 0;

        bool is_jumping_ = false;
    };

    // Reset move command
    class reset_move_command final : public mngn::game_object_command
    {
    public:
        reset_move_command(mngn::game_object *game_object_ptr)
            : game_object_command{game_object_ptr}
        {
        }
        
        void execute() override;

        [[nodiscard]] auto clone() const -> std::unique_ptr<base_command> override
        {
            return std::make_unique<reset_move_command>(*this);
        }
    };
}
