#pragma once

namespace dae
{
    struct Timer
    {
        static float deltaTime;
        
        static const float fixedTimeStep;
        static const float msPerFrame;
    };
}
