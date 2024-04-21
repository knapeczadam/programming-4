#pragma once

// Project includes
#include "utility/singleton.h"

namespace dae
{
    class test_manager final : public singleton<test_manager>
    {
    public:
        void run_all_tests();

    private:
        friend class singleton<test_manager>;
        test_manager() = default;

        void test_components();
        void test_parent_child_relationship();
        void test_scene();
        void test_position();
        
    };
}
