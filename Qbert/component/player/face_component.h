#pragma once

// Project includes
#include "minigin/component/family/custom_component.h"

namespace mngn
{
    class sprite_component;
}

namespace qbert
{
    // Forward declarations
    class direction_component;
    
    class face_component final : public mngn::custom_component
    {
    public:
        face_component()           = default;
        ~face_component() override = default;

        face_component(const face_component& other)            = delete;
        face_component(face_component&& other)                 = delete;
        face_component& operator=(const face_component& other) = delete;
        face_component& operator=(face_component&& other)      = delete;

        void awake() override;
        void on_enable() override;
        void set_sprite_orientation(int left_dir_frame, int right_dir_frame, int up_dir_frame, int down_dir_frame, int diagonal_dir_frame = 0);

    private:
        mngn::sprite_component *sprite_comp_ptr_ = nullptr;
        direction_component *direction_comp_ptr_ = nullptr;
    };
}
