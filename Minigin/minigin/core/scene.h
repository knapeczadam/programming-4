#pragma once

// Standard includes
#include <memory>
#include <string>
#include <vector>

namespace mngn
{
    // Forward declarations
    class game_object;
    class scene_manager;

    // Type aliases
    using game_object_uptr = std::unique_ptr<game_object>;
    
    class scene final
    {
        friend class scene_manager;

    public:
        ~scene();
        
        scene(scene const &other)            = delete;
        scene(scene &&other)                 = delete;
        scene &operator=(scene const &other) = delete;
        scene &operator=(scene &&other)      = delete;

        void awake();
        void on_enable();
        void start();
        void fixed_update();
        void update();
        void late_update();
        void render() const;
        void render_ui() const;
        void on_disable();

        [[nodiscard]] auto name() const -> std::string const & { return name_; }

        auto create_game_object(std::string const &name = "new_game_object") -> game_object *;
        void remove(game_object *game_object_ptr);
        void remove_all();
        [[nodiscard]] auto count() const -> int;
        [[nodiscard]] auto find(std::string const &name, bool include_inactive = false) const -> game_object *;
        [[nodiscard]] auto find_game_objects_with_tag(std::string const &tag, bool include_inactive = false) const -> std::vector<game_object*>;
        [[nodiscard]] auto objects() const -> std::vector<game_object*>;

        [[nodiscard]] auto active() const -> bool { return active_; }
        void set_active(bool active) { active_ = active; }

        [[nodiscard]] auto tag() const -> std::string const & { return tag_; }
        void set_tag(std::string tag) { tag_ = std::move(tag); }
        void clear_tag() { tag_.clear(); }
        
    private:
        explicit scene(std::string name);

        std::string name_;
        std::string tag_;
        std::vector<game_object_uptr> objects_{};
        bool active_ = true;

        static unsigned int id_counter_;
    };
}
