#pragma once

// Project includes
#include "Singleton.h"

namespace dae
{
    class TestManager final : public Singleton<TestManager>
    {
    public:
        void RunAllTests();

    private:
        friend class Singleton<TestManager>;
        TestManager() = default;

        void TestComponents();
        void TestParentChildRelationship();
        void TestScene();
        void TestPosition();
        
    };
}
