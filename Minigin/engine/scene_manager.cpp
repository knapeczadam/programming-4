#include "scene_manager.h"

// Project includes
#include "game_object.h"
#include "scene.h"

namespace dae
{
    void scene_manager::update()
    {
        for (const auto& scene : scenes_)
        {
            scene->update();
        }
    }

    void scene_manager::late_update()
    {
        for (const auto& scene : scenes_)
        {
            scene->late_update();
        }
    }

    void scene_manager::render()
    {
        for (const auto& scene : scenes_)
        {
            scene->render();
        }
    }

    void scene_manager::render_ui()
    {
        for (const auto& scene : scenes_)
        {
            scene->render_ui();
        }
    }

    scene_manager::scene_manager() = default;

    scene_manager::~scene_manager() = default;

    auto scene_manager::create_scene(const std::string& name) -> scene*
    {
        scenes_.emplace_back(std::unique_ptr<scene>(new scene(name)));
        return scenes_.back().get();
    }
}
