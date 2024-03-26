#pragma once

// Project includes
#include "ui_component.h"

namespace dae
{
    class trash_the_cache_component final : public ui_component
    {
    public:
        trash_the_cache_component() = default;
        ~trash_the_cache_component() override = default;

        trash_the_cache_component(const trash_the_cache_component& other)            = delete;
        trash_the_cache_component(trash_the_cache_component&& other)                 = delete;
        trash_the_cache_component& operator=(const trash_the_cache_component& other) = delete;
        trash_the_cache_component& operator=(trash_the_cache_component&& other)      = delete;

        void render_ui() const override;
    };
}
