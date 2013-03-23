
#pragma once


namespace myth
{
	namespace containers
	{
		template <class T>
		class List
		{
		public:
			List(unsigned int initialSize = 10) : 
				elementCount(0),containerSize(initialSize),elements(new T[initialSize])
			{
			}
			~List()
			{
				delete [] elements;
			}

			void Add(T element)
			{
				if (containerSize <= elementCount)
				{
					T* newContainer = new T[containerSize*2];

					for(int i = 0; i < containerSize; ++i)
						newContainer[i] = T(elements[i]);

					delete [] elements;
					elements = newContainer;
					containerSize = containerSize * 2;
				}
				elements[elementCount] = element;

				++elementCount;
			}

			void Remove(const T& element)
			{
				for(int i = 0; i < elementCount; ++i)
				{
					if (element == elements[i])
					{
						RemoveAt(i);
						return;
					}
				}
			}

			void RemoveAt(unsigned int index)
			{
				for(int i = index; i < elementCount; i++)
					elements[i] = elements[i+1];

				--elementCount;
			}
			void Clear()
			{
				elementCount = 0;
			}
			bool Contains(const T& element)
			{
				for(int i = 0; i < elementCount; i++)
					if (element == elements[i])
					{
						return true;
					}
				return false;
			}
			int Count(){return elementCount;}
			int Size(){return containerSize;}
			
			T* elements;
		private:
			int elementCount;
			int containerSize;
		};
	}
}