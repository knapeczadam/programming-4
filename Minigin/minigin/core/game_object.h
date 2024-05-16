#pragma once

// Project includes
#include "minigin/utility/transform.h"

// Standard includes
#include <algorithm>
#include <memory>
#include <ranges>
#include <set>
#include <string>
#include <typeindex>
#include <vector>
#include <unordered_map>

namespace mngn
{
    // Forward declarations
    enum class component_family;
    class game_component;

    // Concepts
    template <class T>
    concept family_component = std::is_base_of_v<game_component, T> and std::is_abstract_v<T>;

    template <class T>
    concept child_component = std::is_base_of_v<game_component, T> and std::is_constructible_v<T>;

    // Type aliases
    using component_map = std::unordered_map<std::type_index, game_component*>;
    using component_multimap = std::unordered_multimap<std::type_index, game_component*>;
    
    template <class T>
    using component_multimap_t = std::unordered_multimap<std::type_index, T*>;

    template <class T>
    using component_vector_t = std::vector<T*>;

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

        [[nodiscard]] auto name() const -> std::string { return name_; }
        [[nodiscard]] auto find(std::string const &name) const -> game_object *;

        [[nodiscard]] auto has_tag(std::string const &tag) const -> bool { return tags_.contains(tag); }
        void add_tag(std::string const &tag) { tags_.insert(tag); }
        void add_tags(std::set<std::string> const &tags) { tags_.insert(tags.begin(), tags.end()); }

        void awake();
        void start();
        void fixed_update();
        void update();
        void update_world_position();
        void late_update();

        [[nodiscard]] auto active() const -> bool { return active_; }
        void set_active(bool active) { active_ = active; }

        [[nodiscard]] auto parent() const -> game_object * { return parent_ptr_; }
        auto set_parent(game_object *parent_ptr, bool keep_world_position = true) -> bool;
        auto has_child(game_object *child_ptr) const -> bool;

        [[nodiscard]] auto child_count() const -> int;
        [[nodiscard]] auto child_at(int const index) const -> game_object *;

        auto remove_component(game_component const *component_ptr) -> bool;
        auto remove_components(component_family const family_type) -> int;

        [[nodiscard]] auto has_component(component_family family_type) const -> bool;

        [[nodiscard]] auto components(component_family const family_type) const -> component_map;
        [[nodiscard]] auto components() const -> component_map;

        [[nodiscard]] auto components_in_children(component_family family_type) const -> component_multimap;
        [[nodiscard]] auto components_in_children() const -> component_multimap;

        [[nodiscard]] auto components_in_parent(component_family family_type) const -> component_multimap;
        [[nodiscard]] auto components_in_parent() const -> component_multimap;

        template <class T, typename... Args> requires child_component<T>
        auto add_component(Args &&... args) -> T *;

        template <class T> requires child_component<T>
        [[nodiscard]] auto component() const -> T *;

        template <class T> requires family_component<T>
        [[nodiscard]] auto components() const -> component_multimap_t<T>;

        template <class T> requires child_component<T>
        [[nodiscard]] auto component_in_children() const -> T *;

        template <class T> requires child_component<T>
        [[nodiscard]] auto components_in_children() const -> component_vector_t<T>;

        template <class T> requires family_component<T>
        [[nodiscard]] auto components_in_children() const -> component_multimap_t<T>;

        template <class T> requires child_component<T>
        [[nodiscard]] auto component_in_parent() const -> T *;

        template <class T> requires child_component<T>
        [[nodiscard]] auto components_in_parent() const -> component_vector_t<T>;

        template <class T> requires family_component<T>
        [[nodiscard]] auto components_in_parent() const -> component_multimap_t<T>;

        template <class T> requires child_component<T>
        auto remove_component() -> bool;

        template <class T> requires family_component<T>
        auto remove_components() -> int;

        template <class T> requires child_component<T>
        [[nodiscard]] auto has_component() const -> bool;

        template <class T> requires family_component<T>
        [[nodiscard]] auto has_component() const -> bool;

        auto world_position() -> const glm::vec3 &;
        [[nodiscard]] auto local_position() const -> const glm::vec3 &;

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
        bool active_          = true;
        std::set<std::string>   tags_;

        // TODO: switch to map?
        std::unordered_map<std::type_index, std::unique_ptr<game_component>> component_map_ = {};

        game_object *parent_ptr_            = nullptr;
        std::vector<game_object*> children_ = {};
    };
}

#include "game_object.hpp"
