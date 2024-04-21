#pragma once

// Standard includes
#include <functional>
#include <string>

namespace dae
{
    class minigin
    {
    public:
        explicit minigin(std::string const &data_path);
        ~minigin();

        minigin(minigin const &other)            = delete;
        minigin(minigin &&other)                 = delete;
        minigin &operator=(minigin const &other) = delete;
        minigin &operator=(minigin &&other)      = delete;
        
        void run(std::function<void()> const &load);
    };
}
