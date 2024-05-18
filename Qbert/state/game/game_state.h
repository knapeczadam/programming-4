#pragma once
#include "state/state.h"

namespace mngn
{
    class scene;
}

namespace qbert
{
    class game_state : public state
    {
    public:
        game_state() = default;
        ~game_state() override = default;

        game_state(game_state const &other)            = delete;
        game_state(game_state &&other)                 = delete;
        game_state &operator=(game_state const &other) = delete;
        game_state &operator=(game_state &&other)      = delete;

        void on_enter() override { }
        void update()   override { }
        void on_exit()  override { }

    protected:
        mngn::scene *scene_ptr_ = nullptr;
    };
}
