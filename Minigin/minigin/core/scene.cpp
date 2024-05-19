#include "scene.h"

// Project includes
#include "minigin/core/game_component.h"
#include "minigin/core/game_object.h"
#include "minigin/component/family/rendering_component.h"
#include "minigin/component/family/ui_component.h"

// Standard includes
#include <algorithm>
#include <iostream>
#include <ranges>

// ImGui includes
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_sdl2.h"

namespace mngn
{
    unsigned int scene::id_counter_ = 0;

    scene::scene(std::string name) : name_{std::move(name)}
    {
    }

    scene::~scene() = default;

    void scene::on_enable()
    {
        for (auto const &object : objects_)
        {
            if (object->active()) object->on_enable();
        }
    }

    void scene::start()
    {
        for (auto const &object : objects_)
        {
            if (object->active()) object->start();
        }
    }

    void scene::fixed_update()
    {
        for (auto const &object : objects_)
        {
            if (object->active()) object->fixed_update();
        }
    }

    void scene::update()
    {
        for (auto const &object : objects_)
        {
            if (object->active()) object->update();
        }
    }

    void scene::late_update()
    {
        for (auto const &object : objects_)
        {
            if (object->active()) object->late_update();
        }
    }

    void scene::render() const
    {
        // TODO: measure performance: get_components_in_children
        for (auto const &object : objects_)
        {
            if (object->active())
            {
                auto const renderers = object->components(component_family::rendering);
                for (auto const &comp : renderers | std::views::values)
                {
                    if (comp->enabled()) static_cast<rendering_component*>(comp)->render();
                }
            }
        }
    }

    void scene::render_ui() const
    {
        for (auto const &object : objects_)
        {
            auto const renderers = object->components(component_family::ui);
            for (auto const &comp : renderers | std::views::values)
            {
                ImGui_ImplOpenGL3_NewFrame();
                ImGui_ImplSDL2_NewFrame();
                ImGui::NewFrame();
            
                if (comp->enabled()) static_cast<ui_component*>(comp)->render_ui();
                
                ImGui::Render();
                ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            }
        }
    }

    void scene::on_disable()
    {
        for (auto const &object : objects_)
        {
            if (object->active()) object->on_disable();
        }
    }

    auto scene::create_game_object(std::string const &name) -> game_object *
    {
        objects_.emplace_back(std::make_unique<game_object>(name, this));
        return objects_.back().get();
    }

    void scene::remove(game_object *game_object_ptr)
    {
        std::erase_if(objects_, [game_object_ptr](auto const &object)
        {
            return object.get() == game_object_ptr;
        });
    }

    void scene::remove_all()
    {
        objects_.clear();
    }

    auto scene::count() const -> int
    {
        return static_cast<int>(objects_.size());
    }

    auto scene::find(std::string const &name) const -> game_object *
    {
        auto const it = std::ranges::find_if(objects_, [&name](auto const &object)
        {
            return object->active() and object->name() == name;
        });

        return it != objects_.end() ? it->get() : nullptr;
    }

    auto scene::find_with_tag(std::string const &tag) const -> std::vector<game_object *>
    {
        std::vector<game_object *> result;
        for (auto const &object : objects_)
        {
            if (object->active() and object->has_tag(tag)) result.push_back(object.get());
        }

        return result;
    }
}
