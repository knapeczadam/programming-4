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
    class level_display_component final : public mngn::custom_component, public mngn::i_observer
    {
    public:
        level_display_component()           = default;
        ~level_display_component() override = default;

        level_display_component(level_display_component const &other)            = delete;
        level_display_component(level_display_component &&other)                 = delete;
        level_display_component &operator=(level_display_component const &other) = delete;
        level_display_component &operator=(level_display_component &&other)      = delete;

        void awake() override;
        void on_enable() override;
        void notify(std::string const &event, mngn::subject *subject_ptr) override;

    private:
        mngn::sprite_ui_component *sprite_ui_comp_ptr_ = nullptr;
    };
}
