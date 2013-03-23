
#pragma once

#ifdef _DEBUG

#include <Windows.h>
#include <string>
#include <hash_map>
#include <sstream>

namespace
{
	int __myth_assertidcounter = 0;

	std::hash_map<int,int> __myth_assertignorelist;

	bool AssertBreak(LPCWSTR message, int assertId)
	{
		if (__myth_assertignorelist.find(assertId) != __myth_assertignorelist.end()) return false;

		int val = MessageBoxW(NULL,message, L"Abort = Break - Retry = Ignore Once - Ignore = Ignore Always", MB_ICONERROR | MB_ABORTRETRYIGNORE); 

		if (val == IDABORT) 
		{
			return true;
		}
		else if (val == IDIGNORE) 
		{
			__myth_assertignorelist[assertId] = assertId;
		}

		return false;
	}
}

#define assert_break(message,assertId) if (AssertBreak(message,assertId)) {_asm{int 3}}

#define assert_fail(message,assertId) \
	do \
{ \
	std::wstringstream stream; \
	stream << "Assertion triggered in function " << __FUNCTION__ << " in file " << (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__) << ".\n" << message; \
	std::wstring s = stream.str(); \
	assert_break(s.c_str() ,assertId); \
} while(0) \

#define Assert(express,message) \
	do \
{ \
	static int __myth_assertId = __myth_assertidcounter++; \
	if (!(express)) {assert_fail(message,__myth_assertId);} \
} while(0) \


#define AssertExecutionCount(count, message) \
	do \
{ \
	static int __myth_assertId = __myth_assertidcounter++; \
	static int __myth_executionCount = 0; \
	__myth_executionCount++; \
	if (__myth_executionCount > count) {assert_fail(message,__myth_assertId);} \
} while(0) \

#define DEBUGCODE if(true)
#define DEBUGIF if(true) if
#else
#define Assert(express,message) \
	do \
{ \
	(void)sizeof(express); \
} while(0) \

#define AssertExecutionCount(count,message)

#define DEBUGCODE if (false)
#define DEBUGIF if (false) if
#endif