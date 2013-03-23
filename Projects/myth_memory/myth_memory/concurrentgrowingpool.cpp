/////////////////////////////
//concurrentgrowingpool.cpp//
/////////////////////////////

#include <myth\mem\concurrentgrowingpool.h>

using myth::mem::ConcurrentGrowingPool;


ConcurrentGrowingPool::ConcurrentGrowingPool(size_t size):
	tasBit(0), OVERHEAD_SIZE(sizeof(PoolInformation)), head(0)
{
	Grow(size);
}

ConcurrentGrowingPool::~ConcurrentGrowingPool()
{
	PoolInformation* current = head;

	while(current)
	{
		head = current->next;
		free(current->memory);
		current = head;
	}
}

void ConcurrentGrowingPool::Grow(size_t size)
{
	head = ReserveMemory(size);
}

void* ConcurrentGrowingPool::GrowAndAlloc(size_t size, size_t allocSize)
{
	PoolInformation* next = ReserveMemory(size);

	void* ptr = (char*)next->memory + (next->allocatedBytes += allocSize);

	head = next;

	return ptr;
}

void* ConcurrentGrowingPool::Alloc(size_t size)
{	
	size_t location;
	while(true)
	{
		PoolInformation* current = head;
		location = std::atomic_fetch_add(&current->allocatedBytes,size);

		if (location + size < current->maxSize) 
			return (char*)current->memory + location;

		if (std::atomic_exchange(&tasBit,1) == 0) 
		{
			void* ptr = GrowAndAlloc(size > current->maxSize ? size : current->maxSize,size);
			tasBit = 0;
			return ptr;
		}
		else while(tasBit == 1){}
	}
}
