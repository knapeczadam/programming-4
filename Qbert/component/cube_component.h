#pragma once

// Project includes
#include "minigin/component/family/custom_component.h"
#include "minigin/core/i_observer.h"

// Standard includes
#include <vector>

// Forward declaration
namespace mngn
{
    class sprite;
}

namespace qbert
{
    class cube_component : public mngn::custom_component, public mngn::i_observer
    {
    public:
        cube_component()           = default;
        explicit cube_component(std::vector<mngn::sprite*> colors, bool revertible = false);
        ~cube_component() override = default;

        cube_component(cube_component const &other)            = delete;
        cube_component(cube_component &&other)                 = delete;
        cube_component &operator=(cube_component const &other) = delete;
        cube_component &operator=(cube_component &&other)      = delete;

        void awake() override;
        void notify(std::string const &event, mngn::subject *subject_ptr) override;

    private:
        std::vector<mngn::sprite*> colors_;
        int                  current_color_ = 0;
        bool                 revertible_    = false;
    };
}
