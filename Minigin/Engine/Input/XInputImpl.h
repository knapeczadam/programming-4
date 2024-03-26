#pragma once

// Project includes
#include "IInputImpl.h"

// Windows includes
#include <windows.h>
#include <XInput.h>

namespace dae
{
    class XInputImpl final : public IInputImpl
    {
    public:
        auto DoProcessInput(std::vector<GameInputCommand> commands) -> bool override;

    private:
        auto IsDownThisFrame(int button) const -> bool;
        auto IsUpThisFrame(int button) const -> bool;
        auto IsPressed(int button) const -> bool;

    private:
        XINPUT_STATE m_previousState = {};
        XINPUT_STATE m_currentState = {};
        int controllerIndex = 0;
        int buttonsPressedThisFrame = 0;
        int buttonsReleasedThisFrame = 0;
    };
}
