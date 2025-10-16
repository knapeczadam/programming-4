#include <gtest/gtest.h>
#include <vector>
#include <cstring> // for std::memset

#include "MemoryOverrides.h"
#include "FixedSizeAllocator.h"

#if __GNUC__
// ignoring some gcc warnings because we are deliberately messing with memory
#pragma GCC diagnostic ignored "-Wdelete-incomplete"
#ifndef __clang__
#pragma GCC diagnostic ignored "-Wclass-memaccess"
#endif
#endif

namespace dae
{
	const size_t block_size = sizeof(void*) * 4;
	const size_t nb_blocks = 32;
	const size_t pointer_size = sizeof(void*);

	class Object
	{
	public:
		int m_integer{ 0 };
		float m_float{ 0 };
	};

	TEST(FixedSizeAllocatorTests, Construct)
	{
		FixedSizeAllocator allocator(block_size, nb_blocks);
	}

	TEST(FixedSizeAllocatorTests, SingleAllocation)
	{
		FixedSizeAllocator allocator(block_size, nb_blocks);

		const size_t test_size = block_size;
		void* pointer;
		pointer = allocator.Acquire(test_size);
		EXPECT_NE(pointer, nullptr);
		std::memset(pointer, 1, test_size);
		allocator.Release(pointer);
	}

	TEST(FixedSizeAllocatorTests, NewDelete)
	{
		FixedSizeAllocator allocator(block_size, nb_blocks);

		Object *pointer = new(allocator) Object();
		EXPECT_NE(pointer, nullptr);
		std::memset(pointer, 1, sizeof(*pointer));
		delete pointer;
	}

	TEST(FixedSizeAllocatorTests, InvalidRelease)
	{
		FixedSizeAllocator allocator(block_size, nb_blocks);

		void *pointer = new char;
		EXPECT_THROW(allocator.Release(pointer), std::runtime_error);
		delete pointer;
	}

	TEST(FixedSizeAllocatorTests, TwoAllocations)
	{
		FixedSizeAllocator allocator(block_size, nb_blocks);

		const size_t test_size = block_size;
		void* pointer1;
		void* pointer2;
		pointer1 = allocator.Acquire(test_size);
		pointer2 = allocator.Acquire(test_size);
		EXPECT_NE(pointer1, nullptr);
		EXPECT_NE(pointer2, nullptr);
		std::memset(pointer1, 1, test_size);
		std::memset(pointer2, 1, test_size);
		allocator.Release(pointer1);
		allocator.Release(pointer2);
	}

	TEST(FixedSizeAllocatorTests, ManySmallAllocations)
	{
		FixedSizeAllocator allocator(block_size, nb_blocks);
		const size_t test_size = block_size / 2;
		std::vector<void*> pointers;
		for (size_t i = 0; i < nb_blocks; ++i)
		{
			void* pointer = allocator.Acquire(test_size);
			EXPECT_NE(pointer, nullptr);
			pointers.push_back(pointer);
		}
		for (size_t i = 0; i < nb_blocks; ++i)
		{
			allocator.Release(pointers[i]);
		}
	}

	TEST(FixedSizeAllocatorTests, OutOfMemory)
	{
		FixedSizeAllocator allocator(block_size, nb_blocks);
		const size_t test_size = block_size;
		for (size_t i = 0; i < nb_blocks; ++i)
		{
			void* pointer = allocator.Acquire(test_size);
			EXPECT_NE(pointer, nullptr);
		}
		EXPECT_THROW(allocator.Acquire(test_size), std::bad_alloc);
	}

	TEST(FixedSizeAllocatorTests, TooLargeAllocation)
	{
		FixedSizeAllocator allocator(block_size, nb_blocks);
		const size_t test_size = block_size + 1;
		EXPECT_THROW(allocator.Acquire(test_size), std::bad_alloc);
	}
}
