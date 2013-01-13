
#include "pch.h"
#include "TenDrops.h"

void SoundManager::playEffect( const char* filename )
{
	if (effectSoundEnabled)
		SimpleAudioEngine::sharedEngine()->playEffect(filename);
}

void SoundManager::playBackgroundMusic( const char* filename )
{
	if (backgroundMusicEnabled)
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic(filename);
}