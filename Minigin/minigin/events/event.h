#pragma once

namespace mngn
{
    class event
    {
    public:
        virtual ~event() = default;
    };

    class sound_event final : public event
    {
    public:
        int sound_id;
        int volume;
    };
}
