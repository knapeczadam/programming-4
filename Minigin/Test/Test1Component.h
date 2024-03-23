#pragma once

// Project includes
#include "TestComponent.h"

namespace dae
{
    class Test1Component : public TestComponent
    {
    public:
        Test1Component() = default;
        virtual ~Test1Component() override = default;

        Test1Component(const Test1Component& other)            = delete;
        Test1Component(Test1Component&& other)                 = delete;
        Test1Component& operator=(const Test1Component& other) = delete;
        Test1Component& operator=(Test1Component&& other)      = delete;

        void Test() const override { }
    };
}
