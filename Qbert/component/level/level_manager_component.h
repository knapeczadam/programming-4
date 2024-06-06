#pragma once

// Project includes
#include "minigin/component/family/custom_component.h"
#include "minigin/core/i_observer.h"

// Standard includes
#include <vector>

namespace qbert
{
    // Forward declaration
    class disk_component;
    
    class level_manager_component final : public mngn::custom_component, public mngn::subject,  public mngn::i_observer
    {
    public:
        level_manager_component()           = default;
        ~level_manager_component() override = default;

        level_manager_component(level_manager_component const &other)            = delete;
        level_manager_component(level_manager_component &&other)                 = delete;
        level_manager_component &operator=(level_manager_component const &other) = delete;
        level_manager_component &operator=(level_manager_component &&other)      = delete;

        void awake() override;
        void update() override;
        void on_disable() override;
        
        void notify(std::string const &event, mngn::subject *subject_ptr) override;

    private:
        std::vector<disk_component*> disks_;
        float accu_time_        = 0.0f;
        float const extra_time_ = 5.29f;
        bool extra_time_active_ = false;
    };
}
