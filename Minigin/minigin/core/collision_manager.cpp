#include "collision_manager.h"

#include "minigin/component/family/collider_component.h"
#include "minigin/core/game_object.h"

namespace mngn
{
    void collision_manager::add_collider(collider_component *collider_ptr)
    {
        colliders_.push_back(collider_ptr);
    }

    void collision_manager::register_collider(collider_component *collider_ptr)
    {
        std::erase(colliders_, collider_ptr);
        colliders_to_register_.push_back(collider_ptr);
    }

    void collision_manager::detect_collisions()
    {
        for (auto *collider_ptr : colliders_to_register_)
        {
            if (not collider_ptr->owner()->active() or not collider_ptr->enabled) continue;
            for (auto *other_collider_ptr : colliders_)
            {
                if (check_collision(collider_ptr, other_collider_ptr))
                {
                    collider_ptr->on_trigger_enter(other_collider_ptr->owner());
                }
            }
        }
    }

    auto collision_manager::check_collision(collider_component *collider1_ptr, collider_component *collider2_ptr) const -> bool
    {
        bool collision_x = collider1_ptr->owner()->world_position().x + collider1_ptr->width() >= collider2_ptr->owner()->world_position().x and
                          collider1_ptr->owner()->world_position().x <= collider2_ptr->owner()->world_position().x + collider2_ptr->width();
        bool collision_y = collider1_ptr->owner()->world_position().y + collider1_ptr->height() >= collider2_ptr->owner()->world_position().y and
                          collider1_ptr->owner()->world_position().y <= collider2_ptr->owner()->world_position().y + collider2_ptr->height();
        return collision_x and collision_y;
    }
}
