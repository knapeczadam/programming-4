#pragma once

// Project includes
#include "minigin/component/text_ui_component.h"
#include "minigin/core/i_observer.h"

namespace qbert
{
    class health_text_component final : public mngn::text_ui_component, public mngn::i_observer
    {
    public:
        health_text_component()           = default;
        ~health_text_component() override = default;

        health_text_component(health_text_component const &other)            = delete;
        health_text_component(health_text_component &&other)                 = delete;
        health_text_component &operator=(health_text_component const &other) = delete;
        health_text_component &operator=(health_text_component &&other)      = delete;

        void notify(std::string const &event, mngn::subject *subject_ptr) override;
    };
}
