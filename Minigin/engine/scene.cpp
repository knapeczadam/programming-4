#include "scene.h"

// Project includes
#include "base_component.h"
#include "game_object.h"
#include "rendering_component.h"
#include "ui_component.h"

// Standard includes
#include <algorithm>
#include <iostream>
#include <ranges>

// ImGui includes
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_sdl2.h"

namespace dae
{
    unsigned int scene::id_counter_ = 0;

    scene::scene(std::string name) : name_(std::move(name))
    {
    }

    scene::~scene() = default;

    auto scene::add_game_object(const std::string& name) -> game_object*
    {
        objects_.emplace_back(std::make_unique<game_object>(name));
        return objects_.back().get();
    }

    void scene::remove_game_object(game_object* object)
    {
        std::erase_if(objects_, [object](const auto& obj)
        {
            return obj.get() == object;
        });
    }

    void scene::remove_all()
    {
        objects_.clear();
    }

    auto scene::get_game_object_count() const -> int
    {
        return static_cast<int>(objects_.size());
    }

    auto scene::find_game_object(const std::string& name) const -> game_object*
    {
        const auto it = std::ranges::find_if(objects_, [&name](const auto& obj)
        {
            return obj->get_name() == name;
        });

        return it != objects_.end() ? it->get() : nullptr;
    }

    void scene::update()
    {
        for (const auto& object : objects_)
        {
            object->update();
        }
    }

    void scene::late_update()
    {
        for (const auto& object : objects_)
        {
            if (object->is_alive())
            {
                object->late_update();
            }
            else
            {
                remove_game_object(object.get());
            }
        }
    }

    void scene::render() const
    {
        for (const auto& object : objects_)
        {
            // TODO: measure performance!
            const auto renderers = object->get_components_in_children(component_family::rendering);
            for (const auto& comp : renderers | std::views::values)
            {
                static_cast<rendering_component*>(comp)->render();
            }
            
            // auto renderers = object->GetComponentsInChildren<RenderingComponent>();
            // for (const auto& comp : renderers | std::views::values)
            // {
            //     comp->Render();
            // }
        }
    }

    void scene::render_ui() const
    {
        for (const auto& object : objects_)
        {
            const auto renderers = object->get_components(component_family::ui);
            for (const auto& comp : renderers | std::views::values)
            {
                ImGui_ImplOpenGL3_NewFrame();
                ImGui_ImplSDL2_NewFrame();
                ImGui::NewFrame();
            
                const auto render_comp = static_cast<ui_component*>(comp);
                render_comp->render_ui();
                
                ImGui::Render();
                ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            }
        }
    }
}
