#pragma once

// Project includes
#include "minigin/core/i_observer.h"
#include "minigin/input/base_command.h"

namespace qbert
{
    class debug_command final : public mngn::base_command, public mngn::subject
    {
    public:
        void execute() override;
        
        [[nodiscard]] auto clone() const -> std::unique_ptr<base_command> override
        {
            return nullptr;
        }
    };
}
