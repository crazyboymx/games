
#include "pch.h"
#include "TenDrops.h"

LevelConfiguration* LevelConfiguration::getRandomConfiguration()
{
	LevelConfiguration* config = LevelConfiguration::create();

	config->leftDrops = Utils::rand(10, 20);
	forn(i, 0, config->ncells)
		config->waters[i] = Utils::rand(0, 4);
	return config;
}