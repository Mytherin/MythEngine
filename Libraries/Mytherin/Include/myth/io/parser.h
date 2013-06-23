

#pragma once

#ifdef _dll_io_export_
#define declspec_io __declspec(dllexport)
#else
#define declspec_io __declspec(dllimport)
#endif

#include <myth\generic\list.h>
#include <myth\generic\map.h>
#include <myth\generic\string.h>

namespace myth
{
	namespace io
	{	
		typedef Map<String,String> KeyValueMap;

		class declspec_io Parser
		{
		public:
			static String LineEnd();

			/*!
			Splits a string into separate parts separated a specific character.
			\param The string to parse.
			\param The character to split the string by.
			\return A list of all the substrings.
			*/
			static List<String> SplitStrings(String str, const char split);

			/*!
			Generic method that allows you to parse a set of (name,value) pairs from a string with a specified format.
			\param str The string to parse from.
			\param format The format of the (name,value) pairs as a string. The format should contain %n as 'name' and %v as 'value'. The format must contain %n and %v one time.
			 there must be at least one character between the %n and %v (this may be a space) and there must be at least one character before or after both %n and %v within the format.
			Examples of some correct formats are: 
			* "%n = %v;" 
			* "#define %n %v"
			* "(%v,%n)"
			Examples of some incorrect formats:
			* "(%v)"        [no %n tag]
			* "%n%v"        [no character between %n and %v]
			* "%n %v"       [no character either before %n or after %v]
			* "%n (%v,%v)"  [%v occurs twice]
			\param ignoreWhiteSpace Set to true to ignore white space (white space will be removed from both the 'format' and 'str' parameters), 
			* set to false to treat whitespace characters as a regular characters
			\param caseSensitiveName Whether or not the names that are used as key in the (name,value) pair are case sensitive. If this is set to false, the names used as keys are all lower case (so 'Name' is converted to 'name'), otherwise the original case is used.
			\return A map of <name,value> pairs extracted from the string
			*/
			static KeyValueMap ParseAssignments(String str, String format, bool ignoreWhiteSpace = true, bool caseSensitiveName = false);
		};
	}
}