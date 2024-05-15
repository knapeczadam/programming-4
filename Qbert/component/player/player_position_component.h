#pragma once

// Project includes
#include "minigin/component/family/custom_component.h"
#include "minigin/core/i_observer.h"

namespace qbert
{
    // Forward declarations
    class direction_component;
    
    class player_position_component final : public mngn::custom_component, public mngn::subject
    {
    public:
        player_position_component()           = default;
        player_position_component(int row_idx, int col_idx);
        ~player_position_component() override = default;

        player_position_component(player_position_component const &other)            = delete;
        player_position_component(player_position_component &&other)                 = delete;
        player_position_component &operator=(player_position_component const &other) = delete;
        player_position_component &operator=(player_position_component &&other)      = delete;

        void awake() override;
        void update_position();
        [[nodiscard]] auto row() const -> int { return row_idx_; }
        [[nodiscard]] auto col() const -> int { return col_idx_; }

        void reset() { row_idx_ = 0; col_idx_ = 0; }

    private:
        direction_component *direction_comp_ptr_ = nullptr;
        int row_idx_ = 0;
        int col_idx_ = 0;
    };
}
