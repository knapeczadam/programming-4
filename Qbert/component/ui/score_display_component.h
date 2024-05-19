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
    // Forward declarations
    class number_component;
    
    class score_display_component final : public mngn::custom_component, public mngn::i_observer
    {
    public:
        score_display_component()           = default;
        ~score_display_component() override = default;

        score_display_component(score_display_component const &other)            = delete;
        score_display_component(score_display_component &&other)                 = delete;
        score_display_component &operator=(score_display_component const &other) = delete;
        score_display_component &operator=(score_display_component &&other)      = delete;

        void start() override;
        void notify(std::string const &event, mngn::subject *subject_ptr) override;

    private:
        number_component *number_comp_ptr_ = nullptr;
        
    };
}
