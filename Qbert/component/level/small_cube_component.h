#pragma once

// Project includes
#include "minigin/component/family/custom_component.h"

// Forward declaration
namespace mngn
{
    class sprite;
    class sprite_ui_component;
}

namespace qbert
{
    class small_cube_component final : public mngn::custom_component
    {
    public:
        small_cube_component()           = default;
        explicit small_cube_component(int sprite_id, int texture_id);

        small_cube_component(small_cube_component const &other)            = delete;
        small_cube_component(small_cube_component &&other)                 = delete;
        small_cube_component &operator=(small_cube_component const &other) = delete;
        small_cube_component &operator=(small_cube_component &&other)      = delete;

        void start() override;
        void on_enable() override;
        void on_disable() override;

        void enable_animation();
        void disable_animation();

    private:
        mngn::sprite_ui_component *sprite_ui_comp_ptr_  = nullptr;
        mngn::sprite              *original_sprite_ptr_ = nullptr;
        mngn::sprite              *animated_sprite_ptr_ = nullptr;
    };
}
