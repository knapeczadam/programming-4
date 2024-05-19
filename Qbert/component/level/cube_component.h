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
        explicit cube_component(int row_idx, int col_idx, std::vector<mngn::sprite*> colors, bool revertible = false);
        ~cube_component() override = default;

        cube_component(cube_component const &other)            = delete;
        cube_component(cube_component &&other)                 = delete;
        cube_component &operator=(cube_component const &other) = delete;
        cube_component &operator=(cube_component &&other)      = delete;

        void start() override;
        void on_disable() override;
        void notify(std::string const &event, mngn::subject *subject_ptr) override;

    private:
        int  row_idx_         = 0;
        int  col_idx_         = 0;
        int  current_color_   = 0;
        int  score_count_     = 0;
        int const cube_score_ = 25;
        bool revertible_    = false;
        
        std::vector<mngn::sprite*> colors_;
    };
}
