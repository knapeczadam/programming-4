#pragma once

// Project includes
#include "TestComponent.h"

namespace dae
{
    class Test2Component : public TestComponent
    {
    public:
        Test2Component() = default;
        virtual ~Test2Component() override = default;

        Test2Component(const Test2Component& other)            = delete;
        Test2Component(Test2Component&& other)                 = delete;
        Test2Component& operator=(const Test2Component& other) = delete;
        Test2Component& operator=(Test2Component&& other)      = delete;

        void Test() const override { }
    };
}
