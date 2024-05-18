#pragma once

// Project includes
#include "minigin/utility/singleton.h"
#include "core/factory.h"

// JSON includes
#include "json.hpp"

namespace qbert
{
    // Aliases
    using json = nlohmann::json;
    
    class level_config_manager final : public mngn::singleton<level_config_manager>
    {
    public:
        ~level_config_manager() override = default;

        level_config_manager(level_config_manager const& other)            = delete;
        level_config_manager(level_config_manager &&other)                 = delete;
        level_config_manager &operator=(level_config_manager const &other) = delete;
        level_config_manager &operator=(level_config_manager &&other)      = delete;

        void load_level_config(std::string const &file_path);
        [[nodiscard]] auto get_level_config() const -> json const & { return level_config_; }
        
    private:
        friend class mngn::singleton<level_config_manager>;
        level_config_manager() = default;

    private:
        json level_config_;
    };
}
