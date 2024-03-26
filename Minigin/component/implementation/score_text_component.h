#pragma once

// Project includes
#include "i_observer.h"
#include "text_component.h"

namespace dae
{
    class score_text_component final : public text_component, public i_observer
    {
    public:
        score_text_component() = default;
        ~score_text_component() override = default;

        score_text_component(const score_text_component& other)            = delete;
        score_text_component(score_text_component&& other)                 = delete;
        score_text_component& operator=(const score_text_component& other) = delete;
        score_text_component& operator=(score_text_component&& other)      = delete;

        void notify(const std::string& event, subject* subject) override;
    };
}
