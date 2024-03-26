#pragma once

// Standard includes
#include <vector>

namespace dae
{
    // Forward declarations
    class GameActorCommand;
    enum class InputState;
    enum class InputType;
    
    // Forward declarations
    struct GameInputCommand;
    
    class IInputImpl
    {
    public:
        IInputImpl() = default;
        virtual ~IInputImpl() = default;

        IInputImpl(const IInputImpl& other)            = delete;
        IInputImpl(IInputImpl&& other)                 = delete;
        IInputImpl& operator=(const IInputImpl& other) = delete;
        IInputImpl& operator=(IInputImpl&& other)      = delete;
        
        virtual auto DoProcessInput(std::vector<GameInputCommand> commands) -> bool = 0;
    };
}