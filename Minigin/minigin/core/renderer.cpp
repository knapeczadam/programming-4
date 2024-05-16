#include "renderer.h"

// Project includes
#include "scene_manager.h"
#include "minigin/utility/texture.h"

// Standard includes
#include <stdexcept>

// ImGui includes
#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_sdl2.h"

int get_open_gl_driver_index()
{
    auto opengl_index = -1;
    auto const driver_count = SDL_GetNumRenderDrivers();
    for (auto i = 0; i < driver_count; i++)
    {
        SDL_RendererInfo info;
        if (not SDL_GetRenderDriverInfo(i, &info))
            if (not strcmp(info.name, "opengl"))
                opengl_index = i;
    }
    return opengl_index;
}

namespace mngn
{
    void renderer::init(SDL_Window *window_ptr)
    {
        window_ptr_ = window_ptr;
        renderer_ptr_ = SDL_CreateRenderer(window_ptr, get_open_gl_driver_index(), SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (renderer_ptr_ == nullptr)
        {
            throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
        }

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui_ImplSDL2_InitForOpenGL(window_ptr, SDL_GL_GetCurrentContext());
        ImGui_ImplOpenGL3_Init();
    }
    
    void renderer::render() const
    {
        auto const &color = background_color();
        SDL_SetRenderDrawColor(renderer_ptr_, color.r, color.g, color.b, color.a);
        SDL_RenderClear(renderer_ptr_);

        scene_manager::instance().render();
        scene_manager::instance().render_ui();

        SDL_RenderPresent(renderer_ptr_);
    }

    void renderer::destroy()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();

        if (renderer_ptr_ != nullptr)
        {
            SDL_DestroyRenderer(renderer_ptr_);
            renderer_ptr_ = nullptr;
        }
    }

    void renderer::render_texture(texture const &texture, const float x, const float y) const
    {
        SDL_Rect dst_rect{};
        dst_rect.x = static_cast<int>(x);
        dst_rect.y = static_cast<int>(y);
        SDL_QueryTexture(texture.sdl_texture(), nullptr, nullptr, &dst_rect.w, &dst_rect.h);
        SDL_RenderCopy(sdl_renderer(), texture.sdl_texture(), nullptr, &dst_rect);

        // draw debug magenta rectangle
        SDL_SetRenderDrawColor(sdl_renderer(), 255, 0, 255, 255);
        SDL_RenderDrawRect(sdl_renderer(), &dst_rect);
        
#ifndef NDEBUG
        darw_debug_rect(dst_rect);
#endif
    }

    void renderer::render_texture(texture const &texture, const float x, const float y, const float width, const float height) const
    {
        SDL_Rect dst_rect{};
        dst_rect.x = static_cast<int>(x);
        dst_rect.y = static_cast<int>(y);
        dst_rect.w = static_cast<int>(width);
        dst_rect.h = static_cast<int>(height);
        SDL_RenderCopy(sdl_renderer(), texture.sdl_texture(), nullptr, &dst_rect);

#ifndef NDEBUG
        darw_debug_rect(dst_rect);
#endif
    }

    void renderer::render_texture(texture const &texture, SDL_Rect const &src_rect, SDL_Rect const &dst_rect) const
    {
        SDL_RenderCopy(sdl_renderer(), texture.sdl_texture(), &src_rect, &dst_rect);
        
#ifndef NDEBUG
        darw_debug_rect(dst_rect);
#endif
    }

    auto renderer::sdl_renderer() const -> SDL_Renderer * { return renderer_ptr_; }

    void renderer::darw_debug_rect(SDL_Rect const &dst_rect) const
    {
        SDL_SetRenderDrawColor(sdl_renderer(), 255, 0, 255, 255);
        SDL_RenderDrawRect(sdl_renderer(), &dst_rect);
    }
}
