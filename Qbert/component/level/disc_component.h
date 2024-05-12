#pragma once

// Project includes
#include "minigin/component/family/custom_component.h"

namespace qbert
{
    class disc_component final : public mngn::custom_component
    {
    public:
        disc_component()           = default;
        disc_component(int row_id, int col_id);
        ~disc_component() override = default;

        disc_component(disc_component const &other)            = delete;
        disc_component(disc_component &&other)                 = delete;
        disc_component &operator=(disc_component const &other) = delete;
        disc_component &operator=(disc_component &&other)      = delete;

        void awake() override;

        [[nodiscard]] int get_row_id() const { return row_id_; }
        [[nodiscard]] int get_col_id() const { return col_id_; }

    private:
        int row_id_ = 0;
        int col_id_ = 0;
    };
}
