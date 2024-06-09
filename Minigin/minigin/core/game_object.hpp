#pragma once

// Project includes
#include "minigin/component/family/collider_component.h"
#include "minigin/core/collision_manager.h"

namespace mngn
{
    // Forward declaration
    class game_object;

    /// \brief Gets a reference to a component of type T on the same GameObject as the component specified.
    /// \tparam T 
    /// \return 
    template <class T> requires child_component<T>
    auto game_object::component() const -> T *
    {
        for (auto const &comp : component_map_ | std::views::values)
        {
            if (auto comp_ptr = dynamic_cast<T*>(comp.get()))
            {
                return comp_ptr;
            }
        }
        return nullptr;
    }

    template <class T> requires family_component<T>
    auto game_object::components() const -> component_multimap_t<T>
    {
        component_multimap_t<T> components;
        for (auto const &[key, comp] : component_map_)
        {
            if (auto comp_ptr = dynamic_cast<T*>(comp.get()))
            {
                components.emplace(key, comp_ptr);
            }
        }
        return components;
    }

    /// \brief Gets a reference to a component of type T on the same GameObject as the component specified, or any child of the GameObject.
    /// \tparam T 
    /// \return 
    template <class T> requires child_component<T>
    auto game_object::component_in_children() const -> T *
    {
        if (auto comp_ptr = component<T>())
        {
            return comp_ptr;
        }
        for (auto const &child_ptr : children_)
        {
            if (auto comp_ptr = child_ptr->component_in_children<T>())
            {
                return comp_ptr;
            }
        }
        return nullptr;
    }

    /// \brief Gets references to all components of type T on the same GameObject as the component specified, and any child of the GameObject.
    /// \tparam T 
    /// \return 
    template <class T> requires child_component<T>
    auto game_object::components_in_children() const -> component_vector_t<T>
    {
        component_vector_t<T> components;
        if (auto comp_ptr = component<T>())
        {
            components.emplace_back(comp_ptr);
        }
        for (auto const &child_ptr : children_)
        {
            for (auto const &comp_ptr : child_ptr->components_in_children<T>())
            {
                components.emplace_back(comp_ptr);
            }
        }
        return components;
    }

    template <class T> requires family_component<T>
    auto game_object::components_in_children() const -> component_multimap_t<T>
    {
        component_multimap_t<T> components;
        for (auto const &[key, comp] : component_map_)
        {
            if (auto comp_ptr = dynamic_cast<T*>(comp.get()))
            {
                components.emplace(key, comp_ptr);
            }
        }
        for (auto const &child_ptr : children_)
        {
            for (auto const &[key, comp_ptr] : child_ptr->components_in_children<T>())
            {
                components.emplace(key, comp_ptr);
            }
        }
        return components;
    }

    /// \brief Gets a reference to a component of type T on the same GameObject as the component specified, or any parent of the GameObject.
    /// \tparam T 
    /// \return 
    template <class T> requires child_component<T>
    auto game_object::component_in_parent() const -> T *
    {
        if (auto comp_ptr = component<T>())
        {
            return comp_ptr;
        }
        if (parent_ptr_)
        {
            return parent_ptr_->component_in_parent<T>();
        }
        return nullptr;
    }

    /// \brief Gets references to all components of type T on the same GameObject as the component specified, and any parent of the GameObject.
    /// \tparam T 
    /// \return 
    template <class T> requires child_component<T>
    auto game_object::components_in_parent() const -> component_vector_t<T> 
    {
        component_vector_t<T> components;
        if (auto comp_ptr = component<T>())
        {
            components.emplace_back(comp_ptr);
        }
        if (parent_ptr_)
        {
            for (auto const &comp_ptr : parent_ptr_->components_in_parent<T>())
            {
                components.emplace_back(comp_ptr);
            }
        }
        return components;
    }

    template <class T> requires family_component<T>
    auto game_object::components_in_parent() const -> component_multimap_t<T>
    {
        component_multimap_t<T> components;
        for (auto const &[key, value] : component_map_)
        {
            if (auto comp_ptr = dynamic_cast<T*>(value.get()))
            {
                components.emplace(key, comp_ptr);
            }
        }
        if (parent_ptr_)
        {
            for (auto const &[key, comp_ptr] : parent_ptr_->components_in_parent<T>())
            {
                components.emplace(key, comp_ptr);
            }
        }
        return components;
    }

    /// \brief Adds a component class of type componentType to the GameObject. 
    /// \tparam T 
    /// \return 
    template <class T, typename... Args> requires implementation_component<T>
    auto game_object::add_component(Args &&... args) -> T *
    {
        auto component = std::make_unique<T>(std::forward<Args>(args)...);
        component->set_owner(this);
        auto comp_ptr = component.get();
        if (auto const collider_comp_ptr = dynamic_cast<collider_component*>(comp_ptr))
        {
            collision_manager::instance().add_collider(collider_comp_ptr);
        }
        component_map_[typeid(T)] = std::move(component);
        return comp_ptr;
    }

    template <class T> requires child_component<T>
    auto game_object::remove_component() -> bool
    {
        if (component_map_.contains(typeid(T)))
        {
            component_map_.erase(typeid(T));
            return true;
        }
        return false;
    }

    template <class T> requires family_component<T>
    auto game_object::remove_components() -> int
    {
        int count = 0;
        for (auto it = component_map_.begin(); it != component_map_.end();)
        {
            if (dynamic_cast<T*>(it->second.get()))
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
}
