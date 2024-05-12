#include "game_object_commands.h"

// Project includes
#include "component/player/jump_component.h"
#include "minigin/core/game_object.h"

namespace qbert
{
    void jump_command::execute()
    {
        if (not is_jumping_)
        {
            get_game_object()->get_component<jump_component>()->jump(row_, col_);
            is_jumping_ = true;
        }
    }

    void jump_command::notify(std::string const &event, [[maybe_unused]] mngn::subject *subject_ptr)
    {
        if (event == "jump_started")
        {
            is_jumping_ = true;
        }
        if (event == "jump_finished")
        {
            is_jumping_ = false;
        }
    }

    void reset_move_command::execute()
    {
    }
}
