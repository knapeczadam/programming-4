#pragma once

namespace qbert
{
    class i_state
    {
    public:
        i_state() = default;
        virtual ~i_state() = default;

        i_state(i_state const &other)            = delete;
        i_state(i_state &&other)                 = delete;
        i_state &operator=(i_state const &other) = delete;
        i_state &operator=(i_state &&other)      = delete;

        virtual void on_enter() = 0;
        virtual void update()   = 0;
        virtual void on_exit()  = 0;
    };
}