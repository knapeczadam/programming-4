#pragma once

// Project includes
#include "IInputImpl.h"

namespace dae
{
    class SDLInputImpl : public IInputImpl
    {
    public:
        auto DoProcessInput(std::vector<GameInputCommand> commands) -> bool override;
    };
}
