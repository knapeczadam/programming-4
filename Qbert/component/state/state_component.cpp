#include "state_component.h"

// Project includes
#include "minigin/core/game_object.h"
#include "state/null_state.h"

namespace qbert
{
    state_component::state_component()
        : state_{std::make_unique<null_state>()}
    {
    }

    void state_component::update()
    {
        state_->update();
    }
}
