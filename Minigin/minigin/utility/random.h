#pragma once

// Standard includes
#include <random>

namespace mngn
{
    inline auto random_int(int min, int max) -> int
    {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dis(min, max);
        return dis(gen);
    }

    inline auto random_float(float min, float max) -> float
    {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dis(min, max);
        return dis(gen);
    }
}
