#pragma once

// Project includes
#include "minigin/component/family/ui_component.h"

namespace mngn
{
    // Forward declarations
    class sprite;
    
    class sprite_ui_component final : public ui_component
    {
    public:
        sprite_ui_component();
        explicit sprite_ui_component(sprite *sprite_ptr);
        sprite_ui_component(int sprite_id, int texture_id, bool cache = true);
        ~sprite_ui_component() override;

        sprite_ui_component(sprite_ui_component const &other)            = delete;
        sprite_ui_component(sprite_ui_component &&other)                 = delete;
        sprite_ui_component &operator=(sprite_ui_component const &other) = delete;
        sprite_ui_component &operator=(sprite_ui_component &&other)      = delete;

        void render_ui() const override;
        void update() override;

        [[nodiscard]] auto get_sprite() const -> sprite * { return sprite_ptr_; }
        void set_sprite(sprite *sprite_ptr) { sprite_ptr_ = sprite_ptr; }

        void set_animated(bool animated) { animated_ = animated; }

    private:
        sprite *sprite_ptr_ = nullptr;
        bool animated_      = true;
    };
}
