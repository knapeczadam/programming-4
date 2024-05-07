#include "texture_component.h"

// Project includes
#include "minigin/core/game_object.h"
#include "minigin/core/renderer.h"
#include "minigin/core/resource_manager.h"
#include "minigin/utility/texture_2d.h"

namespace mngn
{
    texture_component::texture_component(std::string const &filename)
        : m_texture_ptr_{resource_manager::get_instance().load_texture(filename)}
    {
    }
    
    texture_component::texture_component() = default;

    texture_component::~texture_component() = default;

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
