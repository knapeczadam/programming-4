#pragma once

// Project includes
#include "BaseComponent.h"
#include "RenderComponent.h"

// Standard includes
#include <memory>
#include <string>

namespace dae
{
    // Forward declaration
    class Texture2D;
    
    class TextureComponent : public RenderComponent
    {
    public:
        TextureComponent() = default;
        TextureComponent(const std::string& filename);
        ~TextureComponent() override = default;

        TextureComponent(const TextureComponent& other)            = delete;
        TextureComponent(TextureComponent&& other)                 = delete;
        TextureComponent& operator=(const TextureComponent& other) = delete;
        TextureComponent& operator=(TextureComponent&& other)      = delete;

        void Render() const override;
        ComponentType GetType() const override { return ComponentType::Texture; }
        void SetTexture(const std::string& filename);
        
    private:
        std::shared_ptr<Texture2D> m_texture{};
    };
}
