#pragma once

// Project includes
#include "Font.h"
#include "Singleton.h"
#include "Texture2D.h"

// Standard includes
#include <memory>
#include <unordered_map>
#include <string>

namespace dae
{
    // Forward declarations
    // class Texture2D;
    // class Font;

    class ResourceManager final : public Singleton<ResourceManager>
    {
    public:
        void Init(const std::string& data);
        Texture2D* LoadTexture(const std::string& file);
        Font* LoadFont(const std::string& file, unsigned int size);

    private:
        friend class Singleton<ResourceManager>;
        ResourceManager() = default;
        std::string m_dataPath;

        std::unordered_map<std::string, std::unique_ptr<Texture2D>> m_textures{};
        std::unordered_multimap<std::string, std::pair<unsigned int, std::unique_ptr<Font>>> m_fonts{};
    };
}
