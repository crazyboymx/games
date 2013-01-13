
#include "pch.h"
#include "TenDrops.h"

void SoundManager::playEffect( const char* soundName )
{
	if (effectSoundEnabled)
		SimpleAudioEngine::sharedEngine()->playEffect(getSoundFile(soundName));
}

void SoundManager::playBackgroundMusic( const char* soundName )
{
	if (backgroundMusicEnabled)
		SimpleAudioEngine::sharedEngine()->
			playBackgroundMusic(getSoundFile(soundName, false));
}

bool SoundManager::init()
{
	#if _DEBUG
	playEffect("inwater");
	playEffect("level_failed");
	#endif
	return true;
}

char* SoundManager::getSoundFile( const char* soundName, bool effect)
{
	const char* ext = NULL;

	#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
		ext = "ogg";
	#elif CC_TARGET_PLATFORM == CC_PLATFORM_MAC
		// TODO, add resource
		ext = "caf";
	#else
		// windows, etc
		ext = "wav";
	#endif
	return (char*)CCString::createWithFormat("%s.%s", soundName, ext)->getCString();
}