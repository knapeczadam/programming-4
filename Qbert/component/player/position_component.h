#pragma once

// Project includes
#include "minigin/component/family/custom_component.h"
#include "minigin/core/i_observer.h"

// GLM includes
#include <glm/glm.hpp>



namespace qbert
{
    class position_component final : public mngn::custom_component, public mngn::subject
    {
    public:
        position_component()           = default;
        ~position_component() override = default;

        position_component(position_component const &other)            = delete;
        position_component(position_component &&other)                 = delete;
        position_component &operator=(position_component const &other) = delete;
        position_component &operator=(position_component &&other)      = delete;

        void set_position(int row_dir, int col_dir);
        [[nodiscard]] auto get_row_position() const -> int { return row_pos_; }
        [[nodiscard]] auto get_col_position() const -> int { return col_pos_; }

    private:
        int row_pos_ = 0;
        int col_pos_ = 0;
    };
}
