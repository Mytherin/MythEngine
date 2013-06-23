

#pragma once

#ifdef _dll_generic_export_
#define declspec_generic __declspec(dllexport)
#else
#define declspec_generic __declspec(dllimport)
#endif

#include <myth\generic\string.h>

namespace myth
{
	namespace io
	{	
		/*! 
		A class containing static functions that work with various number types.
		*/
		class declspec_generic Numerics
		{
		public:
			
			/*!
			Takes the power of a specified integral number
			\param value The value
			\param power The power
			\return The value to the specified power.
			*/
			template <class T>
			static T Power(T value, int power);
			

			/*!
			Parses a string to an integer (number without decimals).
			\param str The string to parse the integer from.
			\return The parsed integer.
			*/
			template <class T>
			static T ParseIntegerFromString(String str) { return ParseIntegerFromSubstring(str,0,str.size()-1); }
			
			/*!
			Parses a string to an integer (number without decimals).
			\param str The string to parse the integer from.
			\param start The start of the substring. 0 <= start < end must hold true. 
			\param end The end of the substring. start < end < str.Size() must hold true.
			\return The parsed integer.
			*/
			template <class T>
			static T ParseIntegerFromSubstring(String str, int start, int end);

			
			/*!
			Parses a string to a floating point number.
			\param str The string to parse the floating point number from.
			\return The parsed floating point number.
			*/
			template <class T>
			static T ParseFloatFromString(String str) { return ParseFloatFromSubstring(str,0,str.size()-1); }
			
			/*!
			Parses a string to a floating point number.
			\param str The string to parse the floating point number from.
			\param start The start of the substring. 0 <= start < end must hold true. 
			\param end The end of the substring. start < end < str.Size() must hold true.
			\return The parsed floating point number.
			*/
			template <class T>
			static T ParseFloatFromSubstring(String str, int start, int end);

		private: Numerics();
		};

		/*! 
		A class containing static functions that work with integers.
		*/
		class declspec_generic Int
		{
		public:
			static int Power(int val, int power) { return Numerics::Power<int>(val,power);}

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
			static int ParseSubstring(String str, int start, int end) { return Numerics::ParseIntegerFromSubstring<int>(str,start,end);}
		private: Int();
		};
		
		/*! 
		A class containing static functions that work with unsigned integers.
		*/
		class declspec_generic UInt
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
			static unsigned int ParseSubstring(String str, int start, int end){ return Numerics::ParseIntegerFromSubstring<unsigned int>(str,start,end);}
		private: UInt();
		};
		
		/*! 
		A class containing static functions that work with short integers.
		*/
		class declspec_generic Short
		{
		public:
			/*!
			Parses a string to an integer.
			\param The string to parse the integer from.
			\return The parsed integer.
			*/
			static short ParseString(String str) { return ParseSubstring(str,0,str.size()-1); }
			
			/*!
			Parses part of a string to an integer.
			\param The string to parse the integer from.
			\param The start of the substring. 0 <= start < end must hold true. 
			\param The end of the substring. start < end < str.Size() must hold true.
			\return The parsed integer.
			*/
			static short ParseSubstring(String str, int start, int end){ return Numerics::ParseIntegerFromSubstring<short>(str,start,end);}
		private: Short();
		};
		
		/*! 
		A class containing static functions that work with unsigned integers.
		*/
		class declspec_generic UShort
		{
		public:
			/*!
			Parses a string to an unsigned integer.
			\param The string to parse the unsigned integer from.
			\return The parsed unsigned integer.
			*/
			static unsigned short ParseString(String str) { return ParseSubstring(str,0,str.size()-1); }
			
			/*!
			Parses part of a string to an unsigned integer.
			\param The string to parse the unsigned integer from.
			\param The start of the substring. 0 <= start < end must hold true. 
			\param The end of the substring. start < end < str.Size() must hold true.
			\return The parsed unsigned integer.
			*/
			static unsigned short ParseSubstring(String str, int start, int end){ return Numerics::ParseIntegerFromSubstring<unsigned short>(str,start,end);}
		private: UShort();
		};

		/*! 
		A class containing static functions that work with unsigned long integers.
		*/
		class declspec_generic Long
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
			static long ParseSubstring(String str, int start, int end){ return Numerics::ParseIntegerFromSubstring<long>(str,start,end);}
		private: Long();
		};
		
		/*! 
		A class containing static functions that work with unsigned long integers.
		*/
		class declspec_generic ULong
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
			static unsigned long ParseSubstring(String str, int start, int end){ return Numerics::ParseIntegerFromSubstring<unsigned long>(str,start,end);}
		private: ULong();
		};
		
		/*! 
		A class containing static functions that work with floating point numbers.
		*/
		class declspec_generic Float
		{
		public:
			/*!
			Parses a string to a float.
			\param The string to parse the float from.
			\return The parsed float.
			*/
			static float ParseString(String str) { return ParseSubstring(str,0,str.size()-1); }
			
			/*!
			Parses part of a string to a float.
			\param The string to parse the float from.
			\param The start of the substring. 0 <= start < end must hold true. 
			\param The end of the substring. start < end < str.Size() must hold true.
			\return The parsed float.
			*/
			static float ParseSubstring(String str, int start, int end){ return Numerics::ParseFloatFromSubstring<float>(str,start,end);}
		private: Float();
		};

		
		/*! 
		A class containing static functions that work with double numbers.
		*/
		class declspec_generic Double
		{
		public:
			/*!
			Parses a string to a double.
			\param The string to parse the double from.
			\return The parsed double.
			*/
			static double ParseString(String str) { return ParseSubstring(str,0,str.size()-1); }
			
			/*!
			Parses part of a string to a double.
			\param The string to parse the double from.
			\param The start of the substring. 0 <= start < end must hold true. 
			\param The end of the substring. start < end < str.Size() must hold true.
			\return The parsed double.
			*/
			static double ParseSubstring(String str, int start, int end){ return Numerics::ParseFloatFromSubstring<double>(str,start,end);}
		private: Double();
		};
	}
}