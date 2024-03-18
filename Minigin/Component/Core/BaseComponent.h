#pragma once

namespace dae
{
    // Forward declarations
    class GameObject;

    enum class ComponentFamily
    {
        Audio,
        Effect,
        Physics,
        Render,
        Script,
        UI
    };

    enum class ComponentType
    {
        FPS,
        Text,
        Texture,
        TrashTheCache,
        Movement
    };
    
    class BaseComponent
    {
    public:
        BaseComponent() = default;
        virtual ~BaseComponent() = 0 { }

        BaseComponent(const BaseComponent& other)            = delete;
        BaseComponent(BaseComponent&& other)                 = delete;
        BaseComponent& operator=(const BaseComponent& other) = delete;
        BaseComponent& operator=(BaseComponent&& other)      = delete;

        virtual void Update() { }

        virtual ComponentFamily GetFamily() const = 0;
        virtual ComponentType GetType() const = 0;

        
        GameObject* GetOwner() const { return m_gameObjectPtr; }
        void SetOwner(GameObject* owner) { m_gameObjectPtr = owner; }
        
    private:
        GameObject* m_gameObjectPtr = nullptr;
    };
}
