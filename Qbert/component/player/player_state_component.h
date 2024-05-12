#pragma once

// Project includes
#include "minigin/component/family/custom_component.h"

// Standard includes
#include <memory>

namespace qbert
{
    // Forward declarations
    class player_state;
    
    class player_state_component final : public mngn::custom_component
    {
    public:
        player_state_component();
        ~player_state_component() override;

        player_state_component(player_state_component const &other)            = delete;
        player_state_component(player_state_component &&other)                 = delete;
        player_state_component &operator=(player_state_component const &other) = delete;
        player_state_component &operator=(player_state_component &&other)      = delete;

        void awake() override;
        void update() override;
        void change_state(std::unique_ptr<player_state> new_state);

        template <class T>
        [[nodiscard]] auto get_state() const -> T * { return dynamic_cast<T*>(player_state_.get()); }

        template <class T>
        [[nodiscard]] auto is_state() const -> bool { return dynamic_cast<T*>(player_state_.get()) != nullptr; }

    private:
        std::unique_ptr<player_state> player_state_;
    };
}
