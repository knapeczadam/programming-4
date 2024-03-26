#pragma once

// Standard includes
#include <functional>
#include <string>

namespace dae
{
    class minigin
    {
    public:
        explicit minigin(const std::string& dataPath);
        ~minigin();

        minigin(const minigin& other)            = delete;
        minigin(minigin&& other)                 = delete;
        minigin& operator=(const minigin& other) = delete;
        minigin& operator=(minigin&& other)      = delete;
        
        void run(const std::function<void()>& load);
    };
}
