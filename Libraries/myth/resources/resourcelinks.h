
#pragma once

#include <myth\containers\list.h>

namespace myth
{
	namespace resources
	{
		template <class T>
		class ResourceLinks
		{
		public:
			void Add(T *link)
			{
				resources.Add(link);
			}

			void Remove(T *link)
			{
				resources.Remove(link);
			}

			bool Contains(T *link)
			{
				return resources.Contains(link);
			}

			int size()
			{
				return resources.Count();
			}

			void Clear()
			{
				resources.Clear();
			}

			containers::List<T*> resources;
		};
	}
}