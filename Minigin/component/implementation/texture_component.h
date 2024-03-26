#pragma once

// Project includes
#include "rendering_component.h"

// Standard includes
#include <memory>
#include <string>

namespace dae
{
    // Forward declarations
    class texture_2d;
    
    class texture_component final : public rendering_component
    {
    public:
        texture_component() = default;
        explicit texture_component(const std::string& filename);
        ~texture_component() override = default;

        texture_component(const texture_component& other)            = delete;
        texture_component(texture_component&& other)                 = delete;
        texture_component& operator=(const texture_component& other) = delete;
        texture_component& operator=(texture_component&& other)      = delete;

        void render() const override;
        
        void set_texture(const std::string& filename);
        
    private:
        texture_2d* m_texture_ = nullptr;
    };
}
