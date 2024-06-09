#include "sound_manager.h"

// Project includes
#include "minigin/core/resource_manager.h"
#include "minigin/sound/sound_effect.h"
#include "minigin/sound/sound_stream.h"

namespace mngn
{
    void sound_manager::toggle_mute()
    {
        if (muted_)
        {
            muted_ = false;
            volume_ = previous_volume_;

            for (auto const effect_ptr : sound_effects_)
            {
                effect_ptr->set_volume(volume_);
            }

            sound_stream::set_volume(volume_);
        }
        else
        {
            muted_ = true;
            previous_volume_ = volume_;
            volume_ = 0;

            for (auto const effect_ptr : sound_effects_)
            {
                effect_ptr->set_volume(0);
            }
            sound_stream::set_volume(0);
        }
    }

    auto sound_manager::register_effect(int id) -> sound_manager &
    {
        registered_effects_.insert(id);
        return *this;
    }

    auto sound_manager::register_stream(int id) -> sound_manager &
    {
        registered_streams_.insert(id);
        return *this;
    }

    void sound_manager::play_sound(int id, int volume)
    {
        if (muted_) return;
        
        if (registered_effects_.contains(id))
        {
            auto effect_ptr = resource_manager::instance().get_sound_effect(id);
            sound_effects_.insert(effect_ptr);
            effect_ptr->set_volume(volume);
            effect_ptr->play(0);
        }
        else if (registered_streams_.contains(id))
        {
            auto stream_ptr = resource_manager::instance().get_sound_stream(id);
            sound_streams_.insert(stream_ptr);
            sound_stream::set_volume(volume);
            stream_ptr->play(0);
        }
    }
}
