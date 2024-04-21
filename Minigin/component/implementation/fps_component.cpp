#include "fps_component.h"

// Project includes
#include "engine/game_time.h"

// Standard includes
#include <utility>

namespace dae
{
    void fps_component::update()
    {
        text_component::update();

        // TODO: calculate fps on average
        // TODO: use stringstream
        std::string fps = std::to_string(1.0f / game_time::get_instance().delta_time);
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
        
        // void aze::FPS::Update()
        //    {
        //        m_TimeElapsed += GameTime::GetInstance().GetElapsed();
        //        ++m_NrFramesPassed;
        //        if (m_TimeElapsed >= m_UpdateInterval)
        //        {
        //            std::stringstream s;
        //            s << /*static_cast<int>*/(m_NrFramesPassed / m_TimeElapsed);
        //            s << " FPS";
        //            m_pTextRenderer->SetText(s.str());
        //            m_NrFramesPassed = 0;
        //            m_TimeElapsed = 0.f;
        //        }
        //    }

    }
}
