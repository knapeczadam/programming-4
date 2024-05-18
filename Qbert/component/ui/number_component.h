#pragma once

// Project includes
#include "minigin/component/family/custom_component.h"

// Forward declarations
namespace mngn
{
    class sprite;
    class multisprite_ui_component;
}

namespace qbert
{
    class number_component final : public mngn::custom_component
    {
    public:
        number_component()           = default;
        explicit number_component(int number, int sprite_id, int texture_id);
        ~number_component() override = default;

        number_component(number_component const &other)            = delete;
        number_component(number_component &&other)                 = delete;
        number_component &operator=(number_component const &other) = delete;
        number_component &operator=(number_component &&other)      = delete;

        void awake() override;
        void start() override;

        void set_number(int number);

    private:
        int number_ = 0;
        int sprite_id_ = 0;
        int texture_id_ = 0;
        mngn::multisprite_ui_component *multisprite_ui_comp_ptr_ = nullptr;
    };
}
