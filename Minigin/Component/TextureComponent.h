#pragma once

// Project includes
#include "BaseComponent.h"

// Standard includes
#include <memory>
#include <string>

namespace dae
{
    // Forward declaration
    class Texture2D;
    
    class TextureComponent : public BaseComponent
    {
    public:
        TextureComponent() = default;
        TextureComponent(const std::string& filename);
        ~TextureComponent() override = default;

        TextureComponent(const TextureComponent& other)            = delete;
        TextureComponent(TextureComponent&& other)                 = delete;
        TextureComponent& operator=(const TextureComponent& other) = delete;
        TextureComponent& operator=(TextureComponent&& other)      = delete;
        
        void Update() override;
        void Render() const override;
        
        void SetTexture(const std::string& filename);
        
    private:
        std::shared_ptr<Texture2D> m_texture{};
    };
}
