#pragma once

// Standard includes
#include <functional>
#include <string>

namespace mngn
{
    class engine
    {
    public:
        explicit engine(std::string const &data_path);
        ~engine();

        engine(engine const &other)            = delete;
        engine(engine &&other)                 = delete;
        engine &operator=(engine const &other) = delete;
        engine &operator=(engine &&other)      = delete;
        
        void run(std::function<void()> const &load);
    };
}
