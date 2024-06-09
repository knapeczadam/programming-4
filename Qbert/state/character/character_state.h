#pragma once

// Project includes
#include "core/freezer.h"
#include "state/state.h"

// Forward declarations
namespace mngn
{
    class game_object;
}

namespace qbert
{
    class character_state : public state, public freezer
    {
    public:
        explicit character_state(mngn::game_object* player_ptr);
        ~character_state() override = default;

        character_state(character_state const &other)            = delete;
        character_state(character_state &&other)                 = delete;
        character_state &operator=(character_state const &other) = delete;
        character_state &operator=(character_state &&other)      = delete;

        void on_enter() override { }
        void update()   override { }
        void on_exit()  override { }

    protected:
        mngn::game_object *character_ptr_ = nullptr;
    };
}
