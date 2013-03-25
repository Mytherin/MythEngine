

#pragma once

#include <new>
#include <myth\debug\assert.h>

namespace myth
{
	namespace mem
	{
		//! A fast memory pool that can allocate memory and grow to allow for more memory to be allocated
		/*!
		The growing pool is a fast memory pool that can be used in various ways

		-UNSAFE STATIC SIZE-
		Create the pool with a set amount of memory, then use AllocUnsafe to get new memory, the AllocSafe operation does not check whether 
		or not it exceeds the bounds of the available memory, and will cause undefined behavior if it does so. This
		is the fastest possible memory allocation, though you have to be careful not to request more than the available memory.
		As the pool will never be expanded in size, all the memory can be cleared with Reset. This is useful for e.g. memory
		allocation in a single step.

		-UNSAFE DYNAMIC SIZE-
		As above, use the AllocUnsafe function to get memory, but use the Grow function to allocate more memory to the pool.  
		This method is as fast as the UNSAFE STATIC SIZE method described above, although you will no longer be able to clear
		all the memory of the entire pool using Reset.

		-SAFE DYNAMIC SIZE-
		Use the Alloc method to allocate memory, the Alloc method automatically adds new memory to the pool if
		it is filled up. This is slower than the unsafe methods above, but will never cause undefined behavior as the
		memory pool can not be filled up. This is most useful when the amount of memory that should be allocated is unknown.
		*/
		class __declspec(dllexport) GrowingPool
		{
		public:
			//! Empty Constructor
			/*!
			Creates a growing pool without allocating any memory.
			*/
			GrowingPool() : OVERHEAD_SIZE(sizeof(void*)), memory(0),maxSize(0),allocatedBytes(0) {}
			//! Initialization Constructor
			/*!
			Creates a growing pool with a specific amount of memory
			\param size The amount of bytes to be allocated
			*/
			GrowingPool(size_t size);
			//! Default Destructor
			/*!
			Frees up all memory the growing pool allocated. Does not trigger destructors of any objects stored within the memory.
			*/
			~GrowingPool();

			//! Allocate a set amount of memory
			/*!
			The Alloc method is safe, it checks if there is memory left in the pool, if there is it simply allocates the memory and moves
			forward the pointer. If there is no memory left it allocates a new amount of memory equal to the amount of previously allocated memory.
			So if the constructor is called with GrowingPool(1000), after which Alloc is called until it fills up, it will allocate an additional 1000 bytes.
			\param size The amount of bytes to be allocated
			\return A pointer to the allocated memory
			*/
			void* Alloc(size_t size){
				if (allocatedBytes + size >= maxSize) Grow(size > maxSize ? size : maxSize);
				return (char*)memory + (allocatedBytes += size);}
			//! Unsafe allocation of a set amount of memory
			/*!
			The AllocUnsafe method simply increments the pointer within the growingpool and does not check if there is room left for the 
			memory to be allocated. If it exceeds the total amount of available memory it will return a dangling pointer.
			\param size The amount of bytes to be allocated
			\return A pointer to the allocated memory
			*/
			void* AllocUnsafe(size_t size){
				Assert(allocatedBytes + size < maxSize,"MEMORY ALLOCATION ERROR: The available memory of the concurrent growing pool has been overriden.");
				return (char*)memory + (allocatedBytes += size);}
			//! The amount of memory left in the growing pool
			/*!
			\return The amount of bytes left in the pool
			*/
			size_t Space(){return maxSize - allocatedBytes;}
			//! Resets the memory pointer to a specific position within the allocated memory
			/*!
			The memory pointer is reset to a specific offset. This means that the pool will
			start giving out pointers from a different place in memory, possibly from a location that 
			was already used to give out memory.
			*/
			void Reset(size_t offset = 0){allocatedBytes = OVERHEAD_SIZE + offset;}

			//! Returns the current amount of allocated bytes in the growing pool
			/*!
			A checkpoint can be created by storing the current State(), and later passing
			the allocated bytes to the growing pool. This reverts the pointer to the previous state.
			*/
			size_t State(){return allocatedBytes;}
			//! Increases the memory allocated by the growing pool
			/*!
			The growing pool reserves additional memory 
			\param size The amount of bytes to grow the pool by
			*/
			void Grow(size_t size);
		private:
			void* memory;
			size_t allocatedBytes;
			size_t maxSize;

			const size_t OVERHEAD_SIZE;
			enum{DEFAULT_SIZE = 4000};
		};
	}
}