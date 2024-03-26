#include "Minigin.h"

#define WIN32_LEAN_AND_MEAN
// Windows includes
#include <windows.h>

// Project includes
#include "InputManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "GameTime.h"

// Standard includes
#include <chrono>
#include <iostream>
#include <stdexcept>
#include <thread>

// SDL includes
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

// Steam includes
#include <steam_api_common.h>

SDL_Window* g_window{};

void print_sdl_version()
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
    minigin::minigin(const std::string& dataPath)
    {
        print_sdl_version();

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

        renderer::get_instance().init(g_window);

        resource_manager::get_instance().init(dataPath);
    }

    minigin::~minigin()
    {
        renderer::get_instance().destroy();
        SDL_DestroyWindow(g_window);
        g_window = nullptr;
        SDL_Quit();
    }

    void minigin::run(const std::function<void()>& load)
    {
        using namespace std::chrono;
        using namespace std::chrono_literals;
        
        load();

        const auto& renderer = renderer::get_instance();
        auto& scene_manager   = scene_manager::get_instance();
        const auto& input          = input_manager::get_instance();

        bool do_continue = true;
        auto last_time = high_resolution_clock::now();
        float lag = 0.0f;
        
        while (do_continue)
        {
            const auto current_time = high_resolution_clock::now();
            game_time::get_instance().delta_time_ = duration<float>(current_time - last_time).count();
            
            last_time = current_time;
            lag += game_time::get_instance().delta_time_;
            
            do_continue = input.process_input();
            // std::cout << "FPS: " << 1.0f / Time::deltaTime << "\n";
            scene_manager.update();
            scene_manager.late_update();
            renderer.render();

            SteamAPI_RunCallbacks(); 

            const auto sleep_time = current_time + milliseconds(static_cast<long long>(game_time::get_instance().ms_per_frame_)) - high_resolution_clock::now();

            std::this_thread::sleep_for(sleep_time);
        }
    }
}
