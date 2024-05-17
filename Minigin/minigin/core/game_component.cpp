#include "game_component.h"

// Project includes
#include "minigin/core/game_object.h"

// Standard includes
#include <cassert>

namespace mngn
{
    void game_component::set_enabled(bool enabled)
    {
        if (enabled and not enabled_)
        {
            enabled_dirty_ = true;
        }
        else if (not enabled and enabled_)
        {
            disabled_dirty_ = true;
        }
        enabled_ = enabled;
    }

    void game_component::set_owner(game_object *owner_ptr)
    {
        assert(owner_ptr != nullptr and "game_component::set_owner: owner_ptr is nullptr");
        if (not owner_ptr)
        {
            return;
        }
        owner_ptr_ = owner_ptr;
        // Note: SetOwner is called by GameObject::AddComponent<T> after the component is created
    }
}
