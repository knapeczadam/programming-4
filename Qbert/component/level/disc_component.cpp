#include "disc_component.h"

// Project includes
#include "minigin/core/game_object.h"

// GLM includes
#include <glm/glm.hpp>

namespace qbert
{
    disc_component::disc_component(int row_id, int col_id)
        : row_id_{row_id}
        , col_id_{col_id}
    {
    }

    void disc_component::awake()
    {
        glm::vec2 origin{208, 96};
        int offset_x = -32;
        int offset_y = 48;

        glm::vec2 pos = origin + glm::vec2{row_id_ * offset_x, row_id_ * offset_y};
        if (col_id_ == -1)
        {
            pos += glm::vec2{-20.0f, -28.0f};
        }
        else
        {
           pos += glm::vec2{(col_id_ - 1.0f) * 64.0f + 50.0f, -28.0f}; 
        }
        get_owner()->set_local_position(pos);
    }
}
