#include "collision_manager.h"

#include <SDL_rect.h>

#include "renderer.h"
#include "scene.h"
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
        registered_colliders_.push_back(collider_ptr);
    }

    void collision_manager::detect_collisions()
    {
        for (auto *collider_ptr : registered_colliders_)
        {
            if (collider_ptr->owner()->scene()->active() and collider_ptr->owner()->active() and collider_ptr->enabled())
            {
                for (auto *other_collider_ptr : colliders_)
                {
                    if (check_collision(collider_ptr, other_collider_ptr))
                    {
                        if (other_collider_ptr->owner()->active() and other_collider_ptr->enabled())
                        {
                            collider_ptr->on_collision_stay(other_collider_ptr->owner());
                        }
                    }
                }
            }
        }
    }

    void collision_manager::render_colliders() const
    {
        for (auto const &collider_ptr : colliders_)
        {
            if (collider_ptr->owner()->scene()->active())
                render_collider(collider_ptr);
        }
        for (auto const &collider_ptr : registered_colliders_)
        {
            if (collider_ptr->owner()->scene()->active())
                render_collider(collider_ptr);
        }
    }

    void collision_manager::render_collider(collider_component *collider_ptr) const
    {
        SDL_Rect dst_rect{};
        dst_rect.x = static_cast<int>(collider_ptr->owner()->world_position().x + collider_ptr->offset_x());
        dst_rect.y = static_cast<int>(collider_ptr->owner()->world_position().y + collider_ptr->offset_y());
        dst_rect.w = static_cast<int>(collider_ptr->width());
        dst_rect.h = static_cast<int>(collider_ptr->height());
        renderer::instance().render_rect(dst_rect, 255, 255, 255, 255);
    }

    auto collision_manager::check_collision(collider_component *collider_1_ptr, collider_component *collider_2_ptr) const -> bool
    {
        auto const &pos_1 = collider_1_ptr->owner()->world_position() + glm::vec3{collider_1_ptr->offset_x(), collider_1_ptr->offset_y(), 0};
        auto const &pos_2 = collider_2_ptr->owner()->world_position() + glm::vec3{collider_2_ptr->offset_x(), collider_2_ptr->offset_y(), 0};
        bool collision_x = pos_1.x + collider_1_ptr->width() >= pos_2.x and pos_1.x <= pos_2.x + collider_2_ptr->width();
        bool collision_y = pos_1.y + collider_1_ptr->height() >= pos_2.y and pos_1.y <= pos_2.y + collider_2_ptr->height();
        return collision_x and collision_y;
    }
}
