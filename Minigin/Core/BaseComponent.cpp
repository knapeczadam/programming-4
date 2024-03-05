#include "BaseComponent.h"

namespace dae
{
    void BaseComponent::SetPosition(float x, float y)
    {
        m_transform.SetPosition(x, y, 0.0f);
    }
}
