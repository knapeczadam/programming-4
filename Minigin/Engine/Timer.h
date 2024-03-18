#pragma once

// Project includes
#include "Singleton.h"

namespace dae
{
    class Timer final : public Singleton<Timer>
    {
    public:
        float deltaTime = 0.0f;
        
        const float fixedTimeStep = 0.02f;
        const float msPerFrame = 16.666666666666668f;
    private:
        friend class Singleton<Timer>;
        Timer() = default;
    };
}
