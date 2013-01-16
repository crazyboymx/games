
#ifndef __PINGANY_LEVELCONFIGURATION_H__
#define __PINGANY_LEVELCONFIGURATION_H__

class LevelConfiguration : public CCObject
{
	LevelConfiguration(){}
	bool init(){ return true; }
public:
	static LevelConfiguration* getRandomConfiguration();
	~LevelConfiguration(){}
	CREATE_FUNC(LevelConfiguration);
};

#endif
