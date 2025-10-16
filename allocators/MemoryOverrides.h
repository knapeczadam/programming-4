#pragma once
#include <stddef.h> // for size_t

// overloads global new and delete.

namespace dae
{
    class MemoryAllocator;
}

auto operator new(size_t nbBytes) -> void *;
auto operator new(size_t nbBytes, dae::MemoryAllocator &storagePool) -> void *;
auto operator new[](size_t nbBytes) -> void *;
auto operator new[](size_t nbBytes, dae::MemoryAllocator &storagePool) -> void *;

void operator delete(void *pointerToBuffer) noexcept;
void operator delete(void *pointerToBuffer, long unsigned int) noexcept;
void operator delete[](void *pointerToBuffer) noexcept;
void operator delete[](void *pointerToBuffer, long unsigned int) noexcept;
void operator delete(void *pointerToBuffer, dae::MemoryAllocator &storagePool) noexcept;
