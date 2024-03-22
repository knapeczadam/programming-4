#pragma once

// Project includes
#include "Singleton.h"

namespace dae
{
    class GameTime final : public Singleton<GameTime>
    {
    public:
        float deltaTime = 0.0f;
        
        const float fixedTimeStep = 0.02f;
        const float msPerFrame = 16.666666666666668f;
    private:
        friend class Singleton<GameTime>;
        GameTime() = default;
    };
}
