#pragma once

// Project includes
#include "BaseComponent.h"

namespace dae
{
    class TestComponent : public BaseComponent
    {
    public:
        TestComponent() = default;
        virtual ~TestComponent() override = default;

        TestComponent(const TestComponent& other)            = delete;
        TestComponent(TestComponent&& other)                 = delete;
        TestComponent& operator=(const TestComponent& other) = delete;
        TestComponent& operator=(TestComponent&& other)      = delete;

        virtual ComponentFamily GetFamily() const override { return ComponentFamily::Test; }
        virtual ComponentType GetType() const override { return ComponentType::Test; }
    };
}