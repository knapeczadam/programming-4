#pragma once

// Project includes
#include "Transform.h"

namespace dae
{
    class BaseComponent
    {
    public:
        BaseComponent() = default;
        virtual ~BaseComponent() = default;

        BaseComponent(const BaseComponent& other)            = delete;
        BaseComponent(BaseComponent&& other)                 = delete;
        BaseComponent& operator=(const BaseComponent& other) = delete;
        BaseComponent& operator=(BaseComponent&& other)      = delete;

        virtual void Update() = 0;
        virtual void Render() const = 0;

        virtual void SetPosition(float x, float y) final;

    protected:
        Transform m_transform{};
    };
}
