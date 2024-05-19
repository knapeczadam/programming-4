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

        void start() override;
        void on_disable() override;
        void disable();

        void init();

        [[nodiscard]] int row() const { return row_idx_; }
        [[nodiscard]] int col() const { return col_idx_; }

    private:
        int row_idx_ = 0;
        int col_idx_ = 0;
        int const original_row_idx_ = 0;
        int const original_col_idx_ = 0;
    };
}
