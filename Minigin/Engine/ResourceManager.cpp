#include "ResourceManager.h"

// Project includes
#include "Renderer.h"
#include "Texture2D.h"
#include "Font.h"

// Standard includes
#include <stdexcept>

// SDL includes
#include <SDL_image.h>
#include <SDL_ttf.h>

namespace dae
{
    void ResourceManager::Init(const std::string& dataPath)
    {
        m_dataPath = dataPath;

        if (TTF_Init() != 0)
        {
            throw std::runtime_error(std::string("Failed to load support for fonts: ") + SDL_GetError());
        }
    }

    Texture2D* ResourceManager::LoadTexture(const std::string& file)
    {
        // Check if texture is already present
        const auto fullPath = m_dataPath + file;
        const auto it = m_textures.find(fullPath);
        if (it != m_textures.cend())
        {
            return it->second.get();
        }
        
        auto texture = IMG_LoadTexture(Renderer::GetInstance().GetSDLRenderer(), fullPath.c_str());
        if (texture == nullptr)
        {
            throw std::runtime_error(std::string("Failed to load texture: ") + SDL_GetError());
        }

        // Cache the texture
        m_textures[fullPath] = std::make_unique<Texture2D>(texture);
        return m_textures[fullPath].get();
    }

    Font* ResourceManager::LoadFont(const std::string& file, unsigned int size)
    {
        // Check if font is already present
        const auto fullPath = m_dataPath + file;
        const auto range = m_fonts.equal_range(fullPath);
        for (auto it = range.first; it != range.second; ++it)
        {
            if (it->second.first == size)
            {
                return it->second.second.get();
            }
        }

        // Load the font and cache it
        auto font = std::make_unique<Font>(fullPath, size);
        m_fonts.emplace(fullPath, std::make_pair(size, std::move(font)));

        // Return the newly loaded font
        const auto rangeNew = m_fonts.equal_range(fullPath);
        for (auto it = rangeNew.first; it != rangeNew.second; ++it)
        {
            if (it->second.first == size)
            {
                return it->second.second.get();
            }
        }
        return nullptr;
    }
}
