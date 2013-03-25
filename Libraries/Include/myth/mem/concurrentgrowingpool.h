////////////////
//concurrentgrowingpool.h//
////////////////

////////////////////
//CLASS:CONCURRENTGROWINGPOOL//
////////////////////

///////////////
//DESCRIPTION//
///////////////
//The concurrent growing pool is a growing pool whose ALLOC and ALLOCSAFE can be applied by multiple threads at the same
//time in a thread-safe manner. Note that GROW cannot be applied by multiple threads.

//See growingpool.h for a description of all the functions.

#pragma once

#include <atomic>
#include <new>
#include <myth\debug\assert.h>


namespace myth
{
	//! Memory Pools
	/*!
	Contains memory pools that are used to speed up memory allocation
	*/
	namespace mem
	{
		//! A GrowingPool that allows for concurrent memory allocation
		/*!
		The concurrent growing pool is a growing pool that allows an infinite amount of threads to allocate memory from it.
		All methods in the growing pool can be called concurrently and are all lock-free. They use the std::atomic_fetch_add to 
		increment the memory pointer. 
		*/
		class __declspec(dllexport) ConcurrentGrowingPool
		{
		public:
			//! Empty Constructor
			ConcurrentGrowingPool() : OVERHEAD_SIZE(sizeof(void*)), tasBit(0), head(0) {}
			//! Initialization Constructor
			/*!
			\param size The amount of bytes to initialize the concurrent growing pool with.
			*/
			ConcurrentGrowingPool(size_t size);
			//! Destructor
			~ConcurrentGrowingPool();

			//! Safe memory allocation of a specific amount of bytes
			/*!
			\param size The amount of bytes to be requested
			\return The pointer to the start of the newly allocated memory
			*/
			void* Alloc(size_t size);
			//! Unsafe memory allocation of a specific amount of bytes
			/*!
			\param size The amount of bytes to be requested
			\return The pointer to the start of the newly allocated memory
			*/
			void* AllocUnsafe(size_t size)
			{
				PoolInformation* current = head;
				int location = std::atomic_fetch_add(&current->allocatedBytes,size);
				Assert(location + size < current->maxSize,"MEMORY ALLOCATION ERROR: The available memory of the concurrent growing pool has been overriden.");
				return (char*)current->memory + location;
			}
			//! Remaining space of the concurrent growing pool
			/*!
			\return The amount of remaining space in the concurrent growing pool
			*/
			size_t Space(){return head->maxSize - head->allocatedBytes;}
			//! Resets the head of the concurrent growing pool
			void Reset(size_t offset = 0){std::atomic_exchange(&head->allocatedBytes,offset);}
			//! Gets the current amount of allocated bytes in the concurrent growing pool
 			size_t State(){return head->allocatedBytes;}
			//! Reserves additional space for the concurrent growing pool
			/*!
			\param size The amount of bytes to expand the concurrent growing pool by
			*/
			void Grow(size_t size);

			//! Reserves additional space for the concurrent growing pool and immediately allocates the requested memory within it
			/*!
			\param size The amount of bytes to expand the pool by
			\param allocSize The amount of bytes to allocate
			\return A pointer to the allocated memory
			*/
			void* GrowAndAlloc(size_t size, size_t allocSize);
		private:
			struct PoolInformation
			{
			public:
				void* memory;
				std::atomic<size_t> allocatedBytes;
				size_t maxSize;
				PoolInformation* next;
			};


			PoolInformation* ReserveMemory(size_t size)
			{
				size = size > DEFAULT_SIZE ? size + OVERHEAD_SIZE : DEFAULT_SIZE + OVERHEAD_SIZE;
				void* memory = malloc(size);

				PoolInformation* newHead = new (memory) PoolInformation;

				newHead->maxSize = size;
				newHead->memory = memory;
				newHead->allocatedBytes = OVERHEAD_SIZE;
				newHead->next = head;

				return newHead;
			}


			PoolInformation* head;
			std::atomic<int> tasBit;

			const size_t OVERHEAD_SIZE;
			enum{DEFAULT_SIZE = 4000};
		};
	}
}