#pragma once

// Project includes
#include "minigin/utility/singleton.h"

// Standard includes
#include <set>

namespace mngn
{
    // Forward declarations
    class sound_effect;
    class sound_stream;
    
    class sound_manager final : public singleton<sound_manager>
    {
    public:
        ~sound_manager() override = default;

        sound_manager(sound_manager const &other)            = delete;
        sound_manager(sound_manager &&other)                 = delete;
        sound_manager &operator=(sound_manager const &other) = delete;
        sound_manager &operator=(sound_manager &&other)      = delete;

        void toggle_mute();

        [[nodiscard]] auto volume() const -> int { return volume_; }
        void set_volume(int const value) { volume_ = value; }

        auto register_effect(int id) -> sound_manager &;
        auto register_stream(int id) -> sound_manager &;

        void play_sound(int id, int volume);

    private:
        friend class singleton<sound_manager>;
        sound_manager() : volume_{ 100 }, previous_volume_{ 100 } {}

    private:
        int  volume_          = 100;
        int  previous_volume_ = 100;
        bool muted_           = false;

        std::set<int> registered_effects_;
        std::set<int> registered_streams_;

        std::set<sound_effect*> sound_effects_;
        std::set<sound_stream*> sound_streams_;
    };
}
