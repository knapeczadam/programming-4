#pragma once

// Project includes
#include "component/family/rendering_component.h"

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
        explicit texture_component(std::string const &filename);
        texture_component();
        ~texture_component() override;

        texture_component(texture_component const &other)            = delete;
        texture_component(texture_component &&other)                 = delete;
        texture_component &operator=(texture_component const &other) = delete;
        texture_component &operator=(texture_component &&other)      = delete;

        void render() const override;
        
        void set_texture(std::string const &filename);
        
    private:
        texture_2d *m_texture_ptr_ = nullptr;
    };
}
