#include "Renderer.h"

// Project includes
#include "SceneManager.h"
#include "Texture2D.h"

// Standard includes
#include <stdexcept>

// ImGui includes
#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_sdl2.h"

int get_open_gl_driver_index()
{
    auto opengl_index = -1;
    const auto driver_count = SDL_GetNumRenderDrivers();
    for (auto i = 0; i < driver_count; i++)
    {
        SDL_RendererInfo info;
        if (!SDL_GetRenderDriverInfo(i, &info))
            if (!strcmp(info.name, "opengl"))
                opengl_index = i;
    }
    return opengl_index;
}

namespace dae
{
    void renderer::init(SDL_Window* window)
    {
        window_ = window;
        renderer_ = SDL_CreateRenderer(window, get_open_gl_driver_index(), SDL_RENDERER_ACCELERATED);
        if (renderer_ == nullptr)
        {
            throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
        }

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui_ImplSDL2_InitForOpenGL(window, SDL_GL_GetCurrentContext());
        ImGui_ImplOpenGL3_Init();
    }
    
    void renderer::render() const
    {
        const auto& color = get_background_color();
        SDL_SetRenderDrawColor(renderer_, color.r, color.g, color.b, color.a);
        SDL_RenderClear(renderer_);

        scene_manager::get_instance().render();
        scene_manager::get_instance().render_ui();

        SDL_RenderPresent(renderer_);
    }

    void renderer::destroy()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();

        if (renderer_ != nullptr)
        {
            SDL_DestroyRenderer(renderer_);
            renderer_ = nullptr;
        }
    }

    void renderer::render_texture(const texture_2d& texture, const float x, const float y) const
    {
        SDL_Rect dst{};
        dst.x = static_cast<int>(x);
        dst.y = static_cast<int>(y);
        SDL_QueryTexture(texture.get_sdl_texture(), nullptr, nullptr, &dst.w, &dst.h);
        SDL_RenderCopy(get_sdl_renderer(), texture.get_sdl_texture(), nullptr, &dst);
    }

    void renderer::render_texture(const texture_2d& texture, const float x, const float y, const float width,
                                 const float height) const
    {
        SDL_Rect dst{};
        dst.x = static_cast<int>(x);
        dst.y = static_cast<int>(y);
        dst.w = static_cast<int>(width);
        dst.h = static_cast<int>(height);
        SDL_RenderCopy(get_sdl_renderer(), texture.get_sdl_texture(), nullptr, &dst);
    }

    auto renderer::get_sdl_renderer() const -> SDL_Renderer* { return renderer_; }
}
