#include "FPSComponent.h"

#include <utility>

#include "Time.h"

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

        std::string fps = std::to_string(1.0f / Time::deltaTime);
        fps = fps.substr(0, fps.find('.') + 2);
        fps += " fps";
        
        SetText(fps);
    }
}
