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

    auto scene::add_game_object(std::string const &name) -> game_object *
    {
        objects_.emplace_back(std::make_unique<game_object>(name));
        return objects_.back().get();
    }

    void scene::remove_game_object(game_object *object_ptr)
    {
        std::erase_if(objects_, [object_ptr](auto const &object)
        {
            return object.get() == object_ptr;
        });
    }

    void scene::remove_all()
    {
        objects_.clear();
    }

    auto scene::game_object_count() const -> int
    {
        return static_cast<int>(objects_.size());
    }

    auto scene::find_game_object(std::string const &name) const -> game_object *
    {
        auto const it = std::ranges::find_if(objects_, [&name](auto const &object)
        {
            return object->name() == name;
        });

        return it != objects_.end() ? it->get() : nullptr;
    }

    void scene::awake()
    {
        std::ranges::for_each(objects_, [](auto const &object) { object->awake(); });
    }

    void scene::fixed_update()
    {
        std::ranges::for_each(objects_, [](auto const &object) { object->fixed_update(); });
    }

    void scene::update()
    {
        std::ranges::for_each(objects_, [](auto const &object) { object->update(); });
    }

    void scene::late_update()
    {
        std::ranges::for_each(objects_, [this](auto const &object)
        {
            object->is_alive() ? object->late_update() : remove_game_object(object.get());
        });
        
    }

    void scene::render() const
    {
        for (auto const &object : objects_)
        {
            // TODO: measure performance!
            // auto const renderers = object->get_components_in_children(component_family::rendering);
            // for (auto const &comp : renderers | std::views::values)
            // {
            //     static_cast<rendering_component*>(comp)->render();
            // }
            std::ranges::for_each(object->components(component_family::rendering) | std::views::values, [](auto const &comp)
            {
                static_cast<rendering_component*>(comp)->render();
            });
            
            
            // auto renderers = object->GetComponentsInChildren<RenderingComponent>();
            // for (auto const &comp : renderers | std::views::values)
            // {
            //     comp->Render();
            // }
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
            
                auto const render_comp = static_cast<ui_component*>(comp);
                render_comp->render_ui();
                
                ImGui::Render();
                ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            }
        }
    }
}
