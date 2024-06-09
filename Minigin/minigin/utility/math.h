#pragma once

// GLM includes
#include <glm/glm.hpp>

namespace mngn
{
    [[nodiscard]] inline auto bezier_curve(glm::vec2 const &p0, glm::vec2 const &p1, glm::vec2 const &p2, glm::vec2 const &p3, float t) -> glm::vec2
    {
        auto const p01  = glm::mix(p0,  p1,  t);
        auto const p12  = glm::mix(p1,  p2,  t);
        auto const p23  = glm::mix(p2,  p3,  t);
        auto const p012 = glm::mix(p01, p12, t);
        auto const p123 = glm::mix(p12, p23, t);
        return glm::mix(p012, p123, t);
    }
}
