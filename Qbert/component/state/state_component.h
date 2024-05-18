#pragma once

// Project includes
#include "state/state.h"
#include "minigin/component/family/custom_component.h"

// Standard includes
#include <concepts>
#include <memory>

namespace qbert
{
    // Concepts
    template <class T>
    concept child_state = std::derived_from<T, state> and not std::same_as<T, state>;
    
    class state_component : public mngn::custom_component
    {
    public:
        state_component();
        ~state_component() override = default;
        
        state_component(state_component const &other)            = delete;
        state_component(state_component &&other)                 = delete;
        state_component &operator=(state_component const &other) = delete;
        state_component &operator=(state_component &&other)      = delete;

        void update() override;

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

    private:
        std::unique_ptr<qbert::state> state_;
    };
}
