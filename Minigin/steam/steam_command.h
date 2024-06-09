#pragma once

// Project includes
#include "minigin/input/base_command.h"

namespace steam
{
    // ResetAchievementsCommand
    class reset_achievements_command final : public mngn::base_command
    {
    public:
        explicit reset_achievements_command(void *achievement_ptr)
            : achievement_ptr_(achievement_ptr)
        {
        }

        void execute() override;

        [[nodiscard]] auto clone() const -> std::unique_ptr<base_command> override
        {
            return std::make_unique<reset_achievements_command>(*this);
        }
        
    private:
        void *achievement_ptr_ = nullptr;
    };
}
