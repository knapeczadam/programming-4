#include "game_object.h"

// Project includes
#include "component/core/game_component.h"

// Standard includes
#include <algorithm>
#include <ranges>

#include "physics_component.h"

namespace dae
{
    game_object::game_object(std::string name)
        : name_{std::move(name)}
    {
    }

    game_object::~game_object() = default;

    void game_object::fixed_update()
    {
        for (auto const &component_ptr : component_map_ | std::views::values)
        {
            if (auto physics_comp_ptr = dynamic_cast<physics_component*>(component_ptr.get()))
            {
                physics_comp_ptr->fixed_update();
            }
        }
    }

    void game_object::update()
    {
        for (auto const &component_ptr : component_map_ | std::views::values)
        {
            component_ptr->update();
        }
    }

    void game_object::add_child(game_object *child_ptr)
    {
        children_.push_back(child_ptr);
    }

    void game_object::update_world_position()
    {
        if (position_dirty_)
        {
            if (parent_ptr_)
            {
                auto const new_pos = parent_ptr_->get_world_position() + transform_.get_local_position();
                transform_.set_world_position(new_pos);
            }
            else
            {
                transform_.set_world_position(transform_.get_local_position());
            }
        }
        position_dirty_ = false;
    }

    void game_object::late_update()
    {
        if (position_dirty_)
        {
            for (auto const &child : children_)
            {
                child->position_dirty_ = true;
            }
        }
        update_world_position();
    }

    auto game_object::set_parent(game_object *parent_ptr, bool keep_world_position) -> bool
    {
        // SetParent has to do five things:
        // 1. Check if the new parent is valid (not itself or one of its children)
        // 2. Remove itself from the previous parent (if any).
        // 3. Set the given parent on itself.
        // 4. Add itself as a child to the given parent.
        // 5. Update position, rotation and scale

        if (parent_ptr == this or parent_ptr_ == parent_ptr or has_child(parent_ptr))
        {
            return false;
        }
        if (parent_ptr == nullptr)
        {
            set_local_position(get_world_position());
        }
        else
        {
            if (keep_world_position)
            {
                auto const new_pos = get_world_position() - parent_ptr->get_world_position();
                transform_.set_local_position(new_pos);
            }
            position_dirty_ = true;
        }
        if (parent_ptr_)
        {
            parent_ptr_->remove_child(this);
        }
        parent_ptr_ = parent_ptr;
        if (parent_ptr_)
        {
            parent_ptr_->add_child(this);
        }
        return true;
    }

    auto game_object::has_child(game_object *child_ptr) const -> bool
    {
        return std::ranges::any_of(children_, [child_ptr](auto const &child) { return child == child_ptr or child->has_child(child_ptr); });
    }

    /// \brief The number of children the parent Transform has.
    /// \return 
    auto game_object::get_child_count() const -> int
    {
        return static_cast<int>(children_.size());
    }

    /// \brief Returns the child GameObject at the specified index.
    /// \param index 
    /// \return 
    auto game_object::get_child_at(int const index) const -> game_object *
    {
        if (index < 0 or index >= static_cast<int>(children_.size()))
        {
            return nullptr;
        }
        return children_.at(index);
    }

    void game_object::remove_child(game_object *child_ptr)
    {
        children_.erase(std::ranges::remove(children_, child_ptr).begin(), children_.end());
    }

    auto game_object::remove_component(game_component const *component_ptr) -> bool
    {
        for (auto it = component_map_.begin(); it != component_map_.end(); ++it)
        {
            if (it->second.get() == component_ptr)
            {
                component_map_.erase(it);
                return true;
            }
        }
        return false;
    }

    auto game_object::remove_components(component_family const family_type) -> int
    {
    int count = 0;
    for (auto it = component_map_.begin(); it != component_map_.end();)
    {
        if (it->second->get_family() == family_type)
        {
            it = component_map_.erase(it);
            ++count;
        }
        else
        {
            ++it;
        }
    }
    return count;
    }

