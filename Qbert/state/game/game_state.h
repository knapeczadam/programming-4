#pragma once
#include "state/i_state.h"

namespace mngn
{
    class scene;
}

namespace qbert
{
    class game_state : public i_state
    {
    public:
        game_state() = default;
        explicit game_state(mngn::scene *scene_ptr);
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
