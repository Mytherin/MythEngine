#include <myth\generic\numerics.h>

using namespace myth::io;

template <class T>
T Numerics::Power(T value, int power)
{
	if (power == 0) return 1;
	//if (power == 1) return value;

	T pow = value;
	for(int i = 1; i < power; i++)
		pow = pow * value;
	return pow;
	/*T halfPower = Power<T>(value,power/2);
	T fullPower = power % 2 != 0 ? halfPower*halfPower * value : halfPower*halfPower;

	return fullPower;*/
}

template <class T>
T Numerics::ParseIntegerFromSubstring(String str, int start, int end)
{
	if (end < start || start < 0) return -1;
	
	bool negative = str[start] == '-';
	if (negative) start++;
	T number = 0;
	int length = end - start;
	//T factor = pow(10,length);
	T factor = Numerics::Power<T>(10,length);

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
		default: 
			return -1;
		}

		factor /= 10;
	}

	return negative ? -number : number;
}


template <class T>
T Numerics::ParseFloatFromSubstring(String str, int start, int end)
{
	if (end < start || start < 0) return -1;
	
	bool negative = str[start] == '-';
	if (negative) start++;
	T number = 0;
	
	int decimal = end;

	for(int i = start; i <= end;i++)
	{
		if (str[i] == '.' || str[i] == ',') 
		{
			decimal = i-1;
			break;
		}
	}
	int length = decimal - start;
	T factor = Numerics::Power<T>(10,length);

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
		case ',':
		case '.':
			continue;
		default: 
			return -1;
		}

		factor /= 10;
	}

	return negative ? -number : number;
}