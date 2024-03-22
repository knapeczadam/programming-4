#include "FPSComponent.h"

// Project includes
#include "GameTime.h"

// Standard includes
#include <utility>

namespace dae
{
    void FPSComponent::Update()
    {
        TextComponent::Update();

        // TODO: calculate fps on average
        // TODO: use stringstream
        std::string fps = std::to_string(1.0f / GameTime::GetInstance().deltaTime);
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
