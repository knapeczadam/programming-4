#pragma once

// Project includes
#include "minigin/component/family/custom_component.h"

namespace qbert
{
    class disk_component final : public mngn::custom_component
    {
    public:
        disk_component()           = default;
        disk_component(int row_idx, int col_idx);
        ~disk_component() override = default;

        disk_component(disk_component const &other)            = delete;
        disk_component(disk_component &&other)                 = delete;
        disk_component &operator=(disk_component const &other) = delete;
        disk_component &operator=(disk_component &&other)      = delete;

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
