#pragma once

// Forward declarations
namespace mngn
{
    class game_object;
}

// Project includes
#include "minigin/component/family/custom_component.h"

namespace qbert
{
    class swear_component final : public mngn::custom_component
    {
    public:
        swear_component()           = default;
        ~swear_component() override = default;

        swear_component(swear_component const &other)            = delete;
        swear_component(swear_component &&other)                 = delete;
        swear_component &operator=(swear_component const &other) = delete;
        swear_component &operator=(swear_component &&other)      = delete;

        void awake() override;
        void update() override;
        void swear();

    private:
        mngn::game_object *swearing_go_ptr_ = nullptr;
        float             swear_time_       = 2.0f;
        float             accu_time_        = 0.0f;
        bool              is_swearing_      = false;
    };
}
