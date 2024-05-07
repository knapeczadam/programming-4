#pragma once

// Project includes
#include "minigin/core/game_component.h"

namespace mngn
{
   class test_component : public game_component
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