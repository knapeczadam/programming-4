#pragma once

// Project includes
#include "component/core/base_component.h"

namespace dae
{
   class test_component : public base_component
   {
   public:
      test_component()           = default;
      ~test_component() override = default;

      test_component(test_component const &other)            = delete;
      test_component(test_component &&other)                 = delete;
      test_component &operator=(test_component const &other) = delete;
      test_component &operator=(test_component &&other)      = delete;

      [[nodiscard]] auto get_family() const -> component_family override { return component_family::test; }

      virtual void test() const = 0;
   };
}