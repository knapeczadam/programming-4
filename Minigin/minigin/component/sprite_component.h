#pragma once

// Project includes
#include "minigin/component/family/rendering_component.h"

namespace mngn
{
    // Forward declarations
    class sprite;
    
    class sprite_component final : public rendering_component
    {
    public:
        sprite_component();
        explicit sprite_component(sprite *sprite_ptr);
        ~sprite_component() override;

        sprite_component(sprite_component const &other)            = delete;
        sprite_component(sprite_component &&other)                 = delete;
        sprite_component &operator=(sprite_component const &other) = delete;
        sprite_component &operator=(sprite_component &&other)      = delete;

        void render() const override;
        void update() override;

    private:
        sprite *sprite_ptr_ = nullptr;
    };
}
