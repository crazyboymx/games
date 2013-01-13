
#ifndef __PINGANY_SOUNDMANAGER_H__
#define __PINGANY_SOUNDMANAGER_H__

class SoundManager : public CCObject
{
	bool init();
	SoundManager(): effectSoundEnabled(true), backgroundMusicEnabled(true)
	{}

	CC_SYNTHESIZE(bool, effectSoundEnabled, EffectSoundEnabled);
	CC_SYNTHESIZE(bool, backgroundMusicEnabled, BackgroundMusicEnabled);

	char* getSoundFile(const char* soundName, bool effect=true);
public:

	void playEffect(const char* soundName);

	void playBackgroundMusic(const char* soundName);

	CREATE_FUNC(SoundManager);
};

#endif
