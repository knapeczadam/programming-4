﻿#include "TextureComponent.h"

// Project includes
#include "GameObject.h"
#include "Renderer.h"
#include "ResourceManager.h"

namespace dae
{
    texture_component::texture_component(const std::string& filename)
        : m_texture_(resource_manager::get_instance().load_texture(filename))
    {
    }

    void texture_component::render() const
    {
        if (m_texture_)
        {
            const auto& pos = get_owner()->get_world_position();
            renderer::get_instance().render_texture(*m_texture_, pos.x, pos.y);
        }
    }

    void texture_component::set_texture(const std::string& filename)
    {
        m_texture_ = resource_manager::get_instance().load_texture(filename);
    }
}
