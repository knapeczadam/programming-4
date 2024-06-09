#include "disk_component.h"

// Project includes
#include "minigin/core/game_object.h"

// GLM includes
#include <glm/glm.hpp>

namespace qbert
{
    disk_component::disk_component(int row_idx, int col_idx)
        : row_idx_{row_idx}
        , col_idx_{col_idx}
        , original_row_idx_{row_idx}
        , original_col_idx_{col_idx}
    {
    }

    void disk_component::start()
    {
        init();
    }

    void disk_component::on_disable()
    {
        row_idx_ = original_row_idx_;
        col_idx_ = original_col_idx_;
        init();
    }

    void disk_component::disable()
    {
        row_idx_ = -1;
        col_idx_ = -1;
        owner()->set_active(false);
    }

    void disk_component::init()
    {
        
        glm::vec2 const origin{208, 96};
        int const offset_x = -32;
        int const offset_y = 48;

        glm::vec2 pos = origin + glm::vec2{row_idx_ * offset_x, row_idx_ * offset_y};
        if (col_idx_ == -1)
        {
            pos += glm::vec2{-20.0f, -28.0f};
        }
        else
        {
           pos += glm::vec2{(col_idx_ - 1.0f) * 64.0f + 50.0f, -28.0f}; 
        }
        owner()->set_local_position(pos);
    }
}
