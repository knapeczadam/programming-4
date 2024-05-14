#pragma once

// Project includes
#include "minigin/component/family/rendering_component.h"

// Standard includes
#include <string>

namespace mngn
{
    // Forward declarations
    class texture;
    
    class texture_component final : public rendering_component
    {
    public:
        explicit texture_component(std::string const &filename);
        explicit texture_component(int id);
        texture_component();
        ~texture_component() override;

        texture_component(texture_component const &other)            = delete;
        texture_component(texture_component &&other)                 = delete;
        texture_component &operator=(texture_component const &other) = delete;
        texture_component &operator=(texture_component &&other)      = delete;

        void render() const override;
        
        void set_texture(std::string const &filename);
        
    private:
        texture *m_texture_ptr_ = nullptr;
    };
}
