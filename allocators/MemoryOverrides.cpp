#include "MemoryOverrides.h"
#include "MemoryAllocator.h"

#include <cstdlib>

using namespace dae;

void *operator new(size_t nbBytes, MemoryAllocator &storagePool)
{
    if (nbBytes == 0) nbBytes = 1;
    while (true)
    {
        auto *const tag = reinterpret_cast<MemoryAllocator::Tag *>(storagePool.Acquire(
            nbBytes + sizeof(MemoryAllocator::Tag)));
        tag->pool = &storagePool;
        return tag + 1;
    }
}

void *operator new[](size_t nbBytes, MemoryAllocator &storagePool)
{
    return operator new(nbBytes, storagePool);
}

void *operator new(size_t nbBytes)
{
    if (nbBytes == 0) nbBytes = 1;
    while (true)
    {
        auto *const tag = reinterpret_cast<MemoryAllocator::Tag *>(malloc(nbBytes + sizeof(MemoryAllocator::Tag)));
        tag->pool = nullptr;
        return tag + 1;
    }
}

void *operator new[](size_t nbBytes)
{
    return operator new(nbBytes);
}

void operator delete(void *pointerToBuffer, MemoryAllocator &storagePool) noexcept
{
    if (pointerToBuffer != nullptr)
    {
        MemoryAllocator::Tag *const tag = reinterpret_cast<MemoryAllocator::Tag *>(pointerToBuffer) - 1;
        storagePool.Release(tag);
    }
}

void operator delete(void *pointerToBuffer) noexcept
{
    if (pointerToBuffer != nullptr)
    {
        MemoryAllocator::Tag *const tag = reinterpret_cast<MemoryAllocator::Tag *>(pointerToBuffer) - 1;
        if (tag->pool != nullptr)
            tag->pool->Release(tag);
        else
            free(tag);
    }
}

void operator delete[](void *pointerToBuffer) noexcept
{
    operator delete(pointerToBuffer);
}

void operator delete(void *pointerToBuffer, long unsigned int) noexcept
{
    operator delete(pointerToBuffer);
}

void operator delete[](void *pointerToBuffer, long unsigned int) noexcept
{
    operator delete(pointerToBuffer);
}
