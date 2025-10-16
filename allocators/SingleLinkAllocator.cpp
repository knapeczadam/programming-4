#include "SingleLinkAllocator.h"
#include <stdexcept>
#include <cstring>

static const unsigned char PATTERN_ALIGN = 0xFC;
static const unsigned char PATTERN_ALLOC = 0x00;

void dae::SingleLinkAllocator::FillAllocatedBlock(Block *block, const size_t nbBytes)
{
    std::memset(block->data, PATTERN_ALLOC, nbBytes);
    const int nbAlignBytes = (sizeof(Block) - ((nbBytes + sizeof(Header)) % sizeof(Block))) % sizeof(Block);
    uint8_t *start = block->data + nbBytes;
    std::memset(start, PATTERN_ALIGN, nbAlignBytes);
}

dae::SingleLinkAllocator::SingleLinkAllocator(const size_t sizeInBytes) : nbBlocks(
                                                                              (sizeInBytes + sizeof(Block) - 1) / sizeof
                                                                              (Block)),
                                                                          pool(new Block[nbBlocks + 1]),
                                                                          // one extra for the head
                                                                          head(pool)
{
    Block *first = pool + 1;
    first->count = nbBlocks;
    first->next = nullptr;

    head->count = 0;
    head->next = first;
}

dae::SingleLinkAllocator::~SingleLinkAllocator()
{
    delete[] pool;
}

auto dae::SingleLinkAllocator::Acquire(const size_t nbBytes) -> void *
{
    const auto nbBlocksToAcquire = (nbBytes + sizeof(Header) + sizeof(Block) - 1) / sizeof(Block);
    auto previousBlock = head;
    auto nextBlock = head->next;
    while (nextBlock != nullptr && nextBlock->count < nbBlocksToAcquire)
    {
        previousBlock = nextBlock;
        nextBlock = nextBlock->next;
    }

    if (nextBlock == nullptr) // we found no suitable block
        throw std::bad_alloc();

    if (nextBlock->count > nbBlocksToAcquire)
    {
        Block *newBlock = nextBlock + nbBlocksToAcquire;
        newBlock->count = nextBlock->count - nbBlocksToAcquire;
        newBlock->next = nextBlock->next;
        nextBlock->count = nbBlocksToAcquire;
        nextBlock->next = newBlock;
    }

    previousBlock->next = nextBlock->next;

#ifdef _DEBUG
    FillAllocatedBlock(nextBlock, nbBytes);
#endif // _DEBUG

    return nextBlock->data;
}

void dae::SingleLinkAllocator::Release(void *pointerToBuffer)
{
    Block *block = reinterpret_cast<Block *>(reinterpret_cast<Header *>(pointerToBuffer) - 1);

    if (block < pool || block > pool + nbBlocks)
        throw std::runtime_error("invalid block");

    auto previousBlock = head;
    auto current = previousBlock->next;
    while (current != nullptr && current < block)
    {
        previousBlock = current;
        current = current->next;
    }

    if (current != nullptr && block + block->count == current)
    {
        block->count += current->count;
        block->next = current->next;
    }
    else
        block->next = current;

    if (previousBlock + previousBlock->count == block)
    {
        previousBlock->count += block->count;
        previousBlock->next = block->next;
    }
    else
        previousBlock->next = block;
}
