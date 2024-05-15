#pragma once

// Project includes
#include "state/i_state.h"

// Standard includes
#include <concepts>
#include <memory>

namespace qbert
{
    // Concepts
    template <class T>
    concept child_state = std::derived_from<T, i_state> and not std::same_as<T, i_state>;
    
    class i_state_component
    {
    public:
        i_state_component() = default;
        virtual ~i_state_component() = default;

        i_state_component(i_state_component const &other)            = delete;
        i_state_component(i_state_component &&other)                 = delete;
        i_state_component &operator=(i_state_component const &other) = delete;
        i_state_component &operator=(i_state_component &&other)      = delete;

        template <class T, typename... Args> requires child_state<T>
        void change_state(Args &&...args)
        {
            state_->on_exit();
            state_ = std::make_unique<T>(std::forward<Args>(args)...);
            state_->on_enter();
        }
        
        template <class T> requires child_state<T>
        [[nodiscard]] auto state() const -> T *
        {
            return dynamic_cast<T*>(state_.get());
        }

        template <class T> requires child_state<T>
        [[nodiscard]] auto is_state() const -> bool
        {
            return dynamic_cast<T*>(state_.get()) != nullptr;
        }

    protected:
        std::unique_ptr<i_state> state_;
    };
}
