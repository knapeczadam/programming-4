#pragma once

// Project includes
#include "minigin/utility/singleton.h"

// Standard includes
#include <memory>
#include <string>
#include <vector>

namespace mngn
{
    // Forward declarations
    class scene;
    class game_object;

    // Type aliases
    using scene_uptr = std::unique_ptr<scene>;
    
    class scene_manager final : public singleton<scene_manager>
    {
    public:
        ~scene_manager() override;

        scene_manager(scene_manager const &other)            = delete;
        scene_manager(scene_manager &&other)                 = delete;
        scene_manager &operator=(scene_manager const &other) = delete;
        scene_manager &operator=(scene_manager &&other)      = delete;

        void awake();
        void fixed_update();
        void update();
        void late_update();
        void render();
        void render_ui();
        
        auto create(std::string const &name) -> scene *;
        [[nodiscard]] auto find_game_objects_with_tag(std::string const &tag) const -> std::vector<game_object*>;

    private:
        friend class singleton<scene_manager>;
        scene_manager();
        
        std::vector<scene_uptr> scenes_;
    };
}
