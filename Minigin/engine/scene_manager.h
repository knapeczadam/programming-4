#pragma once

// Project includes
#include "singleton.h"

// Standard includes
#include <memory>
#include <string>
#include <vector>

namespace dae
{
    // Forward declarations
    class scene;

    // Type aliases
    using scene_ptr = std::unique_ptr<scene>;
    
    class scene_manager final : public singleton<scene_manager>
    {
    public:
        ~scene_manager() override;

        scene_manager(const scene_manager& other)            = delete;
        scene_manager(scene_manager&& other)                 = delete;
        scene_manager& operator=(const scene_manager& other) = delete;
        scene_manager& operator=(scene_manager&& other)      = delete;
        
        auto create_scene(const std::string& name) -> scene*;

        void update();
        void late_update();
        void render();
        void render_ui();

    private:
        friend class singleton<scene_manager>;
        scene_manager();
        
        std::vector<scene_ptr> scenes_;
    };
}
