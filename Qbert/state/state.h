#pragma once

namespace qbert
{
    class state
    {
    public:
        state() = default;
        virtual ~state() = default;

        state(state const &other)            = delete;
        state(state &&other)                 = delete;
        state &operator=(state const &other) = delete;
        state &operator=(state &&other)      = delete;

        virtual void on_enter() { }
        virtual void update()   { }
        virtual void on_exit()  { }
    };
}