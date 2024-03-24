#include "GameObjectCommand.h"

// Project includes
#include "GameObject.h"
#include "HealthComponent.h"
#include "ScoreComponent.h"

namespace dae
{
    void MoveCommand::Execute()
    {
        const auto newPos = GetGameObject()->GetLocalPosition() + m_Direction * m_Speed;
        GetGameObject()->SetLocalPosition(newPos);
    }

    void DamageCommand::Execute()
    {
        GetGameObject()->GetComponent<HealthComponent>()->TakeDamage(m_Damage);
    }

    void ScoreCommand::Execute()
    {
        GetGameObject()->GetComponent<ScoreComponent>()->AddScore(m_Score);
    }
}
