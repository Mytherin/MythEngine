

#pragma once


#ifdef _dll_io_export_
#define declspec_io __declspec(dllexport)
#else
#define declspec_io __declspec(dllimport)
#endif

#include <string>

namespace myth
{
	namespace io
	{
		class declspec_io FileManager
		{
		public:
			//! Synchronous File I/O, reads the specified file from the disk and returns the file contents as well as length of the file
			/*!
			\param filename The name of the file to be loaded
			\param length Location of an integer, if a non-null value is provided the length of the text file will be written to this location
			\return A pointer to the contents of the text file
			*/
			virtual std::string ReadFile(const std::string filename) const = 0;


			//! Synchronous File I/O, starts reading the object with the specified file entry index from a managed file directory object (.zip)
			/*! The object type will be automatically created once the file finishes loading and can be accessed through the handlemanager
			*/
			virtual void IReadFile(int index) = 0;
			//! Asynchronous File I/O, starts reading the object with the specified file entry index from a managed file directory object (.zip)
			/*! The object type will be automatically created once the file finishes loading and can be accessed through the handlemanager
			*/
			virtual void IAReadFile(int index) = 0;


			static FileManager& Instance()
			{
				return *m_instance;
			}
		protected:
			FileManager() {}
			virtual ~FileManager() {}

			static FileManager *m_instance;
		};

#define g_fileManager myth::io::FileManager::Instance()
	}
}