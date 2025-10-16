#pragma once

#include <cstdint>

#include "MemoryAllocator.h"

namespace dae
{
    /*
     * Based on: Memory allocators in C++ - Part 1 - Emmanuel Arias
     * https://eariassoto.github.io/post/memory-allocators-part-1/
     */
    class StackAllocator final : public MemoryAllocator
    {
    public:
        // Type aliases
        using Marker = size_t;

        explicit StackAllocator(size_t size);
        ~StackAllocator() override;

        StackAllocator(const StackAllocator &)             = delete;
        StackAllocator(StackAllocator &&)                  = delete;
        StackAllocator &operator=(const StackAllocator &)  = delete;
        StackAllocator &operator=(const StackAllocator &&) = delete;


        auto Acquire(size_t nbBytes) -> void * override;
        void Release(void *pointerToBuffer) override;

        [[nodiscard]] auto GetMarker() const -> Marker;
        void FreeToMarker(Marker marker);
        void Clear();

    private:
        size_t m_stackSizeInBytes = 0;
        void   *m_allocatedMemory = nullptr;
        Marker m_currentMarker    = 0;

    };
}
