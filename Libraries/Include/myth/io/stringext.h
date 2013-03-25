

#pragma once

#include <string>
#include <vector>

namespace myth
{
	namespace io
	{
		inline int ParseSubstring(std::string str, int start, int end)
		{
			int number = 0;
			int length = end - start;
			int factor = pow(10,length);

			for(int i = start; i <= end;i++)
			{
				switch(str[i])
				{
				case '0':
					break;
				case '1':
					number += 1 * factor;
					break;
				case '2':
					number += 2 * factor;
					break;
				case '3':
					number += 3 * factor;
					break;
				case '4':
					number += 4 * factor;
					break;
				case '5':
					number += 5 * factor;
					break;
				case '6':
					number += 6 * factor;
					break;
				case '7':
					number += 7 * factor;
					break;
				case '8':
					number += 8 * factor;
					break;
				case '9':
					number += 9 * factor;
					break;
				}

				factor /= 10;
			}

			return number;
		}

		inline std::vector<int> SplitIntegers(std::string str, const char split)
		{
			std::vector<int> ints;

			int prev = 0;
			for(int i = 0; i <= str.size();i++)
			{
				if (str[i] == split || i == str.size())
				{
					ints.push_back(ParseSubstring(str,prev,i-1));
					prev = i + 1;
				}
			}

			return ints;
		}
	}
}