#pragma once

// Project includes
#include "minigin/input/base_command.h"

namespace qbert
{
    class debug_command final : public mngn::base_command
    {
    public:
        explicit debug_command(void *debug_ptr = nullptr);
        void execute() override;
        
        [[nodiscard]] auto clone() const -> std::unique_ptr<base_command> override
        {
            return std::make_unique<debug_command>(*this);
        }
    private:
        void *debug_ptr_ = nullptr;
    };

    class toggle_mute_command final : public mngn::base_command
    {
    public:
        void execute() override;
        
        [[nodiscard]] auto clone() const -> std::unique_ptr<base_command> override
        {
            return std::make_unique<toggle_mute_command>(*this);
        }
    };

    class skip_round_command final : public mngn::base_command
    {
    public:
        void execute() override;
        
        [[nodiscard]] auto clone() const -> std::unique_ptr<base_command> override
        {
            return std::make_unique<skip_round_command>(*this);
        }
    };

    class insert_coin_command final : public mngn::base_command
    {
    public:
        void execute() override;
        
        [[nodiscard]] auto clone() const -> std::unique_ptr<base_command> override
        {
            return std::make_unique<insert_coin_command>(*this);
        }
    };
}
