#pragma once

// Project includes
#include "minigin/component/family/custom_component.h"
#include "minigin/core/i_observer.h"

namespace mngn
{
    class sprite_component;
}

namespace qbert
{
    class face_component final : public mngn::custom_component, public mngn::i_observer
    {
    public:
        face_component()           = default;
        ~face_component() override = default;

        face_component(const face_component& other)            = delete;
        face_component(face_component&& other)                 = delete;
        face_component& operator=(const face_component& other) = delete;
        face_component& operator=(face_component&& other)      = delete;

        void awake() override;
        void notify(std::string const &event, mngn::subject *subject_ptr) override;

    private:
        mngn::sprite_component *sprite_comp_ptr_ = nullptr;
    };
}
