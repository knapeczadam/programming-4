#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <XInput.h>
#include <iostream>
#include <thread>

#pragma comment(lib, "xinput.lib")

int xmain()
{
    XINPUT_STATE current_state{};
    int controller_index = 0;
    while (true)
    {
        auto t = std::chrono::high_resolution_clock::now();
        
        ZeroMemory(&current_state, sizeof(XINPUT_STATE));
        XInputGetState(controller_index, &current_state);
        
        std::cout << "\rsThumbLX: " << current_state.Gamepad.sThumbLX << " - sThumbRX: " << current_state.Gamepad.sThumbRX;
        
        if (current_state.Gamepad.wButtons & XINPUT_GAMEPAD_B)
            break;
        
        auto t2 = std::chrono::high_resolution_clock::now() - t;
        t += std::chrono::milliseconds(16) - t2; // we want ~60 fps
        std::this_thread::sleep_until(t);
    }
    return 0;
}
