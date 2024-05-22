#pragma once

// Project includes
#include "minigin/component/family/custom_component.h"

// Forward declarations
namespace mngn
{
    class sprite;
    class multisprite_ui_component;
}

// Standard includes
#include <string>

namespace qbert
{
    struct alphabet_config_info
    {
        std::string text;
        int sprite_id;
        int texture_id;
        int space_sprite_id;
        int space_texture_id;
        int exclamation_sprite_id;
        int exclamation_texture_id;
        int exclamation_frame;
        int dot_sprite_id;
        int dot_texture_id;
        int dot_frame;
        int at_sprite_id;
        int at_texture_id;
        int at_frame;
    };
    class alphabet_component final : public mngn::custom_component
    {
    public:
        alphabet_component()           = default;
        explicit alphabet_component(alphabet_config_info config_info);
        ~alphabet_component() override = default;

        alphabet_component(alphabet_component const &other)            = delete;
        alphabet_component(alphabet_component &&other)                 = delete;
        alphabet_component &operator=(alphabet_component const &other) = delete;
        alphabet_component &operator=(alphabet_component &&other)      = delete;

        void awake() override;
        void on_enable() override;
        void start() override;

    private:
        void set_text();

    private:
        alphabet_config_info config_info_;
        mngn::multisprite_ui_component *multisprite_ui_comp_ptr_ = nullptr;
    };
}
