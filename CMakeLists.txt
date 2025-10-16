cmake_minimum_required(VERSION 3.26)

project(memory_test)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# add googletest - not needed on godbolt!
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
endif()

# add cpp files for the allocator lib here
add_library(allocator_lib
    allocators/MemoryOverrides.cpp
    allocators/SingleLinkAllocator.cpp
        allocators/FixedSizeAllocator.cpp
        allocators/FixedSizeAllocator.h
        allocators/StackAllocator.cpp
        allocators/StackAllocator.h
)

# compile at max warning level + treat warnings as errors
target_compile_options(allocator_lib PRIVATE
$<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
$<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Werror>
)

# add cpp files for the tests here
add_executable(allocator_tests
    tests/SingleLinkAllocatorTest.cpp
    tests/main.cpp
        tests/FixedSizeAllocatorTest.cpp
        tests/StackAllocatorTest.cpp
)

# compile at max warning level + treat warnings as errors
target_compile_options(allocator_tests PRIVATE
$<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
$<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Werror>
)

target_include_directories(allocator_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/allocators/
)

target_link_libraries(allocator_tests
  allocator_lib
  gtest
)
