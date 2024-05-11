#include "fps_component.h"

// Project includes
#include "minigin/core/game_time.h"

// Standard includes
#include <sstream>

namespace qbert
{
    void fps_component::update()
    {
        text_ui_component::update();

        update_timer_ += mngn::game_time::get_instance().delta_time;
        ++frame_count_;
        if (update_timer_ >= update_interval_)
        {
            std::stringstream ss;
            ss << "FPS: ";
            ss << static_cast<float>(frame_count_) / update_timer_;
            set_text(ss.str());
            frame_count_    = 0;
            update_timer_ = 0.0f;
        }
    }
}
