#pragma once

namespace qbert
{
    // Forward declarations
    class player_state_component;

    template <class T, typename... Args> requires child_state<T>
    void player_state_component::change_state(Args &&... args)
    {
        player_state_->on_exit();
        player_state_ = std::make_unique<T>(std::forward<Args>(args)...);
        player_state_->on_enter();
    }

    template <class T> requires child_state<T>
    auto player_state_component::state() const -> T *
    {
        return dynamic_cast<T*>(player_state_.get());
    }

    template <class T> requires child_state<T>
    auto player_state_component::is_state() const -> bool
    {
        return dynamic_cast<T*>(player_state_.get()) != nullptr;
    }
}
