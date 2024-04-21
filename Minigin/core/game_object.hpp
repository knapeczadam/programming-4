#pragma once

namespace dae
{
    // Forward declaration
    class game_object;

    /// \brief Gets a reference to a component of type T on the same GameObject as the component specified.
    /// \tparam T 
    /// \return 
    template <class T> requires is_component_type<T>
    auto game_object::get_component() const -> T *
    {
        if (has_component<T>())
        {
            return static_cast<T*>(component_map_.at(typeid(T)).get());
        }
        return nullptr;
    }

    template <class T> requires is_component_family_type<T>
    auto game_object::get_components() const -> component_multimap_t<T>
    {
        component_multimap_t<T> components;
        for (auto const &[key, value] : component_map_)
        {
            if (auto component_ptr = dynamic_cast<T*>(value.get()))
            {
                components.emplace(key, component_ptr);
            }
        }
        return components;
    }

    /// \brief Gets a reference to a component of type T on the same GameObject as the component specified, or any child of the GameObject.
    /// \tparam T 
    /// \return 
    template <class T> requires is_component_type<T>
    auto game_object::get_component_in_children() const -> T *
    {
        if (auto component_ptr = get_component<T>())
        {
            return component_ptr;
        }
        for (auto const &child : children_)
        {
            if (auto component_ptr = child->get_component_in_children<T>())
            {
                return component_ptr;
            }
        }
        return nullptr;
    }

    /// \brief Gets references to all components of type T on the same GameObject as the component specified, and any child of the GameObject.
    /// \tparam T 
    /// \return 
    template <class T> requires is_component_type<T>
    auto game_object::get_components_in_children() const -> component_multimap_t<T>
    {
        component_multimap_t<T> components;
        if (auto component = get_component<T>())
        {
            components.emplace(typeid(T), component);
        }
        for (auto const &child : children_)
        {
            for (auto const &[key, value] : child->get_components_in_children<T>())
            {
                components.emplace(key, value);
            }
        }
        return components;
    }

    template <class T> requires is_component_family_type<T>
    auto game_object::get_components_in_children() const -> component_multimap_t<T>
    {
        component_multimap_t<T> components;
        for (auto const &[key, value] : component_map_)
        {
            if (auto component_ptr = dynamic_cast<T*>(value.get()))
            {
                components.emplace(key, component_ptr);
            }
        }
        for (auto const &child : children_)
        {
            for (auto const &[key, value] : child->get_components_in_children<T>())
            {
                components.emplace(key, value);
            }
        }
        return components;
    }

    /// \brief Gets a reference to a component of type T on the same GameObject as the component specified, or any parent of the GameObject.
    /// \tparam T 
    /// \return 
    template <class T> requires is_component_type<T>
    auto game_object::get_component_in_parent() const -> T *
    {
        if (auto component_ptr = get_component<T>())
        {
            return component_ptr;
        }
        if (parent_ptr_)
        {
            return parent_ptr_->get_component_in_parent<T>();
        }
        return nullptr;
    }

    /// \brief Gets references to all components of type T on the same GameObject as the component specified, and any parent of the GameObject.
    /// \tparam T 
    /// \return 
    template <class T> requires is_component_type<T>
    auto game_object::get_components_in_parent() const -> component_multimap_t<T> 
    {
        component_multimap_t<T> components;
        if (auto component = get_component<T>())
        {
            components.emplace(typeid(T), component);
        }
        if (parent_ptr_)
        {
            for (auto const &[key, value] : parent_ptr_->get_components_in_parent<T>())
            {
                components.emplace(key, value);
            }
        }
        return components;
    }

    template <class T> requires is_component_family_type<T>
    auto game_object::get_components_in_parent() const -> component_multimap_t<T>
    {
        component_multimap_t<T> components;
        for (auto const &[key, value] : component_map_)
        {
            if (auto component_ptr = dynamic_cast<T*>(value.get()))
            {
                components.emplace(key, component_ptr);
            }
        }
        if (parent_ptr_)
        {
            for (auto const &[key, value] : parent_ptr_->get_components_in_parent<T>())
            {
                components.emplace(key, value);
            }
        }
        return components;
    }

    /// \brief Adds a component class of type componentType to the GameObject. 
    /// \tparam T 
    /// \return 
    template <class T, typename... Args> requires is_component_type<T>
    auto game_object::add_component(Args &&... args) -> T *
    {
        auto component_ptr = std::make_unique<T>(std::forward<Args>(args)...);
        component_ptr->set_owner(this);
        auto copy_ptr = component_ptr.get();
        component_map_[typeid(T)] = std::move(component_ptr);
        return copy_ptr;
    }

    template <class T> requires is_component_type<T>
    auto game_object::remove_component() -> bool
    {
        if (component_map_.contains(typeid(T)))
        {
            component_map_.erase(typeid(T));
            return true;
        }
        return false;
    }

    template <class T> requires is_component_family_type<T>
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

    template <class T> requires is_component_type<T>
    auto game_object::has_component() const -> bool
    {
        return component_map_.contains(typeid(T));
    }

    template <class T> requires is_component_family_type<T>
    auto game_object::has_component() const -> bool
    {
        return std::ranges::any_of(component_map_, [](auto const &pair)
        {
            return dynamic_cast<T*>(pair.second.get());
        });
    }

    
}
