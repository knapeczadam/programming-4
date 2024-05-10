#pragma once

// Project includes
#include "minigin/component/family/ui_component.h"

// Standard includes
#include <vector>

namespace mngn
{
    // Forward declarations
    class sprite;
    
    class multisprite_ui_component final : public ui_component
    {
    public:
        multisprite_ui_component();
        explicit multisprite_ui_component(std::vector<sprite*> const &sprites);
        ~multisprite_ui_component() override;

        multisprite_ui_component(multisprite_ui_component const &other)            = delete;
        multisprite_ui_component(multisprite_ui_component &&other)                 = delete;
        multisprite_ui_component &operator=(multisprite_ui_component const &other) = delete;
        multisprite_ui_component &operator=(multisprite_ui_component &&other)      = delete;

        void render_ui() const override;
        void update() override;

        void set_sprites(std::vector<sprite*> const &sprites) { sprites_ = sprites; }

    private:
        std::vector<sprite*> sprites_;
    };
}
