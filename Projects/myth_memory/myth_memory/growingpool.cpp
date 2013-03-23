///////////////////
//growingpool.cpp//
///////////////////

#include <myth\mem\growingpool.h>

using myth::mem::GrowingPool;

GrowingPool::GrowingPool(size_t size):
	OVERHEAD_SIZE(sizeof(void*)), memory(0)
{
	Grow(size);
}

GrowingPool::~GrowingPool()
{
	void** nextMemory = (void**)memory;

	do
	{
		void** next = (void**)(*nextMemory);
		free(nextMemory);
		nextMemory = next;
	}while (nextMemory != 0);
}

void GrowingPool::Grow(size_t size)
{
	size = size > DEFAULT_SIZE ? size + OVERHEAD_SIZE : DEFAULT_SIZE + OVERHEAD_SIZE;

	void* previousMemory(memory);
	memory = malloc(size);

	//create the overhead, a pointer to the previous memory stack
	new (memory) void*(previousMemory);

	allocatedBytes = OVERHEAD_SIZE;
	maxSize = size;
}