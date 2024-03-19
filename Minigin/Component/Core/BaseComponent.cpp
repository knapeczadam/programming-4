#include "BaseComponent.h"

// Standard includes
#include <cassert>

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
    }
}
