#include "FPSComponent.h"

// Project includes
#include "GameTime.h"

// Standard includes
#include <utility>

namespace dae
{
    void fps_component::update()
    {
        text_component::update();

        // TODO: calculate fps on average
        // TODO: use stringstream
        std::string fps = std::to_string(1.0f / game_time::get_instance().delta_time_);
        fps = fps.substr(0, fps.find('.') + 2);
        fps += " fps";
        
        set_text(fps);

        /*
         * delay = getDeltaTime();
         * count++;
         * if (delay >= maxDelay)
         * {
         * setText(format("FPS: %d", count / delay));
         * delay = 0;
         * count = 0;
         * }
         */
    }
}
