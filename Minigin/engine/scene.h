#pragma once

// Standard includes
#include <memory>
#include <string>
#include <vector>

namespace dae
{
    // Forward declarations
    class game_object;
    class scene_manager;

    // Type aliases
    using game_object_ptr = std::unique_ptr<game_object>;
    
    class scene final
    {
        friend class scene_manager;

    public:
        ~scene();
        
        scene(const scene& other)            = delete;
        scene(scene&& other)                 = delete;
        scene& operator=(const scene& other) = delete;
        scene& operator=(scene&& other)      = delete;

        auto add_game_object(const std::string& name = "New Game Object") -> game_object*;
        void remove_game_object(game_object* object);
        void remove_all();
        auto get_game_object_count() const -> int;
        auto find_game_object(const std::string& name) const -> game_object*;

        void update();
        void late_update();
        void render() const;
        void render_ui() const;

    private:
        explicit scene(std::string name);

        std::string name_;
        std::vector<game_object_ptr> objects_{};

        static unsigned int id_counter_;
    };
}
