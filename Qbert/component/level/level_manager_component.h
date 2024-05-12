﻿#pragma once

// Project includes
#include "minigin/component/family/custom_component.h"
#include "minigin/core/i_observer.h"

// Standard includes
#include <vector>

namespace qbert
{
    // Forward declaration
    class disc_component;
    
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
        void notify(std::string const &event, mngn::subject *subject_ptr) override;

    private:
        std::vector<disc_component*> discs_;
    };
}