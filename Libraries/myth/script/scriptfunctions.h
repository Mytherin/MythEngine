
#include <iostream>

namespace myth
{
	namespace script
	{
		
		void print(int str)
		{
			std::cout << str;
		}

		void print(const char* str)
		{
			std::cout << str;
		}
	}
}