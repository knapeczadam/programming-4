#pragma once

// Project includes
#include "game_command.h"

namespace dae
{
    // ResetAchievementsCommand
    class reset_achievements_command final : public game_command
    {
    public:
        explicit reset_achievements_command(void* achievement_ptr)
            : achievement_ptr_(achievement_ptr)
        {
        }

        void execute() override;
        
    private:
        void* achievement_ptr_;
    };
}
