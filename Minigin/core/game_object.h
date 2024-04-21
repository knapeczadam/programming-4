#pragma once

// Project includes
#include "utility/transform.h"

// Standard includes
#include <algorithm>
#include <memory>
#include <ranges>
#include <string>
#include <typeindex>
#include <unordered_map>

namespace dae
{
    // Forward declarations
    enum class component_family;
    class base_component;

    // Concepts
    template <class T>
    concept is_component_type = std::is_base_of_v<base_component, T> and std::is_constructible_v<T>;

    template <class T>
    concept is_component_family_type = std::is_base_of_v<base_component, T> and std::is_abstract_v<T>;

    // Type aliases
    using component_map = std::unordered_map<std::type_index, base_component*>;
    using component_multimap = std::unordered_multimap<std::type_index, base_component*>;
    
    template <class T>
    using component_multimap_t = std::unordered_multimap<std::type_index, T*>;

    class game_object final
    {
    public:
        game_object() = default;
        explicit game_object(std::string name);
        ~game_object();

        game_object(game_object const &other)            = delete;
        game_object(game_object &&other)                 = delete;
        game_object &operator=(game_object const &other) = delete;
        game_object &operator=(game_object &&other)      = delete;

        [[nodiscard]] auto get_name() const -> std::string { return name_; }

        void fixed_update();
        void update();
        void update_world_position();
        void late_update();

        [[nodiscard]] auto is_alive() const -> bool { return alive_; }
        void destroy() { alive_ = false; }

        [[nodiscard]] auto get_parent() const -> game_object * { return parent_ptr_; }
        auto set_parent(game_object *parent_ptr, bool keep_world_position = true) -> bool;
        auto has_child(game_object *child_ptr) const -> bool;

        [[nodiscard]] auto get_child_count() const -> int;
        [[nodiscard]] auto get_child_at(int const index) const -> game_object *;

        auto remove_component(base_component const *component_ptr) -> bool;
        auto remove_components(component_family const family_type) -> int;

        [[nodiscard]] auto has_component(component_family family_type) const -> bool;

        [[nodiscard]] auto get_components(component_family const family_type) const -> component_map;
        [[nodiscard]] auto get_components() const -> component_map;

        [[nodiscard]] auto get_components_in_children(component_family family_type) const -> component_multimap;
        [[nodiscard]] auto get_components_in_children() const -> component_multimap;

        [[nodiscard]] auto get_components_in_parent(component_family family_type) const -> component_multimap;
        [[nodiscard]] auto get_components_in_parent() const -> component_multimap;

        template <class T, typename... Args> requires is_component_type<T>
        auto add_component(Args &&... args) -> T *;

        // TODO: if not found throw component_not_found_exception
        template <class T> requires is_component_type<T>
        auto get_component() const -> T *;

        template <class T> requires is_component_family_type<T>
        auto get_components() const -> component_multimap_t<T>;

        template <class T> requires is_component_type<T>
        auto get_component_in_children() const -> T *;

        template <class T> requires is_component_type<T>
        auto get_components_in_children() const -> component_multimap_t<T>;

        template <class T> requires is_component_family_type<T>
        auto get_components_in_children() const -> component_multimap_t<T>;

        template <class T> requires is_component_type<T>
        auto get_component_in_parent() const -> T *;

        template <class T> requires is_component_type<T>
        auto get_components_in_parent() const -> component_multimap_t<T>;

        template <class T> requires is_component_family_type<T>
        auto get_components_in_parent() const -> component_multimap_t<T>;

        template <class T> requires is_component_type<T>
        auto remove_component() -> bool;

        template <class T> requires is_component_family_type<T>
        auto remove_components() -> int;

        template <class T> requires is_component_type<T>
        [[nodiscard]] auto has_component() const -> bool;

        template <class T> requires is_component_family_type<T>
        [[nodiscard]] auto has_component() const -> bool;

        auto get_world_position() -> const glm::vec3 &;
        [[nodiscard]] auto get_local_position() const -> const glm::vec3 &;

        void set_local_position(float x, float y);
        void set_local_position(float x, float y, float z);
        void set_local_position(glm::vec2 const &position);
        void set_local_position(glm::vec3 const &position);

    private:
        void add_child(game_object *child_ptr);
        void remove_child(game_object *child_ptr);

    private:
        std::string name_     = {};
        transform transform_  = {};
        bool position_dirty_  = false;
        bool alive_           = true;

        // TODO: switch to map?
        std::unordered_map<std::type_index, std::unique_ptr<base_component>> component_map_ = {};

        game_object *parent_ptr_            = nullptr;
        std::vector<game_object*> children_ = {};
    };
}

#include "game_object.hpp"
