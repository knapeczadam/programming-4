#pragma once

// Project includes
#include "Transform.h"

// Standard includes
#include <memory>
#include <string>

namespace dae
{
    class Texture2D;

    class GameObject final
    {
    public:
        GameObject() = default;
        virtual ~GameObject();
        
        GameObject(const GameObject& other)            = delete;
        GameObject(GameObject&& other)                 = delete;
        GameObject& operator=(const GameObject& other) = delete;
        GameObject& operator=(GameObject&& other)      = delete;

        virtual void Update();
        virtual void Render() const;

        void SetTexture(const std::string& filename);
        void SetPosition(float x, float y);

    private:
        Transform m_transform{};
        // todo: mmm, every gameobject has a texture? Is that correct?
        std::shared_ptr<Texture2D> m_texture{};
    };
}
