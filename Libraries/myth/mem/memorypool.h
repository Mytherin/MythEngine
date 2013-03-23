
#pragma once

namespace myth
{
	namespace mem
	{
		//! A templated memory pool that allows for allocating and freeing of memory for elements of a specific class
		/*!
		The memory pool class is a memory allocation class with the purpose of speeding up memory allocation and deallocation
		of a set of specific classes in a single-threaded environment. The pool requests a large chunk of memory initially, 
		and requests more memory if it fills up; it then manages all the memory

		The MemoryPool grants the largest performance boost when a large amount of the same objects need to be consistently created 
		and destroyed throughout an application's lifespan; if the objects never get destroyed the pool continuously requests new memory and barely
        speeds up the memory allocation; if the objects are destroyed as a bulk (all at once) an unsafe static growing pool is better suited for
		the job as it can instantaneously create 
		*/
		template<class T>
		class __declspec(dllexport) MemoryPool
		{
		public:
			//! Empty Constructor
			/*!
			The empty constructor generates a memory pool with no memory allocated, it must be allocated with Grow later to safely use the pool
			*/
			MemoryPool() : next(0){}
			//! Initialization Constructor
			/*!
			Creates a memory pool with a reserved amount of memory.
			\param size The amount of objects for which memory must be allocated
			*/
			MemoryPool(size_t size) : next(0){ Grow(size);}
			//! Desstructor
			/*! Destroys the free memory of the memory pool; does not destroy any memory that has been allocated with Alloc but not returned
			*/
			~MemoryPool()
			{
				MemoryPool<T> *nextPtr = next;
				for (nextPtr = next; nextPtr != 0; nextPtr = next) {
					next = next->next;
					free(nextPtr);
				}
			}

			//! Allocates memory for a single object of template class T
			/*!
			\return Returns a pointer to the memory
			*/
			void* Alloc()
			{
				if (!next) {
					Grow();
				}

				MemoryPool<T> *head = next;
				next = head->next;

				return head;
			}

			//! Frees an element to the memory pool, allowing it to give out the memory of the object again
			/*!
			\param element A pointer to the element to be freed
			*/
			void Free(void* element)
			{
				MemoryPool<T> *head = (MemoryPool<T>*)element;

				head->next = next;
				next  = head;
			}

			//! Expands the reserved size of the memory pool
			/*!

			\param count The amount of elements to grow the memory pool by.
			*/
			void Grow(int count = EXPANSION_SIZE)
			{
				size_t size = (sizeof(T) > sizeof(MemoryPool<T>*)) ? sizeof(T) : sizeof(MemoryPool<T>*);

				void* mem = malloc(size * count);
				MemoryPool<T> *current = (MemoryPool<T>*) mem;

				next = current;
				for (int i = 0; i < count ; i++) {
					current->next = (MemoryPool<T>*) (char*)(mem + size * (i+1));
					current = current->next;
				}
				current->next = 0;
			}
		private:
			MemoryPool<T>* next;

			enum{EXPANSION_SIZE = 32};
		};
	}
}