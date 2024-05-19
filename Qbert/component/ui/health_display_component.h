#pragma once

// Project includes
#include "minigin/component/family/custom_component.h"
#include "minigin/core/i_observer.h"

// Forward declarations
namespace mngn
{
    class multisprite_ui_component;
}

namespace qbert
{
    class health_display_component final : public mngn::custom_component, public mngn::i_observer
    {
    public:
        health_display_component()           = default;
        ~health_display_component() override = default;

        health_display_component(health_display_component const &other)            = delete;
        health_display_component(health_display_component &&other)                 = delete;
        health_display_component &operator=(health_display_component const &other) = delete;
        health_display_component &operator=(health_display_component &&other)      = delete;

        void start() override;
        void notify(std::string const &event, mngn::subject *subject_ptr) override;

    private:
        mngn::multisprite_ui_component *multisprite_ui_comp_ptr_ = nullptr;
    };
}
