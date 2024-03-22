#include "BaseComponent.h"

// Standard includes
#include <cassert>

// Project includes
#include "GameObject.h"

namespace dae
{
    void BaseComponent::SetOwner(GameObject* ownerPtr)
    {
        assert(ownerPtr != nullptr and "BaseComponent::SetOwner: ownerPtr is nullptr");
        if (not ownerPtr)
        {
            return;
        }
        m_ownerPtr = ownerPtr;
        // Note: SetOwner is called by GameObject::AddComponent<T> after the component is created
    }
}
