#pragma once

// Project includes
#include "CustomComponent.h"
#include "Observer.h"

namespace dae
{
    class ScoreComponent : public CustomComponent, public Subject
    {
    public:
        ScoreComponent() = default;
        virtual ~ScoreComponent() override = default;

        ScoreComponent(const ScoreComponent& other)            = delete;
        ScoreComponent(ScoreComponent&& other)                 = delete;
        ScoreComponent& operator=(const ScoreComponent& other) = delete;
        ScoreComponent& operator=(ScoreComponent&& other)      = delete;

        void AddScore(int score);
        auto GetScore() const -> int { return m_Score; }

        static auto GetInitialScore() -> int { return 0; }

    private:
        int m_Score = GetInitialScore();
    };
}
