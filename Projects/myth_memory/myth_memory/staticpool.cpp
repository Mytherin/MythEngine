//////////////////
//staticpool.cpp//
//////////////////

#include <mytherin\core\memory\staticpool.h>

using MYTH::StaticPool;

StaticPool::StaticPool(size_t size) :
	allocatedBytes(0), maxSize(size)
{
	memory = malloc(maxSize);
}