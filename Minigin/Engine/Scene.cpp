#include "Scene.h"

// Project includes
#include "BaseComponent.h"
#include "RenderingComponent.h"
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

    Scene::Scene(std::string name) : m_name(std::move(name))
    {
    }

    GameObject* Scene::AddEmptyObject()
    {
        m_objects.emplace_back(std::make_unique<GameObject>());
        return m_objects.back().get();
    }

    void Scene::RemoveObject(GameObject* object)
    {
        std::erase_if(m_objects, [object](const auto& obj)
        {
            return obj.get() == object;
        });
    }

    void Scene::RemoveAll()
    {
        m_objects.clear();
    }

    int Scene::GetObjectCount() const
    {
        return static_cast<int>(m_objects.size());
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
            const auto renderers = object->GetComponentsInChildren(ComponentFamily::Rendering);
            for (const auto& comp : renderers | std::views::values)
            {
                static_cast<RenderingComponent*>(comp)->Render();
            }
            
            // auto renderers = object->GetComponentsInChildren<RenderingComponent>();
            // for (const auto& comp : renderers | std::views::values)
            // {
            //     comp->Render();
            // }
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
