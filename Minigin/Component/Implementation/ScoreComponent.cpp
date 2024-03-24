#include "ScoreComponent.h"

namespace dae
{
    void ScoreComponent::AddScore(int score)
    {
        m_Score += score;
        NotifyObservers("ScoreChanged");
    }
}
