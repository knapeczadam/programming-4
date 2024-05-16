#pragma once

// Project includes
#include "minigin/component/family/custom_component.h"
#include "minigin/core/i_observer.h"

namespace qbert
{
    // Forward declarations
    class direction_component;
    
    class position_component : public mngn::custom_component, public mngn::subject
    {
    public:
        position_component()           = default;
        position_component(int row_idx, int col_idx) : row_idx_{row_idx}, col_idx_{col_idx} {}
        ~position_component() override = default;

        position_component(position_component const &other)            = delete;
        position_component(position_component &&other)                 = delete;
        position_component &operator=(position_component const &other) = delete;
        position_component &operator=(position_component &&other)      = delete;
        
        [[nodiscard]] auto row() const -> int { return row_idx_; }
        [[nodiscard]] auto col() const -> int { return col_idx_; }
        void set_col(int col) { col_idx_ = col; }

        void awake() override;

        virtual void update_position();
        virtual void reset();
        
    protected:
        direction_component *direction_comp_ptr_ = nullptr;
        int row_idx_ = 0;
        int col_idx_ = 0;
    };
}
