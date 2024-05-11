#pragma once

// Project includes
#include "minigin/component/family/custom_component.h"
#include "minigin/core/i_observer.h"

// GLM includes
#include <glm/glm.hpp>



namespace qbert
{
    class position_component final : public mngn::custom_component, public mngn::subject, public mngn::i_observer
    {
    public:
        position_component()           = default;
        ~position_component() override = default;

        position_component(position_component const &other)            = delete;
        position_component(position_component &&other)                 = delete;
        position_component &operator=(position_component const &other) = delete;
        position_component &operator=(position_component &&other)      = delete;

        void set_position(int row, int col);
        [[nodiscard]] auto get_row() const -> int { return curr_row_; }
        [[nodiscard]] auto get_col() const -> int { return curr_col_; }

        void notify(std::string const &event, subject *subject_ptr) override;

    private:
        int curr_row_ = 0;
        int curr_col_ = 0;
    };
}
