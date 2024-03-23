#pragma once

// Project includes
#include "RenderingComponent.h"

// Standard includes
#include <memory>
#include <string>

namespace dae
{
    // Forward declarations
    class Texture2D;
    
    class TextureComponent final : public RenderingComponent
    {
    public:
        TextureComponent() = default;
        TextureComponent(const std::string& filename);
        virtual ~TextureComponent() override = default;

        TextureComponent(const TextureComponent& other)            = delete;
        TextureComponent(TextureComponent&& other)                 = delete;
        TextureComponent& operator=(const TextureComponent& other) = delete;
        TextureComponent& operator=(TextureComponent&& other)      = delete;

        virtual void Render() const override;
        
        void SetTexture(const std::string& filename);
        
    private:
        Texture2D* m_texture = nullptr;
    };
}
