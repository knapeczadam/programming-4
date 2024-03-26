#include "InputManager.h"

// Project includes
#include "GameActorCommand.h"
#include "IInputImpl.h"
#include "SDLInputImpl.h"
#include "XInputImpl.h"

// Standard includes
#include <iostream>

namespace dae
{
    class InputManager::InputManagerImpl
    {
    public:
        InputManagerImpl()
        {
            m_InputImpls.push_back(std::make_unique<SDLInputImpl>());
            m_InputImpls.push_back(std::make_unique<XInputImpl>());
        }
        
        bool DoProcessInput(std::vector<GameInputCommand> commands)
        {
            for (auto& inputImpl : m_InputImpls)
            {
                if (not inputImpl->DoProcessInput(commands))
                {
                    return false;
                }
            }
            return true;
        }
        
    public:
        std::vector<std::unique_ptr<IInputImpl>> m_InputImpls;
        
        std::vector<GameInputCommand> m_Commands;
        std::vector<std::unique_ptr<GameActorCommand>> m_GameActorCommands;
    };

    InputManager::InputManager()
        : m_implPtr(std::make_unique<InputManagerImpl>())
    {
    }

    InputManager::~InputManager() = default;

    bool InputManager::ProcessInput()
    {
        return m_implPtr->DoProcessInput(m_implPtr->m_Commands);
    }

    void InputManager::BindCommand(InputType inputType, InputState inputState, int input, std::unique_ptr<GameActorCommand> command)
    {
        m_implPtr->m_GameActorCommands.emplace_back(std::move(command));
        m_implPtr->m_Commands.push_back({inputType, inputState, input, m_implPtr->m_GameActorCommands.back().get()});   
    }

    bool InputManager::UnbindCommand(InputType inputType, InputState inputState, int input)
    {
        for (auto it = m_implPtr->m_Commands.begin(); it != m_implPtr->m_Commands.end(); ++it)
        {
            if (it->inputType == inputType and it->inputState == inputState and it->input == input)
            {
                m_implPtr->m_Commands.erase(it);
                return true;
            }
        }
        return false;
    }
        
}
