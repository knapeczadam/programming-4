#pragma once

// Project includes
#include "RenderComponent.h"

// Standard includes
#include <memory>
#include <string>

namespace dae
{
    // Forward declarations
    class Texture2D;
    
    class TextureComponent : public RenderComponent
    {
    public:
        TextureComponent() = default;
        virtual ~TextureComponent() override = default;

        TextureComponent(const TextureComponent& other)            = delete;
        TextureComponent(TextureComponent&& other)                 = delete;
        TextureComponent& operator=(const TextureComponent& other) = delete;
        TextureComponent& operator=(TextureComponent&& other)      = delete;

        virtual void Render() const override;
        virtual ComponentType GetType() const override { return ComponentType::Texture; }
        void SetTexture(const std::string& filename);
        
    private:
        Texture2D* m_texture{};
    };
}
