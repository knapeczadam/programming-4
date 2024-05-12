#pragma once

// Project includes
#include "minigin/component/family/custom_component.h"

namespace mngn
{
    class sprite_component;
}

namespace qbert
{
    class face_component final : public mngn::custom_component
    {
    public:
        face_component()           = default;
        ~face_component() override = default;

        face_component(const face_component& other)            = delete;
        face_component(face_component&& other)                 = delete;
        face_component& operator=(const face_component& other) = delete;
        face_component& operator=(face_component&& other)      = delete;

        void set_jump_sprite(int row_dir, int col_dir);
        void set_idle_sprite(int row_dir, int col_dir);
        void awake() override;

    private:
        mngn::sprite_component *sprite_comp_ptr_ = nullptr;
    };
}
