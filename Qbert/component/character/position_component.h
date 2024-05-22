#pragma once

// Project includes
#include "minigin/component/family/custom_component.h"
#include "minigin/core/i_observer.h"

// GLM includes
#include <glm/glm.hpp>

namespace qbert
{
    // Forward declarations
    class direction_component;
    
    class position_component : public mngn::custom_component, public mngn::subject
    {
    public:
        position_component() = default;
        position_component(int row_idx, int col_idx);
        ~position_component() override = default;

        position_component(position_component const &other)            = delete;
        position_component(position_component &&other)                 = delete;
        position_component &operator=(position_component const &other) = delete;
        position_component &operator=(position_component &&other)      = delete;
        
        [[nodiscard]] auto row() const -> int { return row_idx_; }
        [[nodiscard]] auto col() const -> int { return col_idx_; }

        void awake() override;
        void on_enable() override;
        void on_disable() override;

        void update_position();
        void reset(int row_idx = 0, int col_idx = 0);
        void move_to_previous();
        
    protected:
        direction_component *direction_comp_ptr_ = nullptr;
        int row_idx_ = 0;
        int col_idx_ = 0;
        int const original_row_idx_ = 0;
        int const original_col_idx_ = 0;
        glm::vec2 original_position_ = {};
        
    };
}
