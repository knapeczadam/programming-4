#pragma once

// Project includes
#include "minigin/test/test_component.h"

namespace mngn
{
    class test1_component final : public test_component
    {
    public:
        test1_component()           = default;
        ~test1_component() override = default;

        test1_component(test1_component const &other)            = delete;
        test1_component(test1_component &&other)                 = delete;
        test1_component &operator=(test1_component const &other) = delete;
        test1_component &operator=(test1_component &&other)      = delete;

        void test() const override { }
    };
}
