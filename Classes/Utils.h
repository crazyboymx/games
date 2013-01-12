#ifndef __PINGANY_UTILS_H_
#define __PINGANY_UTILS_H_

#include "CCStdC.h"
#define forn(i, a, b) \
	for(int i = (a), __end = (b); i < __end; ++i)

class Utils
{
	static bool seeded;
public:
	static int rand(int i, int j);

	template<typename T>
	static void shuffle(T* arr, int offset, int length)
	{
		int last = offset+length-1;
		forn(i, offset, last)
		{
			swap(arr[i], arr[rand(i+1, last)]);
		}
	}

	template<typename T>
	static void swap(T &a, T& b)
	{
		T t = a;
		a = b;
		b = t;
	}
};
#endif
