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
        
        scene(scene const &other)            = delete;
        scene(scene &&other)                 = delete;
        scene &operator=(scene const &other) = delete;
        scene &operator=(scene &&other)      = delete;

        auto add_game_object(std::string const &name = "New Game Object") -> game_object *;
        void remove_game_object(game_object *object_ptr);
        void remove_all();
        [[nodiscard]] auto get_game_object_count() const -> int;
        [[nodiscard]] auto find_game_object(std::string const &name) const -> game_object *;

        void fixed_update();
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
