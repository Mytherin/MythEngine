

#pragma once

#ifdef _dll_oswindows_export_
#define declspec_oswindows __declspec(dllexport)
#else
#define declspec_oswindows __declspec(dllimport)
#endif

#include <myth\io\filemanager.h>
#include <Windows.h>

namespace myth
{
	namespace os
	{
		namespace windows
		{
			class declspec_oswindows Win32FileManager : public io::FileManager
			{
			public:
				//! Empty constructor for the graphics manager
				Win32FileManager();
				//! Destructor
				~Win32FileManager();

				std::string ReadFile(const std::string filename) const;

				void IReadFile(int index);

				void IAReadFile(int index);
			};
		}
	}
}