#pragma once

// Project includes
#include "minigin/component/family/custom_component.h"
#include "component/state/i_state_component.h"

// Forward declarations
namespace mngn
{
    class scene;
}

namespace qbert
{
    class game_state_component final : public mngn::custom_component, public i_state_component
    {
    public:
        game_state_component() = default;
        game_state_component(mngn::scene *scene_ptr);
        ~game_state_component() override = default;

        game_state_component(game_state_component const &other)            = delete;
        game_state_component(game_state_component &&other)                 = delete;
        game_state_component &operator=(game_state_component const &other) = delete;
        game_state_component &operator=(game_state_component &&other)      = delete;

        void awake() override;
        void update() override;

        [[nodiscard]] auto scene() const -> mngn::scene * { return scene_ptr_; }

    private:
        mngn::scene *scene_ptr_ = nullptr;
    };
}
