#pragma once

// Project includes
#include "minigin/component/family/custom_component.h"
#include "minigin/core/i_observer.h"

// GLM includes
#include <glm/glm.hpp>



namespace qbert
{
    class position_idx_component final : public mngn::custom_component, public mngn::subject
    {
    public:
        position_idx_component()           = default;
        position_idx_component(int row_idx, int col_idx);
        ~position_idx_component() override = default;

        position_idx_component(position_idx_component const &other)            = delete;
        position_idx_component(position_idx_component &&other)                 = delete;
        position_idx_component &operator=(position_idx_component const &other) = delete;
        position_idx_component &operator=(position_idx_component &&other)      = delete;

        void set_position_idx(int row_dir, int col_dir);
        [[nodiscard]] auto get_row_idx() const -> int { return row_idx_; }
        [[nodiscard]] auto get_col_idx() const -> int { return col_idx_; }

        void reset_position_idx() noexcept { row_idx_ = 0; col_idx_ = 0; }

    private:
        int row_idx_ = 0;
        int col_idx_ = 0;
    };
}
