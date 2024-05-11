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
    class score_display_component final : public mngn::custom_component, public mngn::i_observer
    {
    public:
        score_display_component()           = default;
        ~score_display_component() override = default;

        score_display_component(score_display_component const &other)            = delete;
        score_display_component(score_display_component &&other)                 = delete;
        score_display_component &operator=(score_display_component const &other) = delete;
        score_display_component &operator=(score_display_component &&other)      = delete;

        void awake() override;
        void notify(std::string const &event, mngn::subject *subject_ptr) override;

    private:
        mngn::multisprite_ui_component *multisprite_ui_component_ptr_ = nullptr;
        
    };
}
