#include "collision_manager.h"

// Project includes
#include "minigin/component/family/collider_component.h"
#include "minigin/core/game_object.h"
#include "minigin/core/renderer.h"
#include "minigin/core/scene.h"

// SDL includes
#include <SDL_rect.h>

namespace mngn
{
    void collision_manager::add_collider(collider_component *collider_ptr)
    {
        colliders_[collider_ptr->owner()->scene()->name()].push_back(collider_ptr);
    }

    void collision_manager::register_collider(collider_component *collider_ptr)
    {
        auto &colliders = colliders_[collider_ptr->owner()->scene()->name()];
        std::erase(colliders, collider_ptr);
             
        registered_colliders_.push_back(collider_ptr);
    }

    void collision_manager::detect_collisions()
    {
        for (auto *collider_ptr : registered_colliders_)
        {
            if (collider_ptr->owner()->scene()->active() and collider_ptr->owner()->active() and collider_ptr->enabled())
            {
                auto colliders = colliders_[collider_ptr->owner()->scene()->name()];
                for (auto const &other_collider_ptr : colliders)
                {
                    if (other_collider_ptr->owner()->active() and other_collider_ptr->enabled())
                    {
                        if (check_collision(collider_ptr, other_collider_ptr))
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
        for (auto const &collider_ptr : colliders_ | std::views::values | std::views::join)
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
        bool const collision_x = pos_1.x + collider_1_ptr->width() >= pos_2.x and pos_1.x <= pos_2.x + collider_2_ptr->width();
        bool const collision_y = pos_1.y + collider_1_ptr->height() >= pos_2.y and pos_1.y <= pos_2.y + collider_2_ptr->height();
        return collision_x and collision_y;
    }
}
