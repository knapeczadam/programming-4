#pragma once

// Project includes
#include "minigin/component/family/custom_component.h"
#include "minigin/core/i_observer.h"

// Forward declarations
namespace mngn
{
    class sprite_ui_component;
}

namespace qbert
{
    class round_display_component final : public mngn::custom_component, public mngn::i_observer
    {
    public:
        round_display_component()           = default;
        ~round_display_component() override = default;

        round_display_component(round_display_component const &other)            = delete;
        round_display_component(round_display_component &&other)                 = delete;
        round_display_component &operator=(round_display_component const &other) = delete;
        round_display_component &operator=(round_display_component &&other)      = delete;

        void awake() override;
        void notify(std::string const &event, mngn::subject *subject_ptr) override;

    private:
        mngn::sprite_ui_component *sprite_ui_component_ptr_ = nullptr;
    };
}
