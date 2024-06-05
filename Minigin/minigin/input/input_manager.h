#pragma once

// Project includes
#include "minigin/utility/singleton.h"

// Standard includes
#include <memory>

namespace mngn
{
    enum class input_type
    {
        keyboard,
        mouse,
        controller
    };
    enum class input_state
    {
        down,
        up,
        pressed
    };
    
    enum class input
    {
        
        k_1,
        k_2,
        k_3,
        
        k_left,
        k_right,
        k_up,
        k_down,

        k_return,
        k_right_shift,

        k_a,
        k_d,
        k_w,
        k_s,

        k_r,
        k_c,
        k_z,
        k_x,

        k_j,
        k_m,

        k_f1,

        c_left,
        c_right,
        c_up,
        c_down,

        c_a,
        c_b,
        c_x,
        c_y
    };

    // Forward declarations
    class base_command;

    struct input_config_info
    {
        input_type input_type;
        input_state input_state;
        input input;
        int controller_idx;
        base_command *command_ptr = nullptr;
    };

    class input_manager final : public singleton<input_manager>
    {
    public:
        ~input_manager() override;

        input_manager(input_manager const &other)            = delete;
        input_manager(input_manager &&other)                 = delete;
        input_manager &operator=(input_manager const &other) = delete;
        input_manager &operator=(input_manager &&other)      = delete;

        [[nodiscard]] auto process_input() const -> bool;

        void bind_command(input_config_info const &config, std::unique_ptr<base_command> command) const;
        [[nodiscard]] auto unbind_command(input_type input_type, input_state input_state, input input) const -> bool;

    private:
        friend class singleton<input_manager>;
        input_manager();

    private:
        struct input_manager_impl;
        std::unique_ptr<input_manager_impl> impl_;
    };
}
