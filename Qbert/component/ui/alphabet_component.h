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
    class alphabet_component final : public mngn::custom_component
    {
    public:
        alphabet_component()           = default;
        explicit alphabet_component(std::string text, int sprite_id, int texture_id, int space_sprite_id, int space_texture_id);
        ~alphabet_component() override = default;

        alphabet_component(alphabet_component const &other)            = delete;
        alphabet_component(alphabet_component &&other)                 = delete;
        alphabet_component &operator=(alphabet_component const &other) = delete;
        alphabet_component &operator=(alphabet_component &&other)      = delete;

        void start() override;

    private:
        void set_text();

    private:
        std::string text_;
        int sprite_id_;
        int texture_id_;
        int space_sprite_id_;
        int space_texture_id_;
        mngn::multisprite_ui_component *multisprite_ui_comp_ptr_ = nullptr;
    };
}
