#pragma once

namespace mngn
{
    // Forward declarations
    enum class resource_id;
    
    class event
    {
    public:
        virtual ~event() = default;
    };

    class sound_event final : public event
    {
    public:
        resource_id sound_id;
        int volume;
    };
}