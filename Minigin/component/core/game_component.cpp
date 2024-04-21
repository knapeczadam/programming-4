#include "game_component.h"

// Project includes
#include "core/game_object.h"

// Standard includes
#include <cassert>

namespace dae
{
    void game_component::set_owner(game_object *owner_ptr)
    {
        assert(owner_ptr != nullptr and "BaseComponent::SetOwner: ownerPtr is nullptr");
        if (not owner_ptr)
        {
            return;
        }
        owner_ptr_ = owner_ptr;
        // Note: SetOwner is called by GameObject::AddComponent<T> after the component is created
    }
}
