#pragma once
#include "Command.h"

namespace dae
{
    // Forward declaration
    class GameObject;

    //---------------------------------------------------------------------------------
    // Base GameObjectCommand
    //---------------------------------------------------------------------------------
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

    //---------------------------------------------------------------------------------
    // GameObject commands
    //---------------------------------------------------------------------------------
    class MoveLeftCommand final : public GameObjectCommand
    {
    public:
        MoveLeftCommand(GameObject* gameObjectPtr) : GameObjectCommand(gameObjectPtr)
        {
        }

        virtual void Execute() override;
    };

    class MoveRightCommand final : public GameObjectCommand
    {
    public:
        MoveRightCommand(GameObject* gameObjectPtr) : GameObjectCommand(gameObjectPtr)
        {
        }

        virtual void Execute() override;
    };

    class MoveUpCommand final : public GameObjectCommand
    {
    public:
        MoveUpCommand(GameObject* gameObjectPtr) : GameObjectCommand(gameObjectPtr)
        {
        }

        virtual void Execute() override;
    };

    class MoveDownCommand final : public GameObjectCommand
    {
    public:
        MoveDownCommand(GameObject* gameObjectPtr) : GameObjectCommand(gameObjectPtr)
        {
        }

        virtual void Execute() override;
    };
}
