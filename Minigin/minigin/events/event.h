#pragma once

// Project includes
#include "minigin/sound/sound_manager.h"

// Standard includes
#include <memory>

namespace mngn
{
    class event
    {
    public:
        event() = default;
        virtual ~event() = default;

        event(event const &other)            = delete;
        event(event &&other)                 = delete;
        event &operator=(event const &other) = delete;
        event &operator=(event &&other)      = delete;

        template <class T, class... Args>
        [[nodiscard]] static auto create_event(Args &&...args) -> std::unique_ptr<T>
        {
            return std::make_unique<T>(std::forward<Args>(args)...);
        }
    };

    class sound_event final : public event
    {
    public:
        sound_event(int sound_id, int volume)
            : sound_id{sound_id}
            , volume{volume}
        {
        }

        explicit sound_event(int sound_id)
            : sound_id{sound_id}
            , volume{sound_manager::instance().volume()}
        {
            
        }
        
        int sound_id;
        int volume;
    };
}