    auto game_object::has_component(component_family family_type) const -> bool
    {
        return std::ranges::any_of(component_map_ | std::views::values, [family_type](auto const &value) { return value->get_family() == family_type; });
    }

    /// \brief Gets references to all components of type T on the same GameObject as the component specified.
    /// \param family_type 
    /// \return 
    auto game_object::get_components(component_family const family_type) const -> component_map
    {
        component_map components{};
        for (auto const &[key, value] : component_map_)
        {
            if (value->get_family() == family_type)
            {
                components[key] = value.get();
            }
        }
        return components;
    }

    /// \brief Gets references to all components of type T on the same GameObject as the component specified.
    /// \return 
    auto game_object::get_components() const -> component_map
    {
        component_map components{};
        for (auto const &[key, value] : component_map_)
        {
            components[key] = value.get();
        }
        return components;
    }

    /// \brief Gets references to all components of type T on the same GameObject as the component specified, and any child of the GameObject.
    /// \param family_type 
    /// \return 
    auto game_object::get_components_in_children(component_family family_type) const -> component_multimap
    {
        component_multimap components{};
        for (auto const &[key, value] : component_map_)
        {
            if (value->get_family() == family_type)
            {
                components.emplace(key, value.get());
            }
        }
        for (auto const &child : children_)
        {
            for (auto const &[key, value] : child->get_components_in_children(family_type))
            {
                components.emplace(key, value);
            }
        }
        return components;
    }


    /// \brief Gets references to all components of type T on the same GameObject as the component specified, and any child of the GameObject.
    /// \return
    auto game_object::get_components_in_children() const -> component_multimap
    {
        component_multimap components{};
        for (auto const &[key, value] : component_map_)
        {
            components.emplace(key, value.get());
        }
        for (auto const &child : children_)
        {
            for (auto const &[key, value] : child->get_components_in_children())
            {
                components.emplace(key, value);
            }
        }
        return components;
    }

    /// \brief Gets references to all components of type T on the same GameObject as the component specified, and any parent of the GameObject.
    /// \param family_type 
    /// \return 
    auto game_object::get_components_in_parent(component_family family_type) const -> component_multimap
    {
        component_multimap components{};
        for (auto const &[key, value] : component_map_)
        {
            if (value->get_family() == family_type)
            {
                components.emplace(key, value.get());
            }
        }
        if (parent_ptr_)
        {
            for (auto const &[key, value] : parent_ptr_->get_components_in_parent(family_type))
            {
                components.emplace(key, value);
            }
        }
        return components;
    }

    /// \brief Gets references to all components of type T on the same GameObject as the component specified, and any parent of the GameObject.
    /// \return 
    auto game_object::get_components_in_parent() const -> component_multimap
    {
        component_multimap components{};
        for (auto const &[key, value] : component_map_)
        {
            components.emplace(key, value.get());
        }
        if (parent_ptr_)
        {
            for (auto const &[key, value] : parent_ptr_->get_components_in_parent())
            {
                components.emplace(key, value);
            }
        }
        return components;
    }

    auto game_object::get_world_position() -> const glm::vec3 &
    {
        if (position_dirty_)
        {
            update_world_position();
        }
        return transform_.get_world_position();
    }

    auto game_object::get_local_position() const -> const glm::vec3 &
    {
        return transform_.get_local_position();
    }

    void game_object::set_local_position(float x, float y)
    {
        set_local_position(glm::vec3{x, y, transform_.get_local_position().z});
    }

    void game_object::set_local_position(float x, float y, float z)
    {
        set_local_position(glm::vec3{x, y, z});
    }

    void game_object::set_local_position(glm::vec2 const &position)
    {
        set_local_position(glm::vec3{position, transform_.get_local_position().z});
    }

    void game_object::set_local_position(glm::vec3 const &position)
    {
        transform_.set_local_position(position);
        position_dirty_ = true;
    }
}
