#include "Scene.h"

// Project includes
#include "BaseComponent.h"
#include "RenderComponent.h"
#include "UIComponent.h"

// Standard includes
#include <algorithm>
#include <iostream>
#include <ranges>

// ImGui includes
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_sdl2.h"

namespace dae
{
    unsigned int Scene::m_idCounter = 0;

    Scene::Scene(const std::string& name) : m_name(name)
    {
    }

    Scene::~Scene() = default;

    void Scene::Add(std::shared_ptr<GameObject> object)
    {
        m_objects.emplace_back(std::move(object));
    }

    void Scene::Remove(std::shared_ptr<GameObject> object)
    {
        std::erase(m_objects, object);
    }

    void Scene::RemoveAll()
    {
        m_objects.clear();
    }

    void Scene::Update()
    {
        for (auto& object : m_objects)
        {
            object->Update();
        }
    }

    void Scene::Render() const
    {
        for (const auto& object : m_objects)
        {
            // TODO: measure performance!
            // const auto renderers = object->GetComponents(ComponentFamily::Render);
            // for (const auto& value : renderers | std::views::values)
            // {
            //     static_cast<RenderComponent*>(value)->Render();
            // }
            
            // if (not object->HasComponent(ComponentFamily::Render)) continue;
            // for (auto [compType, comp] : object->GetComponents<RenderComponent>())
            // {
            //     comp->Render();
            // }

            // const auto renderers = object->GetComponentsInChildren(ComponentFamily::Render);
            // for (const auto& comp : renderers | std::views::values)
            // {
            //     static_cast<RenderComponent*>(comp)->Render();
            // }
            
            auto renderers = object->GetComponentsInChildren<RenderComponent>();
            for (const auto& comp : renderers | std::views::values)
            {
                comp->Render();
            }
        }
    }

    void Scene::RenderUI() const
    {
        for (const auto& object : m_objects)
        {
            const auto renderers = object->GetComponents(ComponentFamily::UI);
            for (const auto& comp : renderers | std::views::values)
            {
                ImGui_ImplOpenGL3_NewFrame();
                ImGui_ImplSDL2_NewFrame();
                ImGui::NewFrame();
            
                const auto renderComp = static_cast<UIComponent*>(comp);
                renderComp->RenderUI();
                
                ImGui::Render();
                ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            }
        }
    }
}
