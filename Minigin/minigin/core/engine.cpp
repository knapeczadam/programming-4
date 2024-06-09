#include "engine.h"

// Project includes
#include "minigin/core/collision_manager.h"
#include "minigin/core/game_time.h"
#include "minigin/core/renderer.h"
#include "minigin/core/resource_manager.h"
#include "minigin/core/scene_manager.h"
#include "minigin/core/sprite_manager.h"
#include "minigin/input/input_manager.h"

// Standard includes
#include <chrono>
#include <stdexcept>
#include <thread>

// SDL includes
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

// Windows includes
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// Steam includes
#include <steam_api_common.h>

SDL_Window *g_window_ptr = nullptr;

void print_sdl_version()
{
    SDL_version version{};
    SDL_VERSION(&version);
    printf("We compiled against SDL version %u.%u.%u ...\n", version.major, version.minor, version.patch);

    SDL_GetVersion(&version);
    printf("We are linking against SDL version %u.%u.%u.\n", version.major, version.minor, version.patch);

    SDL_IMAGE_VERSION(&version);
    printf("We compiled against SDL_image version %u.%u.%u ...\n", version.major, version.minor, version.patch);

    version = *IMG_Linked_Version();
    printf("We are linking against SDL_image version %u.%u.%u.\n", version.major, version.minor, version.patch);

    SDL_TTF_VERSION(&version)
    printf("We compiled against SDL_ttf version %u.%u.%u ...\n", version.major, version.minor, version.patch);

    version = *TTF_Linked_Version();
    printf("We are linking against SDL_ttf version %u.%u.%u.\n", version.major, version.minor, version.patch);

    SDL_MIXER_VERSION(&version)
    version = *Mix_Linked_Version();
    printf("We are linking against SDL_mixer version %u.%u.%u.\n", version.major, version.minor, version.patch);
}

namespace mngn
{
    engine::engine(std::string const &data_path)
    {
        print_sdl_version();

        if (SDL_Init(SDL_INIT_VIDEO) != 0)
        {
            throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
        }

        std::string title = "Programming 4 assignment - ";
        
#ifndef NDEBUG
        title += "Debug";
#else
        title += "Release";
#endif

#ifdef _WIN64
        title += " | x64";
#elif _WIN32
        title += " | x86";
#endif

        g_window_ptr = SDL_CreateWindow(
            title.c_str(),
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            480,
            512,
            SDL_WINDOW_OPENGL
        );
        if (g_window_ptr == nullptr)
        {
            throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
        }

        renderer::instance().init(g_window_ptr);

        resource_manager::instance().init(data_path);
        sprite_manager::instance().set_data_path(data_path);
    }

    engine::~engine()
    {
        renderer::instance().destroy();
        SDL_DestroyWindow(g_window_ptr);
        g_window_ptr = nullptr;
        SDL_Quit();
    }

    void engine::run(std::function<void()> const &load)
    {
        using namespace std::chrono;
        using namespace std::chrono_literals;
        
        load();

        auto const &renderer = renderer::instance();
        auto &scene_manager  = scene_manager::instance();
        auto const &input    = input_manager::instance();

        bool  do_continue = true;
        auto  last_time   = high_resolution_clock::now();
        float lag         = 0.0f;

        scene_manager.awake();
        scene_manager.on_enable();
        scene_manager.start();
        
        while (do_continue)
        {
            auto const current_time = high_resolution_clock::now();
            game_time::instance().set_delta_time(duration<float>(current_time - last_time).count()); // dt always has a 1 frame delay
            
            last_time = current_time;
            lag += game_time::instance().delta_time();
            
            do_continue = input.process_input();

            scene_manager.on_enable();

            while (lag >= game_time::instance().fixed_delta_time())
            {
                scene_manager.fixed_update();
                collision_manager::instance().detect_collisions();
                lag -= game_time::instance().fixed_delta_time();
            }
            
            scene_manager.update();
            scene_manager.late_update();
            renderer.render();
            scene_manager.on_disable();

            // SteamAPI_RunCallbacks(); 

            auto const sleep_time = current_time + milliseconds(static_cast<long long>(game_time::instance().ms_per_frame())) - high_resolution_clock::now();

            std::this_thread::sleep_for(sleep_time);
        }
    }
}
