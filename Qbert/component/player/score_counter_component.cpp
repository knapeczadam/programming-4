#include "score_counter_component.h"

// Project includes
#include "component/character/health_component.h"
#include "component/player/player_health_component.h"
#include "core/audio_player.h"
#include "core/progress_manager.h"
#include "minigin/core/game_object.h"

namespace qbert
{
    void score_counter_component::on_enable()
    {
        notify_observers("update_score_display");
    }

    void score_counter_component::start()
    {
        notify_observers("update_score_display");
    }

    void score_counter_component::on_disable()
    {
        score_ = 0;
    }

    void score_counter_component::add_score(int score)
    {
        score_ += score;
        progress_manager::instance().add_score(score);
        if (progress_manager::instance().bonus_activated())
        {
            owner()->component<player_health_component>()->heal(1);
            progress_manager::instance().deactivate_bonus();
            audio_player::instance().play(audio::bonus);
            
        }
        notify_observers("update_score_display");
    }

    auto score_counter_component::score() const -> int
    {
        return progress_manager::instance().score();
    }
}
