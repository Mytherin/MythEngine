

#pragma once

#ifdef _dll_io_export_
#define declspec_io __declspec(dllexport)
#else
#define declspec_io __declspec(dllimport)
#endif

#include <myth\generic\string.h>

namespace myth
{
	namespace io
	{	
		/*! 
		A class containing static functions that work with integers.
		*/
		class declspec_io Int
		{
		public:
			/*!
			Parses a string to an integer.
			\param The string to parse the integer from.
			\return The parsed integer.
			*/
			static int ParseString(String str) { return ParseSubstring(str,0,str.size()-1); }
			
			/*!
			Parses part of a string to an integer.
			\param The string to parse the integer from.
			\param The start of the substring. 0 <= start < end must hold true. 
			\param The end of the substring. start < end < str.Size() must hold true.
			\return The parsed integer.
			*/
			static int ParseSubstring(String str, int start, int end);
		private: Int();
		};
		
		/*! 
		A class containing static functions that work with unsigned integers.
		*/
		class declspec_io UInt
		{
		public:
			/*!
			Parses a string to an unsigned integer.
			\param The string to parse the unsigned integer from.
			\return The parsed unsigned integer.
			*/
			static unsigned int ParseString(String str) { return ParseSubstring(str,0,str.size()-1); }
			
			/*!
			Parses part of a string to an unsigned integer.
			\param The string to parse the unsigned integer from.
			\param The start of the substring. 0 <= start < end must hold true. 
			\param The end of the substring. start < end < str.Size() must hold true.
			\return The parsed unsigned integer.
			*/
			static unsigned int ParseSubstring(String str, int start, int end);
		private: UInt();
		};
		
		/*! 
		A class containing static functions that work with short integers.
		*/
		class declspec_io Short
		{
		public:
			/*!
			Parses a string to an integer.
			\param The string to parse the short integer from.
			\return The parsed integer.
			*/
			static short ParseString(String str) { return ParseSubstring(str,0,str.size()-1); }
			
			/*!
			Parses part of a string to an short integer.
			\param The string to parse the shortinteger from.
			\param The start of the substring. 0 <= start < end must hold true. 
			\param The end of the substring. start < end < str.Size() must hold true.
			\return The parsed integer.
			*/
			static short ParseSubstring(String str, int start, int end);
		private: Short();
		};
		
		/*! 
		A class containing static functions that work with unsigned short integers.
		*/
		class declspec_io UShort
		{
		public:
			/*!
			Parses a string to an unsigned integer.
			\param The string to parse the unsigned short integer from.
			\return The parsed unsigned integer.
			*/
			static unsigned short ParseString(String str) { return ParseSubstring(str,0,str.size()-1); }
			
			/*!
			Parses part of a string to an unsigned short integer.
			\param The string to parse the unsigned short integer from.
			\param The start of the substring. 0 <= start < end must hold true. 
			\param The end of the substring. start < end < str.Size() must hold true.
			\return The parsed unsigned short integer.
			*/
			static unsigned short ParseSubstring(String str, int start, int end);
		private: UShort();
		};
		
		/*! 
		A class containing static functions that work with unsigned long integers.
		*/
		class declspec_io Long
		{
		public:
			/*!
			Parses a string to a long integer.
			\param The string to parse the long integer from.
			\return The parsed long integer.
			*/
			static long ParseString(String str) { return ParseSubstring(str,0,str.size()-1); }
			
			/*!
			Parses part of a string to an long integer.
			\param The string to parse the long from.
			\param The start of the substring. 0 <= start < end must hold true. 
			\param The end of the substring. start < end < str.Size() must hold true.
			\return The parsed long integer.
			*/
			static long ParseSubstring(String str, int start, int end);
		private: Long();
		};
		
		/*! 
		A class containing static functions that work with unsigned long integers.
		*/
		class declspec_io ULong
		{
		public:
			/*!
			Parses a string to an unsigned long integer.
			\param The string to parse the unsigned long integer from.
			\return The parsed unsigned long integer.
			*/
			static unsigned long ParseString(String str) { return ParseSubstring(str,0,str.size()-1); }
			
			/*!
			Parses part of a string to an unsigned long integer.
			\param The string to parse the unsigned long integer from.
			\param The start of the substring. 0 <= start < end must hold true. 
			\param The end of the substring. start < end < str.Size() must hold true.
			\return The parsed unsigned long integer.
			*/
			static unsigned long ParseSubstring(String str, int start, int end);
		private: ULong();
		};
	}
}