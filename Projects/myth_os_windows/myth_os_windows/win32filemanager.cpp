
#include <myth\os\windows\win32filemanager.h>
#include <myth\debug\assert.h>

#include <fstream>

using namespace myth::os::windows;


Win32FileManager::Win32FileManager()
{
	FileManager::m_instance = this;
	AssertExecutionCount(1,"SINGLETON ERROR: A singleton instance of type Win32FileManager has been initiated more than once");
}

Win32FileManager::~Win32FileManager()
{

}

std::string Win32FileManager::ReadFile(const std::string filename) const
{
	std::ifstream fs(filename,std::ios::binary);

	if (!fs)
	{
		printf("FILE READING ERROR: Attempting to read file %s, but the file could not be found.",filename);
		Assert(fs,"FILE READING ERROR: A file with the specified filename was not found.");
	}

	std::string file;

	fs.seekg(0, std::ios::end);     //move the pointer to the end of the file
	std::ifstream::pos_type filesize = fs.tellg();
	file.resize(filesize);          //read the current pointer position to obtain the length, resize the string to this length

	fs.seekg(0, std::ios::beg);     //move the pointer back to the start of the file

	fs.read(&file[0], filesize);    //read the entire length of the file into the string

	fs.close();                     //close the filestream

	return file;
}

void Win32FileManager::IReadFile(int index)
{
}

void Win32FileManager::IAReadFile(int index)
{
}
