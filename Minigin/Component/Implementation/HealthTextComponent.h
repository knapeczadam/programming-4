#pragma once
#include "IObserver.h"
#include "TextComponent.h"

namespace dae
{
    class health_text_component final : public text_component, public i_observer
    {
    public:
        health_text_component() = default;
        ~health_text_component() override = default;

        health_text_component(const health_text_component& other)            = delete;
        health_text_component(health_text_component&& other)                 = delete;
        health_text_component& operator=(const health_text_component& other) = delete;
        health_text_component& operator=(health_text_component&& other)      = delete;
        
        void notify(const std::string& event, subject* subject) override;
    };
}
