#include "disc_component.h"

// Project includes
#include "minigin/core/game_object.h"

// GLM includes
#include <glm/glm.hpp>

namespace qbert
{
    disc_component::disc_component(int row_idx, int col_idx)
        : row_idx_{row_idx}
        , col_idx_{col_idx}
    {
    }

    void disc_component::awake()
    {
        glm::vec2 origin{208, 96};
        int offset_x = -32;
        int offset_y = 48;

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
