#pragma once

// Project includes
#include "minigin/component/family/custom_component.h"

namespace qbert
{
    class direction_component final : public mngn::custom_component
    {
    public:
        direction_component() = default;
        ~direction_component() override = default;

        direction_component(direction_component const &other)            = delete;
        direction_component(direction_component &&other)                 = delete;
        direction_component &operator=(direction_component const &other) = delete;
        direction_component &operator=(direction_component &&other)      = delete;

        void on_disable() override
        {
            reset();
        }

        [[nodiscard]] auto row() const -> int { return row_; }
        [[nodiscard]] auto col() const -> int { return col_; }
        void set_direction(int row, int col) { row_ = row; col_ = col; }
        void reset() { row_ = 0; col_ = 0; }


    private:
        int row_ = 0;
        int col_ = 0;
    };
}
