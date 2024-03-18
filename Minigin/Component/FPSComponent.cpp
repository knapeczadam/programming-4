#include "FPSComponent.h"

#include <utility>

#include "Timer.h"

// Project includes

namespace dae
{
    FPSComponent::FPSComponent(std::shared_ptr<Font> font)
        : TextComponent("FPS: ", std::move(font))
    {
    }

    void FPSComponent::Update()
    {
        TextComponent::Update();

        // TODO: calculate fps on average 
        std::string fps = std::to_string(1.0f / Timer::GetInstance().deltaTime);
        fps = fps.substr(0, fps.find('.') + 2);
        fps += " fps";
        
        SetText(fps);

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
