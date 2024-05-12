#pragma once

namespace mngn
{
    class game_object;
}

namespace qbert
{
    class player_state
    {
    public:
        explicit player_state(mngn::game_object* player_ptr);
        virtual ~player_state() = default;

        player_state(player_state const &other)            = delete;
        player_state(player_state &&other)                 = delete;
        player_state &operator=(player_state const &other) = delete;
        player_state &operator=(player_state &&other)      = delete;

        virtual void on_enter() { }
        virtual void update()   { }
        virtual void on_exit()  { }

    protected:
        mngn::game_object *player_ptr_ = nullptr;
    };
}
