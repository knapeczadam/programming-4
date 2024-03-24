#include "GameActorCommand.h"

// Project includes
#include "Achievement.h"
#include "GameObject.h"
#include "HealthComponent.h"
#include "ScoreComponent.h"

namespace dae
{
    void MoveCommand::Execute()
    {
        const auto go = static_cast<GameObject*>(GetGameActor());
        const auto newPos = go->GetLocalPosition() + m_Direction * m_Speed;
        go->SetLocalPosition(newPos);
    }

    void DamageCommand::Execute()
    {
        static_cast<HealthComponent*>(GetGameActor())->TakeDamage(m_Damage);
    }

    void ScoreCommand::Execute()
    {
        static_cast<ScoreComponent*>(GetGameActor())->AddScore(m_Score);
    }

    void ResetAchievementsCommand::Execute()
    {
        const auto steamAchievements = static_cast<CSteamAchievements*>(GetGameActor());
        steamAchievements->ResetAchievements();
    }
}
