#include "StackAllocator.h"

#include <cstdlib>
#include <filesystem>
#include <new>
#include <stdexcept>

namespace dae
{
    StackAllocator::StackAllocator(size_t size)
        : m_stackSizeInBytes{size}
          , m_allocatedMemory{std::malloc(size)}
    {
    }

    StackAllocator::~StackAllocator()
    {
        std::free(m_allocatedMemory);
    }

    auto StackAllocator::Acquire(size_t nbBytes) -> void *
    {
        const size_t availableSpace = m_stackSizeInBytes - m_currentMarker;
        if (nbBytes > availableSpace)
        {
            throw std::bad_alloc{};
        }
        uintptr_t address = reinterpret_cast<uintptr_t>(m_allocatedMemory) + m_currentMarker;
        m_currentMarker = m_currentMarker + nbBytes;
        return reinterpret_cast<void *>(address);
    }

    void StackAllocator::Release(void *pointerToBuffer)
    {
        throw std::runtime_error{"Release is not supported for StackAllocator"};

        // auto address = reinterpret_cast<uintptr_t>(pointerToBuffer);
        // auto startAddress = reinterpret_cast<uintptr_t>(m_allocatedMemory);
        // if (address < startAddress or address >= startAddress + m_stackSizeInBytes)
        // {
        //     throw std::runtime_error{"Invalid pointer"};
        // }
        // m_currentMarker = address - startAddress;
    }

    auto StackAllocator::GetMarker() const -> Marker
    {
        return m_currentMarker;
    }

    void StackAllocator::FreeToMarker(Marker marker)
    {
        if (marker < m_currentMarker)
        {
            m_currentMarker = marker;
        }
    }

    void StackAllocator::Clear()
    {
        m_currentMarker = 0;
    }
}
