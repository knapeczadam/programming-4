#pragma once

// Project includes
#include "text_component.h"
#include "core/i_observer.h"

namespace dae
{
    class score_text_component final : public text_component, public i_observer
    {
    public:
        score_text_component()           = default;
        ~score_text_component() override = default;

        score_text_component(score_text_component const &other)            = delete;
        score_text_component(score_text_component &&other)                 = delete;
        score_text_component &operator=(score_text_component const &other) = delete;
        score_text_component &operator=(score_text_component &&other)      = delete;

        void notify(std::string const &event, subject *subject_ptr) override;
    };
}
