#pragma once

// Project includes
#include "minigin/utility/singleton.h"

// Standard includes
#include <vector>

namespace mngn
{
    // Forward declarations
    class collider_component;
    
    class collision_manager final : public singleton<collision_manager>
    {
    public:
        ~collision_manager() override = default;

        collision_manager(collision_manager const &other)            = delete;
        collision_manager(collision_manager &&other)                 = delete;
        collision_manager &operator=(collision_manager const &other) = delete;
        collision_manager &operator=(collision_manager &&other)      = delete;

        void add_collider(collider_component *collider_ptr);
        void register_collider(collider_component *collider_ptr);
        void detect_collisions();

    private:
        [[nodiscard]] auto check_collision(collider_component *collider1_ptr, collider_component *collider2_ptr) const -> bool;

    private:
        friend class singleton<collision_manager>;
        collision_manager() = default;

    private:
        std::vector<collider_component*> colliders_;
        std::vector<collider_component*> colliders_to_register_;
    };
}
