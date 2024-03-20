#pragma once

// Project includes
#include "BaseComponent.h"

namespace dae
{
    class Test2Component : public BaseComponent
    {
    public:
        Test2Component() = default;
        virtual ~Test2Component() override = default;

        Test2Component(const Test2Component& other)            = delete;
        Test2Component(Test2Component&& other)                 = delete;
        Test2Component& operator=(const Test2Component& other) = delete;
        Test2Component& operator=(Test2Component&& other)      = delete;

        virtual ComponentFamily GetFamily() const override { return ComponentFamily::Test; }
        virtual ComponentType GetType() const override { return ComponentType::Test2; }
    };
}
