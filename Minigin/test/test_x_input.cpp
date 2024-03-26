#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <XInput.h>
#include <iostream>
#include <thread>

#pragma comment(lib, "xinput.lib")

int xmain()
{
    XINPUT_STATE currentState{};
    int controllerIndex{};
    while (true)
    {
        auto t = std::chrono::high_resolution_clock::now();
        
        ZeroMemory(&currentState, sizeof(XINPUT_STATE));
        XInputGetState(controllerIndex, &currentState);
        
        std::cout << "\rsThumbLX: " << currentState.Gamepad.sThumbLX
            << " - sThumbRX: " << currentState.Gamepad.sThumbRX;
        
        if (currentState.Gamepad.wButtons & XINPUT_GAMEPAD_B)
            break;
        
        auto t2 = std::chrono::high_resolution_clock::now() - t;
        t += std::chrono::milliseconds(16) - t2; // we want ~60 fps
        std::this_thread::sleep_until(t);
    }
    return 0;
}
