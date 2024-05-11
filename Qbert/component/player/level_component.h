#pragma once

// Project includes
#include "minigin/component/family/custom_component.h"
#include "minigin/core/i_observer.h"

namespace qbert
{
    class level_component final : public mngn::custom_component, public mngn::subject
    {
    public:
        level_component()           = default;
        ~level_component() override = default;

        level_component(level_component const &other)            = delete;
        level_component(level_component &&other)                 = delete;
        level_component &operator=(level_component const &other) = delete;
        level_component &operator=(level_component &&other)      = delete;

        void awake() override;
        
        [[nodiscard]] auto get_level() const -> int { return level_; }
        void set_level(int level);
        void increase_level();
        

    private:
        int level_ = 1;
    };
}
