#include "FixedSizeAllocator.h"

#include <stdexcept>

namespace dae
{

    FixedSizeAllocator::FixedSizeAllocator(uint32_t numOfBlock, uint32_t sizeOfEachBlock)
        : m_numOfBlocks{numOfBlock}
        , m_sizeOfEachBlock{sizeOfEachBlock}
        , m_numFreeBlocks{numOfBlock}
        , m_numInitialized{0}
        , m_memStart {new uint8_t[numOfBlock * sizeOfEachBlock]}
        , m_next{m_memStart}
    {
    }

    FixedSizeAllocator::~FixedSizeAllocator()
    {
        delete[] m_memStart;
    }

    void * FixedSizeAllocator::Acquire(size_t nbBytes)
    {
        if (nbBytes > m_sizeOfEachBlock or m_numFreeBlocks == 0)
        {
            throw std::bad_alloc();
        }
        if (m_numInitialized < m_numOfBlocks)
        {
            auto p = reinterpret_cast<uint32_t *>(AddFromIndex(m_numInitialized));
            *p = m_numInitialized + 1;
            m_numInitialized++;
        }
        void *ret = nullptr;
        if (m_numFreeBlocks > 0)
        {
            ret = m_next;
            --m_numFreeBlocks;
            if (m_numFreeBlocks != 0)
            {
                m_next = AddFromIndex(*m_next);
            }
            else
            {
                m_next = nullptr;
            }
        }
        return ret;
    }

    void FixedSizeAllocator::Release(void *pointerToBuffer)
    {
        // Not sure if this is necessary
        // if (pointerToBuffer == nullptr)
        // {
        //     throw std::runtime_error("Pointer is null");
        // }
        // if (m_numFreeBlocks == m_numOfBlocks)
        // {
        //     throw std::runtime_error("All blocks are free");
        // }
        if (pointerToBuffer < m_memStart or pointerToBuffer >= m_memStart + m_numOfBlocks * m_sizeOfEachBlock)
        {
            throw std::runtime_error("Pointer is out of range");
        }
        if (m_next != nullptr)
        {
            *reinterpret_cast<uint32_t *>(pointerToBuffer) = IndexFromAddr(m_next);
            m_next = reinterpret_cast<uint8_t *>(pointerToBuffer);
        }
        else
        {
            *reinterpret_cast<uint32_t *>(pointerToBuffer) = m_numOfBlocks;
            m_next = reinterpret_cast<uint8_t *>(pointerToBuffer);
        }
        ++m_numFreeBlocks;
    }

    auto FixedSizeAllocator::AddFromIndex(uint32_t i) const -> uint8_t *
    {
        return m_memStart + i * m_sizeOfEachBlock;
    }

    auto FixedSizeAllocator::IndexFromAddr(uint8_t const *p) const -> uint32_t
    {
        return static_cast<uint32_t>(p - m_memStart) / m_sizeOfEachBlock;
    }
}
