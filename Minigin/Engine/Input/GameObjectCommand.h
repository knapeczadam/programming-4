#pragma once

// Project includes
#include "Command.h"

// GLM includes
#include <glm/glm.hpp>

namespace dae
{
    // Forward declarations
    class GameObject;

    class GameObjectCommand : public Command
    {
    public:
        GameObjectCommand(GameObject* gameObjectPtr) : m_GameObjectPtr(gameObjectPtr)
        {
        }

        virtual ~GameObjectCommand() override = default;

        GameObjectCommand(const GameObjectCommand& other) = delete;
        GameObjectCommand(GameObjectCommand&& other) = delete;
        GameObjectCommand& operator=(const GameObjectCommand& other) = delete;
        GameObjectCommand& operator=(GameObjectCommand&& other) = delete;

    protected:
        GameObject* GetGameObject() const { return m_GameObjectPtr; }

    private:
        GameObject* m_GameObjectPtr = nullptr;
    };

    class MoveCommand final : public GameObjectCommand
    {
    public:
        MoveCommand(GameObject* gameObjectPtr, const glm::vec3& direction)
            : GameObjectCommand(gameObjectPtr)
            , m_Direction(direction)
        {
        }
        
        MoveCommand(GameObject* gameObjectPtr, const glm::vec2& direction)
            : GameObjectCommand(gameObjectPtr)
            , m_Direction(glm::vec3(direction, 0.0f))
        {
        }
        
        virtual void Execute() override;

    private:
        glm::vec3 m_Direction {1.0f, 0.0f, 0.0f};
        float m_Speed{ 1.0f };
    };
}
