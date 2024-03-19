#include "GameObjectCommand.h"

// Project includes
#include "GameObject.h"

namespace dae
{
    void MoveCommand::Execute()
    {
        const auto newPos = GetGameObject()->GetPosition() + m_Direction * m_Speed;
        GetGameObject()->SetPosition(newPos);
    }
}
