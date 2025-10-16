#pragma once

#include "MemoryAllocator.h"

#include <cstdint>

namespace dae
{
    /*
     * Based on: Fast Efficient Fixed-Size Memory Pool - Ben Kenwright
     * https://arxiv.org/pdf/2210.16471
     */
    class FixedSizeAllocator final : public MemoryAllocator
    {
    public:
        FixedSizeAllocator(uint32_t numOfBlock, uint32_t sizeOfEachBlock);
        ~FixedSizeAllocator() override;

        FixedSizeAllocator(const FixedSizeAllocator &)             = delete;
        FixedSizeAllocator(FixedSizeAllocator &&)                  = delete;
        FixedSizeAllocator &operator=(const FixedSizeAllocator &)  = delete;
        FixedSizeAllocator &operator=(const FixedSizeAllocator &&) = delete;

        auto Acquire(size_t nbBytes) -> void * override;
        void Release(void *pointerToBuffer) override;

        [[nodiscard]] auto AddFromIndex(uint32_t i) const -> uint8_t *;
        auto IndexFromAddr(uint8_t const *p) const -> uint32_t;

    private:
        uint32_t m_numOfBlocks     = 0;
        uint32_t m_sizeOfEachBlock = 0;
        uint32_t m_numFreeBlocks   = 0;
        uint32_t m_numInitialized  = 0;
        uint8_t  *m_memStart       = nullptr;
        uint8_t  *m_next           = nullptr;
    };

}
