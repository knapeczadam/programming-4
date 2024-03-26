#include "Scene.h"

// Project includes
#include "BaseComponent.h"
#include "GameObject.h"
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

    Scene::~Scene() = default;

    GameObject* Scene::AddGameObject(const std::string& name)
    {
        m_objects.emplace_back(std::make_unique<GameObject>(name));
        return m_objects.back().get();
    }

    void Scene::RemoveGameObject(GameObject* object)
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

    int Scene::GetGameObjectCount() const
    {
        return static_cast<int>(m_objects.size());
    }

    GameObject* Scene::FindGameObject(const std::string& name) const
    {
        const auto it = std::ranges::find_if(m_objects, [&name](const auto& obj)
        {
            return obj->GetName() == name;
        });

        return it != m_objects.end() ? it->get() : nullptr;
    }

    void Scene::Update()
    {
        for (const auto& object : m_objects)
        {
            object->Update();
        }
    }

    void Scene::LateUpdate()
    {
        for (const auto& object : m_objects)
        {
            if (object->IsAlive())
            {
                object->LateUpdate();
            }
            else
            {
                RemoveGameObject(object.get());
            }
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
