#pragma once

// Project includes
#include "component/implementation/text_component.h"
#include "core/i_observer.h"

namespace dae
{
    class health_text_component final : public text_component, public i_observer
    {
    public:
        health_text_component()           = default;
        ~health_text_component() override = default;

        health_text_component(health_text_component const &other)            = delete;
        health_text_component(health_text_component &&other)                 = delete;
        health_text_component &operator=(health_text_component const &other) = delete;
        health_text_component &operator=(health_text_component &&other)      = delete;

        void notify(std::string const &event, subject *subject_ptr) override;
    };
}
