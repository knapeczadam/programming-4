#pragma once

// Project includes
#include "minigin/utility/singleton.h"

// Standard includes
#include <string>

namespace qbert
{
    class initial_manager final : public mngn::singleton<initial_manager>
    {
        enum input
        {
            space     = 26,
            dot       = 27,
            backspace = 28,
            end       = 29
        };
    public:
        ~initial_manager() override = default;

        initial_manager(initial_manager const& other)            = delete;
        initial_manager(initial_manager &&other)                 = delete;
        initial_manager &operator=(initial_manager const &other) = delete;
        initial_manager &operator=(initial_manager &&other)      = delete;

        void move_input(int dir);
        void accept_input();
        [[nodiscard]] auto initial() const -> std::string const& { return initial_; }
        void save_initial();

    private:
        friend class singleton<initial_manager>;
        initial_manager() = default;

        void move_underline();
        void render_initials();

    private:
        std::string initial_;
        int curr_input_ = 0;
        int const max_input_ = 30;
    };
}
