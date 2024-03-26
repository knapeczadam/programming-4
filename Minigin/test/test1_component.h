#pragma once

// Project includes
#include "test_component.h"

namespace dae
{
    class test1_component : public test_component
    {
    public:
        test1_component() = default;
        ~test1_component() override = default;

        test1_component(const test1_component& other)            = delete;
        test1_component(test1_component&& other)                 = delete;
        test1_component& operator=(const test1_component& other) = delete;
        test1_component& operator=(test1_component&& other)      = delete;

        void test() const override { }
    };
}
