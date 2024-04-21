#include "texture_component.h"

// Project includes
#include "core/game_object.h"
#include "engine/renderer.h"
#include "engine/resource_manager.h"

namespace dae
{
    texture_component::texture_component(std::string const &filename)
        : m_texture_ptr_{resource_manager::get_instance().load_texture(filename)}
    {
    }

    void texture_component::render() const
    {
        if (m_texture_ptr_)
        {
            auto const &pos = get_owner()->get_world_position();
            renderer::get_instance().render_texture(*m_texture_ptr_, pos.x, pos.y);
        }
    }

    void texture_component::set_texture(std::string const &filename)
    {
        m_texture_ptr_ = resource_manager::get_instance().load_texture(filename);
    }
}
