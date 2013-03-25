

#pragma once

#include <myth\containers\dictionary.h>
#include <myth\io\fileentry.h>
#include <myth\io\types.h>

namespace myth
{
	namespace io
	{
		class FileIndex
		{
		public:
			FileIndex();
			~FileIndex();

			bool Contains(obj_id id);
			FileEntry Get(obj_id id);
		private:
			containers::Dictionary<FileEntry> index;
		};
	}
}