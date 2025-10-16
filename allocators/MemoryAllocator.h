#pragma once
#include <stddef.h> // for size_t

namespace dae
{
    class MemoryAllocator
    {
    public:
        virtual ~MemoryAllocator() = default;

        MemoryAllocator(const MemoryAllocator &)             = delete;
        MemoryAllocator(MemoryAllocator &&)                  = delete;
        MemoryAllocator &operator=(const MemoryAllocator &)  = delete;
        MemoryAllocator &operator=(const MemoryAllocator &&) = delete;

        virtual auto Acquire(size_t = 0) -> void * = 0;
        virtual void Release(void *) = 0;

        struct Tag
        {
            MemoryAllocator *pool;
        };

    protected:
        MemoryAllocator() = default;
    };
}