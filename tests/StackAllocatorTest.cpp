#include <gtest/gtest.h>
#include <vector>
#include <cstring> // for std::memset

#include "MemoryOverrides.h"
#include "StackAllocator.h"

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
	const size_t allocator_size = 1024;
	const size_t pointer_size = sizeof(void*);

	class Object
	{
	public:
		int m_integer{ 0 };
		float m_float{ 0 };
	};

	TEST(StackAllocatorTests, Construct)
	{
		StackAllocator allocator(allocator_size);
	}

	TEST(StackAllocatorTests, SingleAllocation)
	{
		StackAllocator allocator(allocator_size);

		const size_t test_size = block_size;
		void* pointer;
		pointer = allocator.Acquire(test_size);
		EXPECT_NE(pointer, nullptr);
		std::memset(pointer, 1, test_size);
		allocator.Release(pointer);
	}

	TEST(StackAllocatorTests, NewDelete)
	{
		StackAllocator allocator(allocator_size);

		Object *pointer = new(allocator) Object();
		EXPECT_NE(pointer, nullptr);
		std::memset(pointer, 1, sizeof(*pointer));
		delete pointer;
	}

	TEST(StackAllocatorTests, InvalidRelease)
	{
		StackAllocator allocator(allocator_size);

		void *pointer = new char;
		EXPECT_THROW(allocator.Release(pointer), std::runtime_error);
		delete pointer;
	}

	TEST(StackAllocatorTests, TwoAllocations)
	{
		StackAllocator allocator(allocator_size);

		const size_t test_size = block_size;
		void* pointer1;
		void* pointer2;
		pointer1 = allocator.Acquire(test_size);
		pointer2 = allocator.Acquire(test_size);
		EXPECT_NE(pointer1, nullptr);
		EXPECT_NE(pointer2, nullptr);
		std::memset(pointer1, 1, test_size);
		std::memset(pointer2, 1, test_size);
		allocator.Release(pointer2);
		allocator.Release(pointer1);
	}

	TEST(StackAllocatorTests, ManySmallAllocations)
	{
		StackAllocator allocator(allocator_size);

		const size_t test_size = block_size;
		std::vector<void*> pointers;
		for (size_t i = 0; i < allocator_size / test_size; ++i)
		{
			pointers.push_back(allocator.Acquire(test_size));
			EXPECT_NE(pointers.back(), nullptr);
			std::memset(pointers.back(), 1, test_size);
		}
		for (auto it = pointers.rbegin(); it != pointers.rend(); ++it)
		{
			allocator.Release(*it);
		}
	}

	TEST(StackAllocatorTests, OutOfMemory)
	{
		StackAllocator allocator(allocator_size);

		const size_t test_size = allocator_size + 1;
		EXPECT_THROW(allocator.Acquire(test_size), std::bad_alloc);
	}

	TEST(StackAllocatorTests, Clear)
	{
		StackAllocator allocator(allocator_size);

		const size_t test_size = block_size;
		void* pointer1;
		pointer1 = allocator.Acquire(test_size);
		EXPECT_NE(pointer1, nullptr);
		std::memset(pointer1, 1, test_size);
		allocator.Clear();
		EXPECT_EQ(allocator.GetMarker(), 0);
	}

	TEST(StackAllocatorTests, FreeToMarker)
	{
		StackAllocator allocator(allocator_size);

		const size_t test_size = block_size;
		void* pointer1;
		void* pointer2;
		pointer1 = allocator.Acquire(test_size);
		auto marker = allocator.GetMarker();
		pointer2 = allocator.Acquire(test_size);
		EXPECT_NE(pointer1, nullptr);
		EXPECT_NE(pointer2, nullptr);
		std::memset(pointer1, 1, test_size);
		std::memset(pointer2, 1, test_size);
		EXPECT_NE(allocator.GetMarker(), marker);
		allocator.FreeToMarker(marker);
		EXPECT_EQ(allocator.GetMarker(), marker);
		allocator.Release(pointer2);
		allocator.Release(pointer1);
		EXPECT_EQ(allocator.GetMarker(), 0);
	}

	TEST(StackAllocatorTests, InvalidPointer1)
	{
		StackAllocator allocator(allocator_size);

		const size_t test_size = block_size;
		void* pointer1;
		pointer1 = allocator.Acquire(test_size);
		EXPECT_NE(pointer1, nullptr);
		std::memset(pointer1, 1, test_size);
		EXPECT_THROW(allocator.Release(reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(pointer1) - 1)), std::runtime_error);
		allocator.Release(pointer1);
	}

	TEST(StackAllocatorTests, InvalidPointer2)
	{
		StackAllocator allocator(allocator_size);

		const size_t test_size = block_size;
		void* pointer1;
		pointer1 = allocator.Acquire(test_size);
		EXPECT_NE(pointer1, nullptr);
		std::memset(pointer1, 1, test_size);
		EXPECT_THROW(allocator.Release(reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(pointer1) + allocator_size)), std::runtime_error);
		allocator.Release(pointer1);
	}
}