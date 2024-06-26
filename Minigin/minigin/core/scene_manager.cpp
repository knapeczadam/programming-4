#include "scene_manager.h"

// Project includes
#include "minigin/core/game_object.h"
#include "minigin/core/scene.h"

// Standard includes
#include <algorithm>

namespace mngn
{
    scene_manager::scene_manager() = default;

    scene_manager::~scene_manager() = default;

    void scene_manager::awake()
    {
        for (auto const &scene : scenes_)
        {
            scene->awake();
        }
    }

    void scene_manager::on_enable()
    {
        for (auto const &scene : scenes_)
        {
            if (scene->active()) scene->on_enable();
        }
    }

    void scene_manager::start()
    {
        for (auto const &scene : scenes_)
        {
            scene->start();
        }
    }

    void scene_manager::fixed_update()
    {
        for (auto const &scene : scenes_)
        {
            if (scene->active()) scene->fixed_update();
        }
    }

    void scene_manager::update()
    {
        for (auto const &scene : scenes_)
        {
            if (scene->active()) scene->update();
        }
    }

    void scene_manager::late_update()
    {
        for (auto const &scene : scenes_)
        {
            if (scene->active()) scene->late_update();
        }
    }

    void scene_manager::render()
    {
        for (auto const &scene : scenes_)
        {
            if (scene->active()) scene->render();
        }
    }

    void scene_manager::render_ui()
    {
        for (auto const &scene : scenes_)
        {
            if (scene->active()) scene->render_ui();
        }
    }

    void scene_manager::on_disable()
    {
        for (auto const &scene : scenes_)
        {
            if (scene->active()) scene->on_disable();
        }
    }

    auto scene_manager::create_scene(std::string const &name) -> scene *
    {
        scenes_.emplace_back(std::unique_ptr<scene>(new scene(name)));
        return scenes_.back().get();
    }

    auto scene_manager::find(std::string const &name) -> scene *
    {
        auto const it = std::ranges::find_if(scenes_, [&name](auto const &scene)
        {
            return scene->name() == name;
        });
        return it != scenes_.end() ? it->get() : nullptr;
    }

    auto scene_manager::find_with_tag(std::string const &tag) const -> scene *
    {
        for (auto const &scene : scenes_)
        {
            if (scene->tag() == tag) return scene.get();
        }
        return nullptr;
    }
}
