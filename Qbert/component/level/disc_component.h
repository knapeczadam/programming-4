#pragma once

// Project includes
#include "minigin/component/family/custom_component.h"

namespace qbert
{
    class disc_component final : public mngn::custom_component
    {
    public:
        disc_component()           = default;
        disc_component(int row_idx, int col_idx);
        ~disc_component() override = default;

        disc_component(disc_component const &other)            = delete;
        disc_component(disc_component &&other)                 = delete;
        disc_component &operator=(disc_component const &other) = delete;
        disc_component &operator=(disc_component &&other)      = delete;

        void awake() override;

        [[nodiscard]] int get_row_idx() const { return row_idx_; }
        [[nodiscard]] int get_col_idx() const { return col_idx_; }

    private:
        int row_idx_ = 0;
        int col_idx_ = 0;
    };
}
