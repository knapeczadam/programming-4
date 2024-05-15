#pragma once

#include "state/i_state.h"

namespace mngn
{
    class game_object;
}

namespace qbert
{
    class player_state : public i_state
    {
    public:
        explicit player_state(mngn::game_object* player_ptr);
        ~player_state() override = default;

        player_state(player_state const &other)            = delete;
        player_state(player_state &&other)                 = delete;
        player_state &operator=(player_state const &other) = delete;
        player_state &operator=(player_state &&other)      = delete;

        void on_enter() override { }
        void update()   override { }
        void on_exit()  override { }

    protected:
        mngn::game_object *player_ptr_ = nullptr;
    };
}
