﻿#pragma once

// Project includes
#include "minigin/input/game_object_command.h"

namespace qbert
{
    // Jump command
    class jump_command final : public mngn::game_object_command
    {
    public:
        jump_command(mngn::game_object *game_object_ptr, int row_dir, int col_dir)
            : game_object_command{game_object_ptr}
            , row_dir_{row_dir}
            , col_dir_{col_dir}
        {
        }
        
        void execute() override;

        [[nodiscard]] auto clone() const -> std::unique_ptr<base_command> override
        {
            return std::make_unique<jump_command>(*this);
        }

    private:
        int row_dir_ = 0;
        int col_dir_ = 0;
    };
}
