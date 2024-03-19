#include "Minigin.h"

#define WIN32_LEAN_AND_MEAN
// Windows includes
#include <windows.h>

// Project includes
#include "InputManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "TimeManager.h"

// Standard includes
#include <chrono>
#include <iostream>
#include <stdexcept>
#include <thread>

// SDL includes
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

SDL_Window* g_window{};

void PrintSDLVersion()
{
    SDL_version version{};
    SDL_VERSION(&version);
    printf("We compiled against SDL version %u.%u.%u ...\n",
           version.major, version.minor, version.patch);

    SDL_GetVersion(&version);
    printf("We are linking against SDL version %u.%u.%u.\n",
           version.major, version.minor, version.patch);

    SDL_IMAGE_VERSION(&version);
    printf("We compiled against SDL_image version %u.%u.%u ...\n",
           version.major, version.minor, version.patch);

    version = *IMG_Linked_Version();
    printf("We are linking against SDL_image version %u.%u.%u.\n",
           version.major, version.minor, version.patch);

    SDL_TTF_VERSION(&version)
    printf("We compiled against SDL_ttf version %u.%u.%u ...\n",
           version.major, version.minor, version.patch);

    version = *TTF_Linked_Version();
    printf("We are linking against SDL_ttf version %u.%u.%u.\n",
           version.major, version.minor, version.patch);
}

namespace dae
{
    Minigin::Minigin(const std::string& dataPath)
    {
        PrintSDLVersion();

        if (SDL_Init(SDL_INIT_VIDEO) != 0)
        {
            throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
        }

        std::string title = "Programming 4 assignment - ";

#ifdef _DEBUG
        title += "Debug";
#else
        title += "Release";
#endif

#ifdef _WIN64
        title += " | x64";
#elif _WIN32
        title += " | x86";
#endif

        g_window = SDL_CreateWindow(
            title.c_str(),
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            640,
            480,
            SDL_WINDOW_OPENGL
        );
        if (g_window == nullptr)
        {
            throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
        }

        Renderer::GetInstance().Init(g_window);

        ResourceManager::GetInstance().Init(dataPath);
    }

    Minigin::~Minigin()
    {
        Renderer::GetInstance().Destroy();
        SDL_DestroyWindow(g_window);
        g_window = nullptr;
        SDL_Quit();
    }

    void Minigin::Run(const std::function<void()>& load)
    {
        using namespace std::chrono;
        using namespace std::chrono_literals;
        
        load();

        const auto& renderer = Renderer::GetInstance();
        auto& sceneManager   = SceneManager::GetInstance();
        auto& input          = InputManager::GetInstance();

        bool doContinue = true;
        auto lastTime = high_resolution_clock::now();
        float lag = 0.0f;
        
        while (doContinue)
        {
            const auto currentTime = high_resolution_clock::now();
            TimeManager::GetInstance().deltaTime = duration<float>(currentTime - lastTime).count();
            
            lastTime = currentTime;
            lag += TimeManager::GetInstance().deltaTime;
            
            doContinue = input.ProcessInput();
            // std::cout << "FPS: " << 1.0f / Time::deltaTime << "\n";
            sceneManager.Update();
            // TODO: LateUpdate can be called before rendering
            renderer.Render();

            const auto sleepTime = currentTime + milliseconds(static_cast<long long>(TimeManager::GetInstance().msPerFrame)) - high_resolution_clock::now();

            std::this_thread::sleep_for(sleepTime);
        }
    }
}
