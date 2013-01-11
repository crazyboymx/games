
#include "Utils.h"

bool Utils::seeded = false;

int Utils::rand( int i, int j )
{
	if (seeded)
	{
		srand(time(NULL));
		seeded = true;
	}
	return ::rand() % (j - i + 1) + i;
}