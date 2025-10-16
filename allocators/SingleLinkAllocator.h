#pragma once
#include "MemoryAllocator.h"

#include <cstdint>

namespace dae
{
    /// <summary>
    /// Based on the single link allocator by Bruno R. Preiss in "Data structures and algorithms with object-oriented design patterns in c++"
    /// https://www.wiley.com/college/preiss
    /// </summary>
    class SingleLinkAllocator final : public MemoryAllocator
    {
        struct Header
        {
            size_t count;
        };

        struct Block : Header
        {
            const static int size = sizeof(void *) * 4;

            union
            {
                Block *next;
                uint8_t data[size - sizeof(Header)];
            };
        };

        size_t nbBlocks;
        Block *pool;
        Block *head;

        static void FillAllocatedBlock(Block *block, size_t nbBytes);

    public:
        explicit SingleLinkAllocator(size_t sizeInBytes);
        ~SingleLinkAllocator() override;

        /// <summary>
        /// Gets a pointer to a piece of memory.
        /// </summary>
        /// <param name="nbBytes">The size of the memory in number of bytes.</param>
        /// <returns>A pointer to the first byte of the memory</returns>
        auto Acquire(size_t nbBytes) -> void * override;

        void Release(void *) override;

        SingleLinkAllocator(const SingleLinkAllocator &)             = delete;
        SingleLinkAllocator(SingleLinkAllocator &&)                  = delete;
        SingleLinkAllocator &operator=(const SingleLinkAllocator &)  = delete;
        SingleLinkAllocator &operator=(const SingleLinkAllocator &&) = delete;
    };
}
