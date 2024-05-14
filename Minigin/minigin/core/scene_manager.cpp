#include "scene_manager.h"

// Project includes
#include "scene.h"
#include "minigin/core/game_object.h"

// Standard includes
#include <algorithm>

namespace mngn
{
    scene_manager::scene_manager() = default;

    scene_manager::~scene_manager() = default;

    void scene_manager::awake()
    {
        std::ranges::for_each(scenes_, [](auto const &scene) { scene->awake(); });
    }
    
    void scene_manager::fixed_update()
    {
        std::ranges::for_each(scenes_, [](auto const &scene) { scene->fixed_update(); });
    }

    void scene_manager::update()
    {
        std::ranges::for_each(scenes_, [](auto const &scene) { scene->update(); });
    }

    void scene_manager::late_update()
    {
        std::ranges::for_each(scenes_, [](auto const &scene) { scene->late_update(); });
    }

    void scene_manager::render()
    {
        std::ranges::for_each(scenes_, [](auto const &scene) { scene->render(); });
    }

    void scene_manager::render_ui()
    {
        std::ranges::for_each(scenes_, [](auto const &scene) { scene->render_ui(); });
    }

    auto scene_manager::create_scene(std::string const &name) -> scene *
    {
        scenes_.emplace_back(std::unique_ptr<scene>(new scene(name)));
        return scenes_.back().get();
    }
}
