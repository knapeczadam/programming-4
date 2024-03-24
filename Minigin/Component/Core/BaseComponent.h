#pragma once

namespace dae
{
    // Forward declarations
    class GameObject;

    enum class ComponentFamily
    {
        Audio,
        Custom,
        Physics,
        Rendering,
        UI,
        Test
    };
    
    class BaseComponent
    {
        friend class GameObject;
        
    public:
        BaseComponent() = default;
        virtual ~BaseComponent() = default;

        BaseComponent(const BaseComponent& other)            = delete;
        BaseComponent(BaseComponent&& other)                 = delete;
        BaseComponent& operator=(const BaseComponent& other) = delete;
        BaseComponent& operator=(BaseComponent&& other)      = delete;

        virtual void Update() { }

        virtual ComponentFamily GetFamily() const = 0;
        
        GameObject* GetOwner() const { return m_ownerPtr; }
        
    private:
        void SetOwner(GameObject* ownerPtr);
        
    private:
        GameObject* m_ownerPtr = nullptr;
    };
}
