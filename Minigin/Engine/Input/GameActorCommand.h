#pragma once

// Project includes
#include "Command.h"

// GLM includes
#include <glm/glm.hpp>

namespace dae
{
    class GameActorCommand : public Command
    {
    public:
        GameActorCommand(void* gameActorPtr) : m_GameActorPtr(gameActorPtr)
        {
        }

        virtual ~GameActorCommand() override = default;

        GameActorCommand(const GameActorCommand& other) = delete;
        GameActorCommand(GameActorCommand&& other) = delete;
        GameActorCommand& operator=(const GameActorCommand& other) = delete;
        GameActorCommand& operator=(GameActorCommand&& other) = delete;

    protected:
        void* GetGameActor() const { return m_GameActorPtr; }

    private:
        void* m_GameActorPtr = nullptr;
    };

    // MoveCommand
    class MoveCommand final : public GameActorCommand
    {
    public:
        MoveCommand(void* gameActorPtr, const glm::vec3& direction)
            : GameActorCommand(gameActorPtr)
            , m_Direction(direction)
        {
        }
        
        MoveCommand(void* gameActorPtr, const glm::vec2& direction)
            : GameActorCommand(gameActorPtr)
            , m_Direction(glm::vec3(direction, 0.0f))
        {
        }
        
        virtual void Execute() override;

    private:
        glm::vec3 m_Direction {1.0f, 0.0f, 0.0f};
        float m_Speed{ 1.0f };
    };

    // HealthCommand
    class DamageCommand final : public GameActorCommand
    {
    public:
        DamageCommand(void* gameActorPtr, int damage = 1)
            : GameActorCommand(gameActorPtr)
            , m_Damage(damage)
        {
        }
        void Execute() override;

    private:
        int m_Damage = 1;
    };

    // ScoreCommand
    class ScoreCommand final : public GameActorCommand
    {
    public:
        ScoreCommand(void* gameActorPtr, int score)
            : GameActorCommand(gameActorPtr)
            , m_Score(score)
        {
        }

        void Execute() override;

    private:
        int m_Score = 0;
    };

    // ResetAchievementsCommand
    class ResetAchievementsCommand final : public GameActorCommand
    {
    public:
        ResetAchievementsCommand(void* gameActorPtr)
            : GameActorCommand(gameActorPtr)
        {
        }

        void Execute() override;
    };
}
