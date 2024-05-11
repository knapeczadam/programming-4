#include "health_component.h"

// Project includes
#include "component/player/position_component.h"

namespace qbert
{
    void health_component::awake()
    {
        notify_observers("health_changed");
    }

    void health_component::notify(std::string const &event, subject *subject_ptr)
    {
        if (event == "position_changed")
        {
            auto position_comp_ptr = dynamic_cast<position_component*>(subject_ptr);
            auto const row = position_comp_ptr->get_row();
            auto const col = position_comp_ptr->get_col();
            if (row < 0 or col < 0 or col > row)
            {
                take_damage(1);
            }
        }
    }

    void health_component::take_damage(int damage)
    {
        if (health_ <= 0)
            return;
        health_ -= damage;
        notify_observers("health_changed");
    }
}
