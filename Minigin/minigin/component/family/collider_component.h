#pragma once

// Project includes
#include "minigin/core/game_component.h"

namespace mngn
{
    // Forward declarations
    class game_object;
    
    class collider_component : public game_component
    {
    public:
        collider_component() = default;
        collider_component(float width, float height) : width_{width}, height_{height} {}
        ~collider_component() override = default;

        collider_component(collider_component const &other)            = delete;
        collider_component(collider_component &&other)                 = delete;
        collider_component &operator=(collider_component const &other) = delete;
        collider_component &operator=(collider_component &&other)      = delete;

        virtual void on_collision_stay([[maybe_unused]] game_object *other_ptr) { }

        [[nodiscard]] auto width() const -> float { return width_; }
        [[nodiscard]] auto height() const -> float { return height_; }

        [[nodiscard]] auto family() const -> component_family override { return component_family::collision; }

    protected:
        float width_  = 0.0f;
        float height_ = 0.0f;
    };
}
