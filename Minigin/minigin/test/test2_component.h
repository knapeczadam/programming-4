#pragma once

// Project includes
#include "minigin/test/test_component.h"

namespace mngn
{
    class test2_component final : public test_component
    {
    public:
        test2_component()           = default;
        ~test2_component() override = default;

        test2_component(test2_component const &other)            = delete;
        test2_component(test2_component &&other)                 = delete;
        test2_component &operator=(test2_component const &other) = delete;
        test2_component &operator=(test2_component &&other)      = delete;

        void test() const override { }
    };
}
