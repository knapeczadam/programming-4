#pragma once

// Project includes
#include "state/state.h"

// Forward declarations
namespace mngn
{
    class game_object;
}

namespace qbert
{
    class character_state : public state
    {
    public:
        explicit character_state(mngn::game_object* player_ptr);
        ~character_state() override = default;

        character_state(character_state const &other)            = delete;
        character_state(character_state &&other)                 = delete;
        character_state &operator=(character_state const &other) = delete;
        character_state &operator=(character_state &&other)      = delete;

    protected:
        mngn::game_object *character_ptr_ = nullptr;
    };
}
