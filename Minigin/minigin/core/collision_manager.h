#pragma once

// Project includes
#include "minigin/utility/singleton.h"

// Standard includes
#include <string>
#include <unordered_map>
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

        void render_colliders() const;

    private:
        void render_collider(collider_component *collider_ptr) const;
        [[nodiscard]] auto check_collision(collider_component *collider_1_ptr, collider_component *collider_2_ptr) const -> bool;

    private:
        friend class singleton<collision_manager>;
        collision_manager() = default;

    private:
        std::unordered_map<std::string, std::vector<collider_component*>> colliders_;
        std::vector<collider_component*> registered_colliders_;
    };
}
