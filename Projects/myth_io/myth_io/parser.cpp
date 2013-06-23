
#include <myth\debug\assert.h>
#include <myth\io\parser.h>

#include <algorithm>
#include <iostream>

using namespace myth::io;


String Parser::LineEnd()
{
	#ifdef WIN32
		return "\r\n";
	#elif APPLE
		return "\n";
	#elif LINUX
		return "\r";
	#else
		return 'n';
	#endif
}

KeyValueMap Parser::ParseAssignments(String str,String format, bool ignoreWhiteSpace, bool caseSensitiveName)
{
	KeyValueMap nameValueMap;

	if (ignoreWhiteSpace)
	{
		format.erase(std::remove_if(format.begin(),format.end(),::isspace),format.end());
		str.erase(std::remove_if(str.begin(),str.end(),::isspace),str.end());
	}

	//first parse the format, finding the location of %n and %v
	int phase = 0;
	int name = -1;
	int value = -1;
	for(int i = 0; i < format.size()-1; i++)
	{
		if (format[i] == '%')
		{
			if (format[i+1] == 'n') 
			{
				Assert(name == -1,"FORMAT PARSE ERROR: The \"%n\" tag occurs twice within the format.");
				name = i;
			}
			if (format[i+1] == 'v') 
			{
				Assert(value == -1,"FORMAT PARSE ERROR: The \"%v\" tag occurs twice within the format.");
				value = i;
			}
		}
	}
	Assert((name != 0 && value != 0) || (name != format.size()-1 && value != format.size()-1),"FORMAT PARSE ERROR: There must be at least one character either before the first \"%n\" or \"%v\" or after the last \"%n\" or \"%v\" tags");
	Assert(abs(name - value) != 2,"FORMAT PARSE ERROR: There are no characters between the \"%n\" and \"%v\" tags.");

	int pos = 0;
	int nameStart = -1, valueStart = -1;
	int nameEnd = -1, valueEnd = -1;
	//now parse the (name,value) pairs from the string using the specified format by recording the start/end of both the 'name' and 'value' within the substrings
	for(int i = 0; i < str.size(); i++)
	{
		if (pos != name && pos != value && (pos < value || pos < name))
		{
			if (str[i] == format[pos])
			{
				pos++;
			}
			else pos = 0;
		}
		else if (pos == name)
		{
			if (nameStart == -1)
			{
				nameStart = i;
			}
			else if (str[i] == format[pos+2])
			{
				nameEnd = i;
				pos = pos + 3;
			}
		}
		else if (pos == value)
		{
			if (valueStart == -1)
			{
				valueStart = i;
			}
			else if (str[i] == format[pos+2])
			{
				valueEnd = i;
				pos = pos + 3;
				if (pos == format.size())
				{
					String name = str.substr(nameStart,nameEnd - nameStart);
					if (!caseSensitiveName)
						std::transform(name.begin(),name.end(),name.begin(),::tolower);
					String value = str.substr(valueStart,valueEnd - valueStart);

					nameValueMap.emplace(name,value);

					nameStart = -1;
					nameEnd = -1;
					valueStart = -1;
					valueEnd = -1;
					pos = 0;
				}
			}
		}
		else if (pos > name && pos > value)
		{
			if (pos == format.size() || (pos == format.size()-1 && str[i] == format[pos]))
			{
				String name = str.substr(nameStart,nameEnd - nameStart);
				if (!caseSensitiveName)
					std::transform(name.begin(),name.end(),name.begin(),::tolower);
				String value = str.substr(valueStart,valueEnd - valueStart);

				nameValueMap.emplace(name,value);

				nameStart = -1;
				nameEnd = -1;
				valueStart = -1;
				valueEnd = -1;
				pos = 0;
			}
			else if (str[i] == format[pos])
			{
				pos++;
				/*
				if (pos == format.size())
				{
					String name = str.substr(nameStart,nameEnd - nameStart);
					if (!caseSensitiveName)
						std::transform(name.begin(),name.end(),name.begin(),::tolower);
					String value = str.substr(valueStart,valueEnd - valueStart);

					nameValueMap.emplace(name,value);

					nameStart = -1;
					nameEnd = -1;
					valueStart = -1;
					valueEnd = -1;
					pos = 0;
				}*/
			}
			else pos = 0;
		}
	}
	return nameValueMap;
}
		
List<String> Parser::SplitStrings(String str, const char split)
{
	List<String> splits;

	int prev = 0;
	for(int i = 0; i <= str.size();i++)
	{
		if (str[i] == split || i == str.size())
		{
			if (i == prev) 
			{
				prev = i + 1;
				continue;
			}
			splits.push_back(str.substr(prev,i - prev));
			prev = i + 1;
		}
	}

	return splits;
}