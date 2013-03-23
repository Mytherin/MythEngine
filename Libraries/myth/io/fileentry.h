

#pragma once

#include <myth\io\types.h>

namespace myth
{
	namespace io
	{
		struct FileEntry
		{
		public:
			FileEntry();
			~FileEntry();

			void Load();
			void Unload();

			obj_id obj;
			type_id type;
			char* dirlocation;
			void* object;
			bool loaded;
		};
	}
}