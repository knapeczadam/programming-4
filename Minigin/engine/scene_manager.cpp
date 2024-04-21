#include "scene_manager.h"

// Project includes
#include "scene.h"
#include "core/game_object.h"

namespace dae
{
    scene_manager::scene_manager() = default;

    scene_manager::~scene_manager() = default;

    void scene_manager::update()
    {
        for (auto const & scene : scenes_)
        {
            scene->update();
        }
    }

    void scene_manager::late_update()
    {
        for (auto const &scene : scenes_)
        {
            scene->late_update();
        }
    }

    void scene_manager::render()
    {
        for (auto const &scene : scenes_)
        {
            scene->render();
        }
    }

    void scene_manager::render_ui()
    {
        for (auto const &scene : scenes_)
        {
            scene->render_ui();
        }
    }

    auto scene_manager::create_scene(std::string const &name) -> scene *
    {
        scenes_.emplace_back(std::unique_ptr<scene>(new scene(name)));
        return scenes_.back().get();
    }
}
