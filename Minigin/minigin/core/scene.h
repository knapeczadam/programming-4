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
        void fixed_update();
        void update();
        void late_update();
        void render() const;
        void render_ui() const;

        auto create(std::string const &name = "new_game_object") -> game_object *;
        void remove(game_object *game_object_ptr);
        void remove_all();
        [[nodiscard]] auto count() const -> int;
        [[nodiscard]] auto find(std::string const &name) const -> game_object *;
        [[nodiscard]] auto find_with_tag(std::string const &tag) const -> std::vector<game_object *>;

        [[nodiscard]] auto active() const -> bool { return active_; }
        void set_active(bool active) { active_ = active; }
        
    private:
        explicit scene(std::string name);

        std::string name_;
        std::vector<game_object_uptr> objects_{};
        bool active_ = true;

        static unsigned int id_counter_;
    };
}
