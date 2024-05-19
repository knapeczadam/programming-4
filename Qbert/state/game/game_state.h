#pragma once
#include "state/state.h"

// Forward declarations
namespace mngn
{
    class scene;
}

namespace qbert
{
    // Forward declarations
    class game_state_component;
    
    class game_state : public state
    {
    public:
        explicit game_state(game_state_component *game_state_comp_ptr);
        ~game_state() override = default;

        game_state(game_state const &other)            = delete;
        game_state(game_state &&other)                 = delete;
        game_state &operator=(game_state const &other) = delete;
        game_state &operator=(game_state &&other)      = delete;

    protected:
        game_state_component *game_state_comp_ptr_ = nullptr;
        mngn::scene *scene_ptr_ = nullptr;
    };
}
