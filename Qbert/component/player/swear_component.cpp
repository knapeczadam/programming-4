#include "swear_component.h"

// Project includes
#include "minigin/component/rendering/sprite_component.h"
#include "minigin/core/game_object.h"

namespace qbert
{
    void swear_component::awake()
    {
        swearing_go_ptr_ = owner()->find(owner()->name() + "_swearing");
        swearing_go_ptr_->set_active(false);
    }

    void swear_component::swear(bool swear_on)
    {
        if (swear_on)
        {
            swearing_go_ptr_->set_active(true);
        }
        else
        {
            swearing_go_ptr_->set_active(false);
        }
    }
}
