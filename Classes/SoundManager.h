
#ifndef __PINGANY_SOUNDMANAGER_H__
#define __PINGANY_SOUNDMANAGER_H__

class SoundManager : public CCObject
{
	bool init() { return true; }
	SoundManager(): effectSoundEnabled(true), backgroundMusicEnabled(true)
	{}

	CC_SYNTHESIZE(bool, effectSoundEnabled, EffectSoundEnabled);
	CC_SYNTHESIZE(bool, backgroundMusicEnabled, BackgroundMusicEnabled);
public:

	void playEffect(const char* filename);

	void playBackgroundMusic(const char* filename);

	CREATE_FUNC(SoundManager);
};

#endif
