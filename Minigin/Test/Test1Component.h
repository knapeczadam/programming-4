#pragma once

// Project includes
#include "BaseComponent.h"

namespace dae
{
    class Test1Component : public BaseComponent
    {
    public:
        Test1Component() = default;
        virtual ~Test1Component() override = default;

        Test1Component(const Test1Component& other)            = delete;
        Test1Component(Test1Component&& other)                 = delete;
        Test1Component& operator=(const Test1Component& other) = delete;
        Test1Component& operator=(Test1Component&& other)      = delete;

        virtual ComponentFamily GetFamily() const override { return ComponentFamily::Test; }
        virtual ComponentType GetType() const override { return ComponentType::Test1; }
    };
}