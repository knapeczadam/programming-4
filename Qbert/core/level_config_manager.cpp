#include "level_config_manager.h"

// Standard includes
#include <fstream>
#include <stdexcept>

namespace qbert
{
    void level_config_manager::load_level_config(std::string const &file_path)
    {
        std::ifstream file(file_path);
        if (file)
        {
            level_config_ = json::parse(file);
        }
    }
}
